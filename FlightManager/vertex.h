#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>
#include <edge.h>

class Vertex{
    private:
        std::string name;
        double pos_x;
        double pos_y;
        std::vector<Edge> edges;

     public:
        Vertex(std::string name, double pos_x, double pos_y);
        Vertex(std::string name, double pos_x, double pos_y, std::vector<Edge> edges);
        double get_pos_x();
        double get_pos_y();
        std::string get_name();
        std::vector<Edge> getEdges();
};

#endif // VERTEX_H
