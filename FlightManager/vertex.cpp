#include <vertex.h>

int Vertex::CURRENT_ID = 0;

Vertex::Vertex(std::string name, double pos_x, double pos_y)
{
    this->id = CURRENT_ID++;
    this->name = name;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->edges = new std::vector<Edge>;
}

Vertex::Vertex(std::string name, double pos_x, double pos_y, std::vector<Edge> *edges)
{
    Vertex(name,pos_x,pos_y);
    this->edges = edges;
}

Vertex::Vertex(int id, std::string name, double pos_x, double pos_y, std::vector<Edge> *edges)
{
    if (id > CURRENT_ID)    CURRENT_ID = id;
    this->id = id;
    this->name = name;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->edges = edges;
}

double Vertex::get_pos_x()
{
    return this->pos_x;
}

double Vertex::get_pos_y()
{
    return this->pos_y;
}

std::string Vertex::get_name()
{
        return this->name;
}

std::vector<Edge>* Vertex::get_edges()
{
            return this->edges;
}

Vertex* Vertex::add_edge(Edge edge)
{
    this->edges->push_back(edge);
    return this;
}

int Vertex::get_id()
{
    return this->id;
}

void Vertex::delete_edge(int edge_id){
    for(auto iter = this->edges->begin();iter!=this->edges->end(); ++iter)
    {
        if(iter->get_id() == edge_id)
            this->edges->erase(iter);
        break;
    }
}
