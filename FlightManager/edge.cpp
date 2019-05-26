#include <edge.h>
int Edge::CURRENT_ID = 0;

Edge::Edge(int to_id, int fly_time)
{
    this->id = CURRENT_ID++;
    this->to_id = to_id;
    this->fly_time = fly_time;
};

Edge::Edge(int id, int to_id, int fly_time)
{
    if (id > CURRENT_ID)    CURRENT_ID = id;
    this->id = CURRENT_ID;
    this->to_id = to_id;
    this->fly_time = fly_time;
};

int Edge::get_to_id(){
    return this->to_id;
};
int Edge::get_fly_time(){
    return this->fly_time;
};

int Edge::get_id(){
    return this->id;
};

