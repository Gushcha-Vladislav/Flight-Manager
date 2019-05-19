#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vertex.h>

class Graph {
    private:
        static int id;
        std::unordered_map<int, Vertex> vertexs;
    public:
        Graph();
        ~Graph();
        Graph(Vertex *vertexs);
        Vertex add_vertex(Vertex vertex);
        void delete_vertex(int id);
        Vertex add_edge(int id, Edge edge);
        void delete_edge(int id, Edge edge);
        void drow();
        std::string find_way();
        void serilization();
        void deserilization();
};
#endif // GRAPH_H
