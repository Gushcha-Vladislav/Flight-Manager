#include <vertex.h>

Vertex::Vertex(std::string name, double pos_x, double pos_y)
{
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
