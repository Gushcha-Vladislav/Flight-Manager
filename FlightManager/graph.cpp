#include <graph.h>

Graph::Graph()
{
    this->vertexs = new std::unordered_map<int, Vertex>;
}

Graph::Graph(std::unordered_map<int, Vertex> *vertes, int id)
{
    this->vertexs = vertes;
}
