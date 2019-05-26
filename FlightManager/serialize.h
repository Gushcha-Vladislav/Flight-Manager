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
//class Serialize: public Singleton<Serialize<T>>
class Serialize
{
public:
    void exportToJson(T graph);
    void importFromJson(T graph);
    Serialize(T graph);
    //std::vector<E> getEdges();
    //std::vector<V<E>> getVertices();
    //private:
    //friend class Singleton<Serialize<T>>;

    //std::vector<E> edges;
    //std::vector<V<E>> vertices;
};
}

template <class T>
Serializer::Serialize<T>::Serialize(T graph)
{
    importFromJson(graph);
}

template <class T>
void Serializer::Serialize<T>::exportToJson(T graph){

}

template <class T>
void Serializer::Serialize<T>::importFromJson(T graph){
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
    for(auto iter = jVertices.begin();iter!=jVertices.end(); ++iter)
    {
        //qDebug()<<iter<<endl;
    }





    /*QJsonDocument jsonResponse = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jEdges = jsonObject["Edges"].toArray();
    QJsonArray jVertices = jsonObject["Vertices"].toArray();

    //edges.clear();
    //vertices.clear();

    qDebug()<<jEdges<<endl;
    qDebug()<<jVertices<<endl;
    /*Vertex *propertyVertex;
        foreach (const QJsonValue &value, jVertices) {
            QJsonObject obj = value.toObject();
            propertyVertex = obj["vertex"].toString();
            vertices.push_back(propertyVertex.toStdString());
        }

        QString propertyFrom;
        QString propertyTo;
        foreach (const QJsonValue &value, jEdges) {
            QJsonObject obj = value.toObject();
            propertyFrom = obj["from"].toString();
            propertyTo = obj["to"].toString();
            edges.push_back(std::make_pair(propertyFrom.toStdString(), propertyTo.toStdString()));
        }*/
}

/*template <template <class E> class V, class E>
std::vector<E> Serializer::Serialize<V,E>::getEdges()
{
    return edges;
}

template <template <class E> class V, class E>
std::vector<V<E>> Serializer::Serialize<V,E>::getVertices()
{
    return vertices;
}*/

#endif // SERIALIZE_H
