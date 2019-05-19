#include <graph.h>
#include <QDebug>

Graph::Graph()
{
    this->vertexs = new std::vector<Vertex>;
}

Graph::Graph(std::vector<Vertex> *vertes)
{
    this->vertexs = vertes;
}

<<<<<<< HEAD
std::string Graph::find_way(int from_id, int to_id)
{

//    Vertex v1 = new Vertex('Moscow', 10, 10, );
    int SIZE = this->vertexs->size();
    int a[SIZE][SIZE]; // матрица связей
    int d[SIZE]; // минимальное расстояние
    int v[SIZE]; // посещенные вершины
    int temp;
    int minindex, min;

    // Инициализация матрицы связей
    for (int i = 0; i<SIZE; i++)
    {
      a[i][i] = 0;

      for (int j = i + 1; j<SIZE; j++) {
          int temp_time = 0;
          std::vector<Edge>* edges = this->vertexs->at(i).get_edges();
          int to_vert_id = this->vertexs->at(j).id;
          foreach (Edge edge, edges) {
              if (edge.get_to_id() == to_vert_id) temp_time = edge.get_fly_time();
          }
          a[i][j] = temp;
          a[j][i] = temp;
      }
    }
    //Инициализация вершин и расстояний
      for (int i = 0; i<SIZE; i++)
      {
        d[i] = 10000;
        v[i] = 1;
      }
      d[0] = 0;
      // Шаг алгоритма
      do {
        minindex = 10000;
        min = 10000;
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
        if (minindex != 10000)
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
      } while (minindex < 10000);
      // Вывод кратчайших расстояний до вершин
      printf("\nКратчайшие расстояния до вершин: \n");
      for (int i = 0; i<SIZE; i++)
        printf("%5d ", d[i]);
      // Восстановление пути
      int ver[SIZE]; // массив посещенных вершин
      int end = 4; // индекс конечной вершины = 5 - 1
      ver[0] = end + 1; // начальный элемент - конечная вершина
      int k = 1; // индекс предыдущей вершины
      int weight = d[end]; // вес конечной вершины

      while (end > 0) // пока не дошли до начальной вершины
      {
        for(int i=0; i<SIZE; i++) // просматриваем все вершины
          if (a[end][i] != 0)   // если связь есть
          {
            int temp = weight - a[end][i]; // определяем вес пути из предыдущей вершины
            if (temp == d[i]) // если вес совпал с рассчитанным
            {                 // значит из этой вершины и был переход
              weight = temp; // сохраняем новый вес
              end = i;       // сохраняем предыдущую вершину
              ver[k] = i + 1; // и записываем ее в массив
              k++;
            }
          }
      }

    qDebug();

}
=======
Graph* Graph::add_vertex(Vertex vertex)
{
    this->vertexs->push_back(vertex);
    return this;
}

void Graph::delete_vertex(int vertex_id)
{
    for(auto iter = this->vertexs->begin();iter!=this->vertexs->end(); ++iter)
    {
        if(iter->get_id() == vertex_id)
            this->vertexs->erase(iter);
        break;
    }
}

Vertex Graph::add_edge(int id, Edge edge)
{
    for(auto iter = this->vertexs->begin();iter!=this->vertexs->end(); ++iter)
    {
        if(iter->get_id() == id)
            iter->add_edge(edge);
    }
}

void Graph::delete_edge(int vertex_id, int edge_id)
{
    for(auto iter = this->vertexs->begin();iter!=this->vertexs->end(); ++iter)
    {
        if(iter->get_id() == vertex_id)
            iter->delete_edge(edge_id);
    }
}

Graph::~Graph(){
    this->vertexs->clear();
    delete this->vertexs;
}

>>>>>>> 6b422697b80d99b33a34c31f8508fb73367344d4
