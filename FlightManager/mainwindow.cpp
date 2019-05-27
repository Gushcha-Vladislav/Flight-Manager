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
    graph = new Graph<Vertex,Edge>();

    Serializer::Serialize<Graph<Vertex,Edge>>& serializer = Serializer::Serialize<Graph<Vertex,Edge>>::instance();
    serializer.importFromJson(graph);

    ui->setupUi(this);

    for(auto iter = graph->getVertices()->begin();iter!=graph->getVertices()->end(); ++iter)
    {
        ui->vertexFrom->addItem(QString::fromStdString(iter->get_name()));
        ui->vertexTo->addItem(QString::fromStdString(iter->get_name()));
    }
    ui->flyTimeBox->setButtonSymbols( QAbstractSpinBox::NoButtons );

};
MainWindow::~MainWindow()
{
    Serializer::Serialize<Graph<Vertex,Edge>>& serializer = Serializer::Serialize<Graph<Vertex,Edge>>::instance();
    serializer.exportToJson(graph);
    delete ui;
};

void MainWindow::on_vertexAddPushButton_clicked()
{
    QString vertexName = ui->VertexNameLine->text();
    graph->add_vertex(new Vertex<Edge>(vertexName.toStdString(),1.1,2.2));//нужен конструктор без координат или что-то подобное
    ui->vertexFrom->addItem(ui->VertexNameLine->text());
    ui->vertexTo->addItem(ui->VertexNameLine->text());
}

void MainWindow::on_addEdgePushButton_clicked()//где-то здесь косяк
{
    int from_id, to_id;
    for(auto iter = graph->getVertices()->begin();iter!=graph->getVertices()->end(); ++iter)
    {
        if(!iter->get_name().compare(ui->vertexFrom->currentText().toStdString())){
            from_id = iter->get_id();
        }
        else if(!iter->get_name().compare(ui->vertexTo->currentText().toStdString())){
            to_id = iter->get_id();
        }
    }
    graph->add_edge(from_id,new Edge(to_id,ui->flyTimeBox->text().toInt()));
}
