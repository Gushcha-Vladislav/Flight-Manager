#ifndef GRAPH_H
#define GRAPH_H

#include <vertex.h>
#include <iterator.h>
#include <iostream>
#include "exceptions.h"

template< template<class E> class V, class E>
class Graph {
    private:
        std::vector<V<E>,GraphLib::AllocImpl<V<E>>> *vertices;

    public:
        Graph(){
            this->vertices = new std::vector<V<E>,GraphLib::AllocImpl<V<E>>>;
        }

        Graph( std::vector<int,GraphLib::AllocImpl<V<E>>> vertices){
            this->vertices = vertices;
        }

        V<E> add_vertex(V<E>* vertex){
            this->vertices->push_back(*vertex);
            return this->vertices->at(this->vertices->size()-1);
        }

        ~Graph(){
            this->vertices->clear();
            delete this->vertices;
        }

        void delete_vertex(int vertex_id){
            for(auto iter = this->vertices->begin();iter!=this->vertices->end(); ++iter)
            {
                if(iter->get_id() == vertex_id){
                    this->vertices->erase(iter);
                    break;
                }
            }
        }

        bool add_edge(int vertex_id, E *edge){
            if (vertex_id!=edge->get_to_id()){
                for(auto iter = this->vertices->begin();iter!=this->vertices->end(); ++iter)
                {
                    if(iter->get_id() == vertex_id){
                        iter->add_edge(edge);
                        return true;
                    }
                }
            }
            else {
                throw EdgeLoopException(std::to_string(edge->get_id()));
            }

        }

        void delete_edge(int vertex_id, int edge_id){
            for(auto iter = this->vertices->begin();iter!=this->vertices->end(); ++iter)
            {
                if(iter->get_id() == vertex_id)
                    iter->delete_edge(edge_id);
            }
        }

        V<E> *getVertex(int vertex_id){
            int i = 0;
            for(auto iter = this->vertices->begin();iter!=this->vertices->end(); ++iter,i++)
            {
                if(iter->get_id() == vertex_id){
                    return &this->vertices->at(i);
                }
            }
        }

        V<E> *getVertex(std::string vertex_name){
            int i = 0;
            for(auto iter = this->vertices->begin();iter!=this->vertices->end(); ++iter,i++)
            {
                if(!iter->get_name().compare(vertex_name)){
                    return &this->vertices->at(i);
                }
            }
        }

        std::vector<V<E>,GraphLib::AllocImpl<V<E>>>* getVertices(){
            return this->vertices;
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
