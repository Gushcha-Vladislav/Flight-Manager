#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <unordered_set>
#include <edge.h>

class Vertex{
    private:
        std::string name;
        double pos_x;
        double pos_y;
        std::unordered_set<Edge> edges;

     public:
        Vertex(std::string name, double pos_y, double pos_x);
        Vertex(std::string name, double pos_y, double pos_x, std::unordered_set<Edge> edges);
        double get_pos_x();
        double get_pos_y();
        std::string get_name();
        std::unordered_set<Edge> getEdges();
};

#endif // VERTEX_H
