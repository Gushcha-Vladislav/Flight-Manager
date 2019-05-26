#include <vertex.h>

template <class E>
int Vertex<E>::CURRENT_ID = 0;

template <class E>
Vertex<E>::Vertex(std::string name, double pos_x, double pos_y)
{
    this->id = CURRENT_ID++;
    this->name = name;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->edges = new std::vector<E>;
}


template <class E>
Vertex<E>::Vertex(std::string name, double pos_x, double pos_y, std::vector<E> *edges)
{
    Vertex(name,pos_x,pos_y);
    this->edges = edges;
}

template <class E>
Vertex<E>::Vertex(int id, std::string name, double pos_x, double pos_y, std::vector<E> *edges)
{
    if (id > CURRENT_ID)    CURRENT_ID = id;
    this->id = id;
    this->name = name;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->edges = edges;
}

template <class E>
double Vertex<E>::get_pos_x()
{
    return this->pos_x;
}

template <class E>
double Vertex<E>::get_pos_y()
{
    return this->pos_y;
}

template <class E>
std::string Vertex<E>::get_name()
{
        return this->name;
}

template <class E>
std::vector<E>* Vertex<E>::get_edges()
{
            return this->edges;
}

template <class E>
Vertex<E>* Vertex<E>::add_edge(E edge)
{
    for(auto iter = this->edges->begin();iter!=this->edges->end(); ++iter)
    {
        if(iter->get_id() == edge.get_id()){
            this->edges->erase(iter);
            break;
        }
    }
    this->edges->push_back(edge);
    return this;
}

template <class E>
int Vertex<E>::get_id()
{
    return this->id;
}

template <class E>
void Vertex<E>::delete_edge(int edge_id){
    for(auto iter = this->edges->begin();iter!=this->edges->end(); ++iter)
    {
        if(iter->get_id() == edge_id){
            this->edges->erase(iter);
            break;
        }
    }
}

//template < class E>

// Попробовать вернуть, когда будут использоватьне НЕ тестовые данные
//Vertex<E>::~Vertex(){
//    this->edges->clear();
//    delete this->edges;
//}

//}
