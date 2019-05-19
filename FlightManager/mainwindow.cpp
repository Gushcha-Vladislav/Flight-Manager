#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    Graph *graph = new Graph();
//    graph->find_way(3, 8);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
