#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "graph.h"
#include "vertex.h"

namespace Serializer
{
class Serialize
{
public:
    void exportToJson(Graph<Vertex<Edge>> graph);
    void importFromJson();
    std::vector<Edge> getEdges;
    std::vector<Vertex<Edge>> getVertex;
private:
    Serialize();
    std::vector<Edge> edges;
    std::vector<Vertex<Edge>> vertex;
};
}
#endif // SERIALIZE_H
