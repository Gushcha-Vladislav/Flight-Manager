#include <graph.h>

Graph::Graph(){
    this->vertexs = new std::unordered_map<int, Vertex>;
    this->id = 0;
}
Graph::Graph(Vertex *vertexs){
    this->vertexs = vertexs;
    this->id = 0;
}
