#ifndef INVARIANT_H
#define INVARIANT_H

template<class G>
class Invariant
{
public:
    Invariant();
    ~Invariant(){}

    static bool loopChecker(int from_id, int to_id){
        return (from_id == to_id) ? false : true;
    }
    static bool edgeHasEnd(G *graph, int to_id){
        for(auto iter = graph->getVertices()->begin();iter!=graph->getVertices()->end(); ++iter)
        {
            if(iter->get_id() == to_id){
                return true;
            }
        }
        return false;
    }
};

#endif // INVARIANT_H
