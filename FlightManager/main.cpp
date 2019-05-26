#include "mainwindow.h"
#include <QApplication>
#include "graph.h"
#include <QDebug>
#include "serialize.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();

    /*Edge *e35 = new Edge(5,8);
    Edge *e36 = new Edge(6,5);

    std::vector<Edge> *edges3 = new std::vector<Edge>();

    edges3->push_back(*e35);
    edges3->push_back(*e36);

    Edge *e53 = new Edge(3,4);
    Edge *e56 = new Edge(6,4);
    Edge *e58 = new Edge(8,3);

    std::vector<Edge>* edges5 = new std::vector<Edge>();

    edges5->push_back(*e53);
    edges5->push_back(*e56);
    edges5->push_back(*e58);

    Edge *e63 = new Edge(3,12);

    std::vector<Edge>* edges6 = new std::vector<Edge>();

    edges6->push_back(*e63);

    Edge *e85 = new Edge(5,1);
    Edge *e86 = new Edge(6,2);

    std::vector<Edge> *edges8 = new std::vector<Edge>();

    edges8->push_back(*e85);
    edges8->push_back(*e86);

    Vertex<Edge> *v0 = new Vertex<Edge>(3, "Vertex3", 3.0, 3.0, edges3);
    Vertex<Edge> *v1 = new Vertex<Edge>(5, "Vertex5", 3.0, 3.0, edges5);
    Vertex<Edge> *v2 = new Vertex<Edge>(6, "Vertex6", 3.0, 3.0, edges6);
    Vertex<Edge> *v3 = new Vertex<Edge>(8, "Vertex8", 3.0, 3.0, edges8);

    std::vector<Vertex<Edge>> *vertexes = new std::vector<Vertex<Edge>>();

    vertexes->push_back(*v0);
    vertexes->push_back(*v1);
    vertexes->push_back(*v2);
    vertexes->push_back(*v3);

    Graph<Vertex,Edge> * g = new Graph<Vertex,Edge> (vertexes);
    Iterator<Vertex<Edge>>* it = g->begin();
    qDebug() << it->get_value().get_id();
    it->next();
    qDebug() << it->get_value().get_id();*/
    Graph<Vertex,Edge> *graph = new Graph<Vertex,Edge>();
    Serializer::Serialize<Graph<Vertex,Edge>> *seria = new Serializer::Serialize<Graph<Vertex,Edge>>(graph);
    seria->exportToJson(graph);
    return 0;
}
