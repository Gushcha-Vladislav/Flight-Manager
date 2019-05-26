#ifndef GRAPH_H
#define GRAPH_H

#include <vertex.h>
#include <iterator.h>
#include <iostream>

template< template<class E> class V, class E>
class Graph {
    private:
        static int id;
        std::vector<V<E>,GraphLib::AllocImpl<V<E>>> *vertices;
    public:
        Graph(){
            this->vertices = new std::vector<V<E>,GraphLib::AllocImpl<V<E>>>;
        }

        Graph( std::vector<int,GraphLib::AllocImpl<V<E>>> vertices){
            this->vertices = vertices;
        }

        Graph* add_vertex(V<E>* vertex){
            this->vertices->push_back(*vertex);
            return this;
        }

        ~Graph(){
            this->vertices->clear();
            delete this->vertices;
        }

        void delete_vertex(int vertex_id){
            for(auto iter = this->vertices->begin();iter!=this->vertices->end(); ++iter)
            {
                if(iter->get_id() == vertex_id)
                    this->vertices->erase(iter);
                break;
            }
        }

        V<E> add_edge(int id, E *edge){
            for(auto iter = this->vertices->begin();iter!=this->vertices->end(); ++iter)
            {
                if(iter->get_id() == id)
                    iter->add_edge(edge);
            }
        }

        void delete_edge(int vertex_id, int edge_id){
            for(auto iter = this->vertices->begin();iter!=this->vertices->end(); ++iter)
            {
                if(iter->get_id() == vertex_id)
                    iter->delete_edge(edge_id);
            }
        }

        void drow(){

        }
        std::string find_way(int from_id, int to_id);

        typedef Iterator<V<E>>* iterator;

        iterator begin(){
            return new Iterator<V<E>>(vertices, 0);
        }
        iterator end(){
            return new Iterator<V<E>>(this->vertices, this->vertices->size());
        }
    private:
};

#include <graph.cpp>
#endif // GRAPH_H
