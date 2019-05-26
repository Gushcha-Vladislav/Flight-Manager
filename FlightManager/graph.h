#ifndef GRAPH_H
#define GRAPH_H

#include <vertex.h>

//template <template <class E> class V, class E>
class Graph {
    private:
        static int id;
        std::vector<Vertex> *vertices;
    public:
        Graph();
        Graph(std::vector<Vertex> *vertices);
        Graph* add_vertex(Vertex vertex);
        ~Graph();
        void delete_vertex(int vertex_id);
        Vertex add_edge(int vertex_id, Edge edge);
        void delete_edge(int vertex_id, int edge_id);
        void draw();
        std::string find_way(int from_id, int to_id);
        void serilization();
        void deserilization();
        void test();
//        std::vector<V<E>>* initTestVertexes();
};
#endif // GRAPH_H
