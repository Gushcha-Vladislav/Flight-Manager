#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "graph.h"
#include "vertex.h"

namespace Serializer
{
class Serialize
{
public:
    void exportToJson(Graph graph);
    void importFromJson();
    std::vector<Edge> getEdges;
    std::vector<Vertex> getVertex;
private:
    Serialize();
    std::vector<Edge> edges;
    std::vector<Vertex> vertex;
};
}
#endif // SERIALIZE_H
