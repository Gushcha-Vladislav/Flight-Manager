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

}

template <class T>
void Serializer::Serialize<T>::importFromJson(T* graph){
    QFile file("../FlightManager/graph.json");
    //QDir::currentPath()
    if (!file.open(QIODevice::ReadOnly)) {
        //throw exception
        qDebug()<<"puk"<<endl;
    }
    QByteArray rawData = file.readAll();
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(rawData));
    QJsonObject json = doc.object();
    //qDebug()<<json["vertices"].toArray();
    QJsonArray jVertices = json["vertices"].toArray();
    QJsonArray jEdges;
    for(auto iter = jVertices.begin();iter!=jVertices.end(); ++iter)
    {
        QJsonObject obj = iter->toObject();

        qDebug()<<"vertex id:"<<obj["id"].toInt();
        qDebug()<<"name"<<obj["name"].toString();
        qDebug()<<"pos_x"<<obj["pos_x"].toDouble();
        qDebug()<<"pos_y"<<obj["pos_y"].toDouble();
        graph->add_vertex(new Vertex<Edge>(obj["id"].toInt(),obj["name"].toString().toStdString(),obj["pos_x"].toDouble(),obj["pos_y"].toDouble()));
        jEdges = obj["edges"].toArray();
        for(auto iter = jEdges.begin();iter!=jEdges.end(); ++iter)
        {
            QJsonObject objEdges = iter->toObject();
            qDebug()<<"edge id:"<<objEdges["id"].toInt();
            qDebug()<<"to id:"<<objEdges["to_id"].toInt();
            qDebug()<<"fly time"<<objEdges["fly_time"].toInt();
            graph->add_edge(obj["id"].toInt(),new Edge(objEdges["id"].toInt(),objEdges["to_id"].toInt(),objEdges["fly_time"].toInt()));
        }
    }

    qDebug()<<"All done";
}

#endif // SERIALIZE_H
