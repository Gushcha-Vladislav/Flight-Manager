#include <graph.h>
#include <QDebug>
#include <QWidget>
#include <QGraphicsEllipseItem>
#include <QtMath>

template< template<class E> class V, class E>
QGraphicsScene* GraphLib::Graph<V,E>::draw(){
    QGraphicsScene *scene = new QGraphicsScene;
    auto pointer = new QPainterPath();
    QFont font;
    font.setPixelSize(25);
    const int R = 260;
    const int DIAM = 40;
    double angle = 0;
    for (auto it = this->vertices->begin(); it != this->vertices->end(); ++it){
        it->set_pos_x(R*sin(angle));
        it->set_pos_y(R*cos(angle));
        auto circle = new QGraphicsEllipseItem(it->get_pos_x(), it->get_pos_y(), DIAM,DIAM);
        angle+=2*M_PI/this->vertices->size();
        circle->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
        circle->setBrush(Qt::green);
        scene->addItem(circle);
        pointer->addText(it->get_pos_x()-DIAM,it->get_pos_y()+2*DIAM, font, QString::fromUtf8(it->get_name().c_str()));
    }

//    pointer->moveTo(-260,-260);
//    pointer->cubicTo(10,10, 100,100,260,260);
    scene->addPath(*pointer);
    return scene;
}

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
          int temp_time = 0;
          if (i == j) {
              a[i][j] = 0;
              continue;
          }
          std::vector<E,AllocatorLib::AllocImpl<E>>* edges = vertexes->at(i).get_edges();
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
      std::vector<std::string,AllocatorLib::AllocImpl<std::string>>* way = new std::vector<std::string,AllocatorLib::AllocImpl<std::string>>();
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

        if (end == SIZE - 1) return "No ways";
      }
      std::string fullWay = way->at(way->size() - 1);

      for(auto vert = way->rbegin() + 1;vert!=way->rend();vert++) {
        fullWay = fullWay + " -> " + vert->substr();
      }

   return fullWay;
}
