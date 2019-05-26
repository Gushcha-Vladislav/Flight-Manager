#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include "vertex.h"
#include "edge.h"
#include "serialize.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Graph<Vertex,Edge> *graph = new Graph<Vertex,Edge>();
    graph->~Graph();
    Serializer::Serialize<Graph<Vertex,Edge>> *seria = new Serializer::Serialize<Graph<Vertex,Edge>>(graph);
    //Serializer::Serialize<Graph<Vertex,Edge>>::getInstance().importFromJson(*graph);

    ui->setupUi(this);
};
MainWindow::~MainWindow()
{
    delete ui;
};
