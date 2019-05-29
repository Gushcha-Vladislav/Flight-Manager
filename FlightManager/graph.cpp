#include <graph.h>
#include <QDebug>

struct Way {
    std::string name;
    int fly_time;
};

template< template<class E> class V, class E>
std::string GraphLib::Graph<V,E>::find_way(int from_id, int to_id)
{

   std::vector<V<E>,AllocatorLib::AllocImpl<V<E>>>* vertexes = this->vertices;

    int MAX_INT = 100000;
    int SIZE = vertices->size();
    int a[SIZE][SIZE]; // матрица связей
    int d[SIZE]; // минимальное расстояние
    int v[SIZE]; // посещенные вершины
    int temp;
    int minindex, min;

    int begin_vert_index = 0;
    int end_vert_index = 0;

    for(auto vert = vertices->begin();vert!=vertexes->end();++vert) {
        if ((begin_vert_index != 0) && (end_vert_index != 0)) break;

        if (vert->get_id() == from_id) {
            begin_vert_index = std::distance(vertices->begin(), vert);
        }
        if (vert->get_id() == to_id) {
            end_vert_index = std::distance(vertices->begin(), vert);
        }
    }

    if (end_vert_index == 0) {
        std::swap(vertices->at(0), vertices->at(begin_vert_index));
        end_vert_index = begin_vert_index;
    }

    std::swap(vertices->at(SIZE - 1), vertexes->at(end_vert_index));

    // Инициализация матрицы связей
    for (int i = 0; i<SIZE; i++)
    {

      for (int j = 0; j<SIZE; j++) {
          int temp_time = MAX_INT;
          if (i == j) {
              a[i][j] = 0;
              continue;
          }
          std::vector<E,AllocatorLib::AllocImpl<E>>* edges = vertexes->at(i).get_edges();
          int to_vert_id = vertexes->at(j).get_id();

          for(auto edge = edges->begin();edge!=edges->end();++edge) {
              if (edge->get_to_id() == to_vert_id)
                  if (edge->get_fly_time() < temp_time)
                    temp_time = edge->get_fly_time();
          }
          a[i][j] = (temp_time == MAX_INT) ? 0 : temp_time;
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
      std::vector<Way,AllocatorLib::AllocImpl<Way>>* way = new std::vector<Way,AllocatorLib::AllocImpl<Way>>();
      int end = SIZE - 1; // индекс конечной вершины = 5 - 1
      Way w;
      w.name = vertexes->at(end).get_name();
      way->push_back(w); //начальный элемент - конечная вершина
      int k = 1; // индекс предыдущей вершины
      int weight = d[end];
      qDebug() << "PPPP" << weight;
      int fullWeight = weight;// вес конечной вершины

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
              Way w;

              qDebug() << "weght for " << QString::fromStdString(vertices->at(i).get_name()) << weight;

              w.name = vertices->at(i).get_name();
              w.fly_time = fullWeight - weight;
              way->push_back(w);// сохраняем предыдущую вершину
              k++;
            }
          }

        if (end == SIZE - 1) return "No ways";
      }
      std::string fullWay = way->at(way->size() - 1).name+ "-> (" + std::to_string(way->at(way->size() - 1).fly_time) + ") -> " ;

      for(auto vert = way->rbegin() + 1;vert!=way->rend() - 1;vert++) {
        fullWay = fullWay+ vert->name + "-> (" + std::to_string(vert->fly_time) + ") -> " ;
      }

      fullWay = fullWay + way->at(0).name;

   return fullWay;
}
