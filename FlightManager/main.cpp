#include "mainwindow.h"
#include <QApplication>
#include "graph.h"
#include <QDebug>
#include "serialize.h"

int main(int argc, char *argv[])
{
    Graph<Vertex,Edge> *graph = new Graph<Vertex,Edge>();

    Serializer::Serialize<Graph<Vertex,Edge>>& serializer = Serializer::Serialize<Graph<Vertex,Edge>>::instance();
    serializer.importFromJson(graph);
    serializer.exportToJson(graph);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    return 0;
}
