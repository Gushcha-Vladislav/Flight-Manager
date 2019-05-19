#include <edge.h>

Edge::Edge(int to_id, int fly_time)
{
    this->to_id = to_id;
    this->fly_time = fly_time;
}

int Edge::get_to_id(){
    return this->to_id;
}
int Edge::get_fly_time(){
    return this->fly_time;
}
