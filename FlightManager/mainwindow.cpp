#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Graph *graph = new Graph();
    graph->test();
    graph->~Graph();

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
