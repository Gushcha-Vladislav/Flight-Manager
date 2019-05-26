#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "graph.h"
#include "vertex.h"

namespace Serializer
{
template <template <class> class V, class E>
class Serialize
{
public:
    void exportToJson(Graph<V,E> graph);
    void importFromJson();
    std::vector<E> getEdges;
    std::vector<V<E>> getVertex;
private:
    Serialize();
    std::vector<E> edges;
    std::vector<V<E>> vertex;
};
}
#endif // SERIALIZE_H
