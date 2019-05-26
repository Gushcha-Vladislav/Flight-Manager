#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include "vertex.h"
#include "edge.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Graph<Vertex,Edge> *graph = new Graph<Vertex,Edge>();
    graph->~Graph();

    ui->setupUi(this);
};
MainWindow::~MainWindow()
{
    delete ui;
};
