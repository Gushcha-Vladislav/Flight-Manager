#ifndef GRAPH_H
#define GRAPH_H

#include <vertex.cpp>
#include <iterator.h>

template<class V>
class Graph {
    private:
        static int id;
        std::vector<V> *vertices;
    public:
        Graph();
        Graph( std::vector<V> *vertices);
        Graph* add_vertex(V *vertex);
        ~Graph();
        void delete_vertex(int vertex_id);
        V add_edge(int id, Edge edge);
        void delete_edge(int id, int edge_id);
        void drow();
        std::string find_way(int from_id, int to_id);
        void serilization();
        void deserilization();

        typedef Iterator<V> iterator;
        typedef Iterator<const V> const_iterator;

        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;
    private:
};
#endif // GRAPH_H
