#include <graph.h>
#include <QDebug>

template <class V>
Graph<V>::Graph()
{
    this->vertices = new std::vector<V>;
};

template <class V>
Graph<V>::Graph(std::vector<V> *vertices)
{
    this->vertices = vertices;
};

template < class V>
Graph<V>* Graph<V>::add_vertex(V* vertex)
{
    this->vertices->push_back(vertex);
    return this;
};

template < class V>
void Graph<V>::delete_vertex(int vertex_id)
{
    for(auto iter = this->vertices->begin();iter!=this->vertices->end(); ++iter)
    {
        if(iter->get_id() == vertex_id)
            this->vertices->erase(iter);
        break;
    }
};

template < class V>
V Graph<V>::add_edge(int id, Edge edge)
{
    for(auto iter = this->vertices->begin();iter!=this->vertices->end(); ++iter)
    {
        if(iter->get_id() == id)
            iter->add_edge(edge);
    }
};


template < class V>
void Graph<V>::delete_edge(int vertex_id, int edge_id)
{
    for(auto iter = this->vertices->begin();iter!=this->vertices->end(); ++iter)
    {
        if(iter->get_id() == vertex_id)
            iter->delete_edge(edge_id);
    }
};

template < class V>
Graph<V>::~Graph(){
    this->vertices->clear();
    delete this->vertices;
};

template < class V>
Iterator<V> Graph<V>::begin()
{
    return iterator(this->vertices[0]);
};

template < class V>
Iterator<V> Graph<V>::end()
{
    return new Iterator<V>(this->vertices[this->vertices->size()-1]);
};

template < class V>
Iterator<const V> Graph<V>::begin() const
{
    return new Iterator<const V>(this->vertices[0]);
};

template < class V>
Iterator<const V> Graph<V>::end() const
{
    return Iterator<const V>(this->vertices->size()-1);
};

template < class V>
std::string Graph<V>::find_way(int from_id, int to_id)
{

//   Debug version with test data

//   auto vertexes = initTestVertexes();

//   for(auto vert = vertexes->begin();vert!=vertexes->end(); ++vert)
//   {
//       this->add_vertex(*vert);
//   }

   // Release version
   std::vector<Vertex<E>>* vertexes = this->vertexs;

    int MAX_INT = 100000;
    int SIZE = vertexes->size();
    int a[SIZE][SIZE]; // матрица связей
    int d[SIZE]; // минимальное расстояние
    int v[SIZE]; // посещенные вершины
    int temp;
    int minindex, min;

    int begin_vert_index = 0;
    int end_vert_index = 0;

    for(auto vert = vertexes->begin();vert!=vertexes->end();++vert) {
        if ((begin_vert_index != 0) && (end_vert_index != 0)) break;

        if (vert->get_id() == from_id) begin_vert_index = std::distance(vertexes->begin(), vert);
        if (vert->get_id() == to_id) end_vert_index = std::distance(vertexes->begin(), vert);
    }

    std::swap(vertexes->at(0), vertexes->at(begin_vert_index));
    std::swap(vertexes->at(SIZE - 1), vertexes->at(end_vert_index));

    // Инициализация матрицы связей
    for (int i = 0; i<SIZE; i++)
    {
      a[i][i] = 0;

      for (int j = 0; j<SIZE; j++) {
          int temp_time = 0;
          if (i == j) {
              a[i][j] = 0;
              continue;
          }
          std::vector<Edge>* edges = vertexes->at(i).get_edges();
          int to_vert_id = vertexes->at(j).get_id();

          for(auto edge = edges->begin();edge!=edges->end();++edge) {
              if (edge->get_to_id() == to_vert_id) temp_time = edge->get_fly_time();
          }
          a[i][j] = temp_time;
      }
    }

    //Инициализация вершин и расстояний
      for (int i = 0; i<SIZE; i++)
      {
        d[i] = MAX_INT;
        v[i] = 1;
      }
      d[0] = 0;
      // Шаг алгоритма
      do {
        minindex = MAX_INT;
        min = MAX_INT;
        for (int i = 0; i<SIZE; i++)
        { // Если вершину ещё не обошли и вес меньше min
          if ((v[i] == 1) && (d[i]<min))
          { // Переприсваиваем значения
            min = d[i];
            minindex = i;
          }
        }
        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (minindex != MAX_INT)
        {
          for (int i = 0; i<SIZE; i++)
          {
            if (a[minindex][i] > 0)
            {
              temp = min + a[minindex][i];
              if (temp < d[i])
              {
                d[i] = temp;
              }
            }
          }
          v[minindex] = 0;
        }
      } while (minindex < MAX_INT);
      // Восстановление пути
      std::vector<std::string>* way = new std::vector<std::string>();
      int end = SIZE - 1; // индекс конечной вершины = 5 - 1
      way->push_back(vertices->at(end).get_name()); // начальный элемент - конечная вершина
      int k = 1; // индекс предыдущей вершины
      int weight = d[end]; // вес конечной вершины

      while (end > 0) // пока не дошли до начальной вершины
      {
        for(int i=0; i<SIZE; i++) // просматриваем все вершины
          if (a[i][end] != 0)   // если связь есть
          {
            int temp = weight - a[i][end]; // определяем вес пути из предыдущей вершины
            if (temp == d[i]) // если вес совпал с рассчитанным
            {                 // значит из этой вершины и был переход
              weight = temp; // сохраняем новый вес
              end = i;
              way->push_back(vertices->at(i).get_name());// сохраняем предыдущую вершину
              k++;
            }
          }
      }
      std::string fullWay = way->at(way->size() - 1);

      for(auto vert = way->rbegin() + 1;vert!=way->rend();vert++) {
        fullWay = fullWay + " -> " + vert->substr();
      }

   return fullWay;
}

//I can't do it with generics and want to sleep (((
/*std::vector<V<E>>* Graph<V,E>::initTestVertexes() {
    Edge *e35 = new Edge(5,8);
    Edge *e36 = new Edge(6,5);

    std::vector<Edge> *edges3 = new std::vector<Edge>();

    edges3->push_back(*e35);
    edges3->push_back(*e36);

    Edge *e53 = new Edge(3,4);
    Edge *e56 = new Edge(6,4);
    Edge *e58 = new Edge(8,3);

    std::vector<Edge>* edges5 = new std::vector<Edge>();

    edges5->push_back(*e53);
    edges5->push_back(*e56);
    edges5->push_back(*e58);

    Edge *e63 = new Edge(3,12);

    std::vector<Edge>* edges6 = new std::vector<Edge>();

    edges6->push_back(*e63);

    Edge *e85 = new Edge(5,1);
    Edge *e86 = new Edge(6,2);

    std::vector<Edge> *edges8 = new std::vector<Edge>();

    edges8->push_back(*e85);
    edges8->push_back(*e86);

    Vertex *v0 = new Vertex(3, "Vertex3", 3.0, 3.0, edges3);
    Vertex *v1 = new Vertex(5, "Vertex5", 3.0, 3.0, edges5);
    Vertex *v2 = new Vertex(6, "Vertex6", 3.0, 3.0, edges6);
    Vertex *v3 = new Vertex(8, "Vertex8", 3.0, 3.0, edges8);

    std::vector<Vertex> *vertexes = new std::vector<Vertex>();

    vertexes->push_back(*v0);
    vertexes->push_back(*v1);
    vertexes->push_back(*v2);
    vertexes->push_back(*v3);

    return vertexes;
}*/
