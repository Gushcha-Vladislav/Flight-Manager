#include <graph.h>

Graph::Graph()
{
    this->vertexs = new std::vector<Vertex>;
}

Graph::Graph(std::vector<Vertex> *vertes, int id)
{
    this->vertexs = vertes;
}
