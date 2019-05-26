#ifndef GRAPH_H
#define GRAPH_H

#include <vertex.h>

template <template <class E> class V, class E>
class Graph {
    private:
        static int id;
        std::vector<V<E>> *vertices;
    public:
        Graph();
        Graph(std::vector<V<E>> *vertices);
        Graph* add_vertex(V<E> vertex);
        ~Graph();
        void delete_vertex(int vertex_id);
        V<E> add_edge(int vertex_id, E edge);
        void delete_edge(int vertex_id, int edge_id);
        void draw();
        std::string find_way(int from_id, int to_id);
        void serilization();
        void deserilization();
        void test();
//        std::vector<V<E>>* initTestVertexes();
};
#endif // GRAPH_H
