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
    const int R = 240;
    const int DIAM = 30;
    double angle = 0;
    for (auto it = this->vertices->begin(); it != this->vertices->end(); ++it){
        it->set_pos_x(R*sin(angle));
        it->set_pos_y(R*cos(angle));
        it->set_wait_pos_x(23 * sin(angle+M_PI) + it->get_pos_x());
        it->set_wait_pos_y(23 * cos(angle+M_PI) + it->get_pos_y());
        auto circle = new QGraphicsEllipseItem(it->get_pos_x()-DIAM/2, it->get_pos_y()-DIAM/2, DIAM,DIAM);
        angle+=2*M_PI/this->vertices->size();
        circle->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
        circle->setBrush(Qt::green);
        scene->addItem(circle);
        pointer->addText(it->get_pos_x()-DIAM,it->get_pos_y()+2*DIAM, font, QString::fromUtf8(it->get_name().c_str()));
    }

    for (auto it = this->vertices->begin(); it != this->vertices->end(); ++it){
        int i = 1;
        for (auto ed = it->get_edges()->begin(); ed != it->get_edges()->end(); ++ed, i++){
            auto curr = getVertex(ed->get_to_id());
            double x2,y2;
            if(curr!=nullptr){
                if(it->get_pos_y() < curr->get_pos_y() && abs(it->get_pos_y() - curr->get_pos_y())>1){
                    if(abs(it->get_pos_x() - curr->get_pos_x())<=1){
                        x2 = it->get_pos_x() + 20*i;
                        y2 = it->get_pos_y() + (curr->get_pos_y() - it->get_pos_y())/2;

                    }
                    if(abs(it->get_pos_x() - curr->get_pos_x())>1 && it->get_pos_x() < curr->get_pos_x() ){
                        x2 = it->get_pos_x() +(curr->get_pos_x() - it->get_pos_x())/2 + (curr->get_pos_y() - it->get_pos_y())/10*i;
                        y2 = it->get_pos_y() +(curr->get_pos_y() - it->get_pos_y())/2 - (curr->get_pos_x() - it->get_pos_x())/10*i;
                    }
                    if(abs(it->get_pos_x() - curr->get_pos_x())>1 && it->get_pos_x() > curr->get_pos_x() ){
                        x2 =it->get_pos_x() +(curr->get_pos_x() - it->get_pos_x())/2 + (curr->get_pos_y() - it->get_pos_y())/10*i;
                        y2 = it->get_pos_y() +(curr->get_pos_y() - it->get_pos_y())/2+ (curr->get_pos_x() - it->get_pos_x())/10*i;
                    }
                }
                if(it->get_pos_y() > curr->get_pos_y() && abs(it->get_pos_y() - curr->get_pos_y())>1){
                    if(abs(it->get_pos_x() - curr->get_pos_x())<1){
                        x2 = it->get_pos_x()- 20 * i;
                        y2 = it->get_pos_y() + (curr->get_pos_y() - it->get_pos_y())/2;

                    }
                    if(abs(it->get_pos_x() - curr->get_pos_x())>1 && it->get_pos_x() < curr->get_pos_x() ){
                        x2 =it->get_pos_x() +(curr->get_pos_x() - it->get_pos_x())/2 + (curr->get_pos_y() - it->get_pos_y())/10*i;
                        y2 = it->get_pos_y() +(curr->get_pos_y() - it->get_pos_y())/2+ (curr->get_pos_x() - it->get_pos_x())/10*i;
                    }
                    if(abs(it->get_pos_x() - curr->get_pos_x())>1 && it->get_pos_x() > curr->get_pos_x() ){
                        x2 =it->get_pos_x() +(curr->get_pos_x() - it->get_pos_x())/2 - (curr->get_pos_y() - it->get_pos_y())/10*i;
                        y2 = it->get_pos_y() +(curr->get_pos_y() - it->get_pos_y())/2+ (curr->get_pos_x() - it->get_pos_x())/10*i;
                    }
                }
                if(abs(it->get_pos_y() - curr->get_pos_y())<=1){
                    if(it->get_pos_x() > curr->get_pos_x()){
                        x2 = it->get_pos_x() - (it->get_pos_x() - curr->get_pos_x())/2;
                        y2 = it->get_pos_y() + 20*i;

                    }else{
                        x2 = it->get_pos_x() + (curr->get_pos_x() - it->get_pos_x())/2;
                        y2 = it->get_pos_y() + 20*i;
                    }
                }
                pointer->moveTo(it->get_pos_x(),it->get_pos_y());
                pointer->cubicTo(it->get_pos_x(),it->get_pos_y(),x2,y2,curr->get_wait_pos_x(),curr->get_wait_pos_y());
                auto circle =  new QGraphicsEllipseItem(curr->get_wait_pos_x()-5, curr->get_wait_pos_y()-5, 10,10);
                circle->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
                circle->setBrush(Qt::green);
                scene->addItem(circle);
                //            pointer->addText(it->get_pos_x()-DIAM,it->get_pos_y()+2*DIAM, font, QString::fromUtf8(it->get_name().c_str()));
            }
        }}

    scene->addPath(*pointer);
    return scene;
}

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
    int fullWeight = weight;// вес конечной вершины

    while (end > 0) // пока не дошли до начальной вершины
    {
        for(int i=0; i<SIZE; i++) // просматриваем все вершины

            if (a[i][end] != 0)   // если связь есть
            {
                int temp = weight - a[i][end]; // определяем вес пути из предыдущей вершины
                if (temp == d[i]) // если вес совпал с рассчитанным
                {
                    int kek = a[i][end];
                    weight = temp; // сохраняем новый вес
                    end = i;
                    Way w;
                    w.name = vertices->at(i).get_name();
                    w.fly_time = kek;
                    way->push_back(w);// сохраняем предыдущую вершину
                    k++;
                }
            }

        if (end == SIZE - 1) return "No ways";
    }
    std::string fullWay = "";

    for(auto vert = way->rbegin() ;vert!=way->rend() - 1;vert++) {
        fullWay = fullWay+ vert->name + "-> (" + std::to_string(vert->fly_time) + ") -> " ;
    }

    fullWay = fullWay + way->at(0).name + "\nFull way: " + std::to_string(fullWeight);

    return fullWay;
}
