#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include "vertex.h"
#include "edge.h"
#include "graph.cpp"
#include "vertex.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Graph<Vertex,Edge> *graph = new Graph<Vertex,Edge>();
    graph->test();
    graph->~Graph();

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
