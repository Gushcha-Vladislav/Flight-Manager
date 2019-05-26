#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>
#include <edge.h>
#include "allocimpl.h"

template <class E>
class Vertex{
    private:
        static int CURRENT_ID;
        int id;
        std::string name;
        double pos_x;
        double pos_y;
        std::vector<Edge,GraphLib::AllocImpl<Edge>> *edges;

     public:
        Vertex(std::string name, double pos_x, double pos_y){
            this->id = CURRENT_ID++;
            this->name = name;
            this->pos_x = pos_x;
            this->pos_y = pos_y;
            this->edges = new std::vector<Edge,GraphLib::AllocImpl<Edge>>;
        }

        Vertex(std::string name, double pos_x, double pos_y, std::vector<Edge,GraphLib::AllocImpl<Edge>>* edges){
            this->id = CURRENT_ID++;
            this->name = name;
            this->pos_x = pos_x;
            this->pos_y = pos_y;
            this->edges = edges;
        }

        Vertex(int id, std::string name, double pos_x, double pos_y){
            if (id > CURRENT_ID)    CURRENT_ID = id;
            this->id = id;
            this->name = name;
            this->pos_x = pos_x;
            this->pos_y = pos_y;
        }

        Vertex(int id, std::string name, double pos_x, double pos_y, std::vector<Edge,GraphLib::AllocImpl<Edge>>* edges){
            if (id > CURRENT_ID)    CURRENT_ID = id;
            this->id = id;
            this->name = name;
            this->pos_x = pos_x;
            this->pos_y = pos_y;
            this->edges = edges;
        }

        bool operator==(const Vertex<E> & v){
            return v.get_id() == this->get_id();
        }
        bool operator==(Vertex<E> * v){
            return v->get_id() == this->get_id();
        }
        bool operator!=(const Vertex<E> & v){
            return v.get_id() != this->get_id();
        }
        bool operator!=(Vertex<E>* v){
            return v->get_id() != this->get_id();
        }

        double get_pos_x(){
            return this->pos_x;
        }

        double get_pos_y(){
            return this->pos_y;
        }

        std::string get_name(){
            return this->name;
        }

        int get_id(){
            return this->id;
        }

        std::vector<Edge,GraphLib::AllocImpl<Edge>> get_edges(){
            return this->edges;
        }

        E* add_edge(E *edge){
            this->edges->push_back(*edge);
            return &this->edges->at(edges->size()-1);
        }

        void delete_edge(int edge_id){
            for(auto iter = this->edges->begin();iter!=this->edges->end(); ++iter)
            {
                if(iter->get_id() == edge_id)
                    this->edges->erase(iter);
                break;
            }
        }
};

template <class E>
int Vertex<E>::CURRENT_ID = 0;
#endif // VERTEX_H
