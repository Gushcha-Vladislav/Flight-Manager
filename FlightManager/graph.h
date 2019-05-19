#ifndef GRAPH_H
#define GRAPH_H

#include <vertex.h>

class Graph {
    private:
        static int id;
        std::vector<Vertex> *vertexs;
    public:
        Graph();
        Graph(std::vector<Vertex> *vertes, int id);
        Vertex add_vertex(Vertex vertex);
        void delete_vertex(int id);
        Vertex add_edge(int id, Edge edge);
        void delete_edge(int id, Edge edge);
        void drow();
        std::string find_way(int from_id, int to_id);
        void serilization();
        void deserilization();
};
#endif // GRAPH_H
