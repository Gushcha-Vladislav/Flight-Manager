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

    Graph<Vertex,Edge> *graph = new Graph<Vertex,Edge>();
    Serializer::Serialize<Graph<Vertex,Edge>> *seria = new Serializer::Serialize<Graph<Vertex,Edge>>(graph);
    seria->exportToJson(graph);
    return 0;
}
