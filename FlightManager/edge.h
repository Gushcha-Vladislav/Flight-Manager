#ifndef EDGE_H
#define EDGE_H

class Edge{
    private :
        int to_id;
        int fly_time;
    public :
        Edge(int to_id, int fly_time);
        int get_to_id();
        int get_fly_time();
};

#endif // EDGE_H
