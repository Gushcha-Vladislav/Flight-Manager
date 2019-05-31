#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>
#include <edge.h>
#include "allocimpl.h"
#include "exceptions.h"

template <class E>
class Vertex{
    private:
        static int CURRENT_ID;
        int id;
        std::string name;
        double pos_x;
        double pos_y;
        double wait_pos_x;
        double wait_pos_y;
        std::vector<Edge,AllocatorLib::AllocImpl<Edge>> *edges;

     public:
        Vertex(std::string name, double pos_x, double pos_y){
            this->id = ++CURRENT_ID;
            this->name = name;
            this->pos_x = pos_x;
            this->pos_y = pos_y;
            this->edges = new std::vector<Edge,AllocatorLib::AllocImpl<Edge>>;
        }

        Vertex(int id, std::string name, double pos_x, double pos_y){
            if (id > CURRENT_ID)    CURRENT_ID = id;
            this->id = id;
            this->name = name;
            this->pos_x = pos_x;
            this->pos_y = pos_y;
            this->edges = new std::vector<Edge,AllocatorLib::AllocImpl<Edge>>;
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

        void set_pos_x(double x){
            this->pos_x = x;
        }

        void set_pos_y(double y){
            this->pos_y = y;
        }

        double get_wait_pos_x(){
            return this->wait_pos_x;
        }

        double get_wait_pos_y(){
            return this->wait_pos_y;
        }

        void set_wait_pos_x(double x){
            this->wait_pos_x = x;
        }

        void set_wait_pos_y(double y){
            this->wait_pos_y = y;
        }
        std::string get_name(){
            return this->name;
        }

        int get_id(){
            return this->id;
        }

        std::vector<Edge,AllocatorLib::AllocImpl<Edge>>* get_edges(){
            return this->edges;
        }

        E add_edge(E *edge){
            this->edges->push_back(*edge);
            return this->edges->at(edges->size()-1);
        }

        void delete_edge(int edge_id){
            for(auto iter = this->edges->begin();iter!=this->edges->end(); ++iter)
            {
                if(iter->get_id() == edge_id)
                    this->edges->erase(iter);
                break;
            }
        }
        bool delete_edge(int to_id, int fly_time){
            for(auto iter = this->edges->begin();iter!=this->edges->end(); ++iter)
            {
                if((iter->get_to_id() == to_id) && (iter->get_fly_time() == fly_time)){
                    this->edges->erase(iter);
                    return true;
                }
            }
            throw EdgeDeletingException(to_id,fly_time);
        }

};

template <class E>
int Vertex<E>::CURRENT_ID = 0;
#endif // VERTEX_H
