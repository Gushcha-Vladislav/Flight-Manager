#ifndef GRAPH_H
#define GRAPH_H

#include <vertex.h>

class Graph {
    private:
        static int id;
        std::vector<Vertex> *vertexs;
    public:
        Graph();
        Graph(std::vector<Vertex> *vertes);
        Graph* add_vertex(Vertex vertex);
        ~Graph();
        void delete_vertex(int vertex_id);
        Vertex add_edge(int id, Edge edge);
        void delete_edge(int id, int edge_id);
        void drow();
        std::string find_way();
        void serilization();
        void deserilization();
};
#endif // GRAPH_H
