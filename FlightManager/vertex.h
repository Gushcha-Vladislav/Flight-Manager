#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>
#include <edge.h>

//template < class E>
class Vertex{
    private:
        static int CURRENT_ID;
        int id;
        std::string name;
        double pos_x;
        double pos_y;
        std::vector<Edge> *edges;

     public:
        Vertex(std::string name, double pos_x, double pos_y);
        Vertex(std::string name, double pos_x, double pos_y, std::vector<Edge> *edges);
        Vertex(int id, std::string name, double pos_x, double pos_y, std::vector<Edge> *edges);
        // Попробовать вернуть, когда будут использоватьне НЕ тестовые данные
//        ~Vertex();
        double get_pos_x();
        double get_pos_y();
        std::string get_name();
        int get_id();
        std::vector<Edge>* get_edges();
        Vertex* add_edge(Edge edge);
        void delete_edge(int edge_id);
};

#endif // VERTEX_H
