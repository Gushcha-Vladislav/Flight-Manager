#include <graph.h>

Graph::Graph()
{
    this->vertexs = new std::vector<Vertex>;
}

Graph::Graph(std::vector<Vertex> *vertes)
{
    this->vertexs = vertes;
}

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

