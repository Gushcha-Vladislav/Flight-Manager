#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "graph.h"
#include "edge.h"
#include "singleton.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QFile>
#include <QDebug>

namespace Serializer
{
template <class T>
class Serialize
{
public:
    void exportToJson(T* graph);
    void importFromJson(T* graph);
    Serialize(T* graph);
};
}

template <class T>
Serializer::Serialize<T>::Serialize(T* graph)
{
    importFromJson(graph);
}

template <class T>
void Serializer::Serialize<T>::exportToJson(T* graph){
    QJsonObject json;
    QJsonArray jVertices;
    for(auto iter = graph->getVertices()->begin();iter!=graph->getVertices()->end(); ++iter)
    {
        QJsonArray jEdges;
        QJsonObject obj;
        obj["id"] = iter->get_id();
        obj["name"] = QString::fromStdString(iter->get_name());
        obj["pos_x"] = iter->get_pos_x();
        obj["pos_y"] = iter->get_pos_y();
        for(auto iterEdge = iter->get_edges()->begin();iterEdge!=iter->get_edges()->end(); ++iterEdge)
        {
            QJsonObject edge;
            edge["id"] = iterEdge->get_id();
            edge["to_id"] = iterEdge->get_to_id();
            edge["fly_time"] = iterEdge->get_fly_time();
            jEdges.push_back(edge);
        }
        obj["edges"] = jEdges;
        jVertices.push_back(obj);
    }
    json["vertices"] = jVertices;

    QJsonDocument json_doc(json);
    QString json_string = json_doc.toJson();
    QString path = "../FlightManager/graph.json";
    QFile save_file(path);
    if (save_file.exists())
        save_file.remove();
    if (!save_file.open(QIODevice::WriteOnly)) {
        //throw exception
        qDebug()<<"pukexp";
    }
    save_file.write(json_string.toLocal8Bit());
    save_file.close();
}

template <class T>
void Serializer::Serialize<T>::importFromJson(T* graph){
    QFile file("../FlightManager/graph.json");
    if (!file.open(QIODevice::ReadOnly)) {
        //throw exception
        qDebug()<<"pukimp"<<endl;
    }
    QByteArray rawData = file.readAll();
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(rawData));
    QJsonObject json = doc.object();
    QJsonArray jVertices = json["vertices"].toArray();
    QJsonArray jEdges;
    for(auto iter = jVertices.begin();iter!=jVertices.end(); ++iter)
    {
        QJsonObject obj = iter->toObject();
        graph->add_vertex(new Vertex<Edge>(obj["id"].toInt(),obj["name"].toString().toStdString(),obj["pos_x"].toDouble(),obj["pos_y"].toDouble()));
        jEdges = obj["edges"].toArray();
        for(auto iter = jEdges.begin();iter!=jEdges.end(); ++iter)
        {
            QJsonObject objEdges = iter->toObject();
            graph->add_edge(obj["id"].toInt(),new Edge(objEdges["id"].toInt(),objEdges["to_id"].toInt(),objEdges["fly_time"].toInt()));
        }
    }
}

#endif // SERIALIZE_H
