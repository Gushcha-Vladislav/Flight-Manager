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
        ui->deleteVertex->addItem(QString::fromStdString(iter->get_name()));
        ui->vertexFromDel->addItem(QString::fromStdString(iter->get_name()));
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
    ui->deleteVertex->addItem(ui->VertexNameLine->text());
    ui->vertexFromDel->addItem(ui->VertexNameLine->text());
    ui->VertexNameLine->clear();
}

void MainWindow::on_addEdgePushButton_clicked()//где-то здесь косяк
{
    int from_id=-1, to_id=-1;
    from_id = graph->getVertex(ui->vertexFrom->currentText().toStdString())->get_id();
    to_id = graph->getVertex(ui->vertexTo->currentText().toStdString())->get_id();
    if((from_id==-1)||(to_id==-1)){
        QMessageBox::information(0, "Ошибка", "Вершины не найдены!");
    }
    else{
        graph->add_edge(from_id,new Edge(to_id,ui->flyTimeBox->text().toInt()));
    }
}

void MainWindow::on_deleteVertexPushButton_clicked()
{
    for(auto iter = graph->getVertices()->begin();iter!=graph->getVertices()->end(); ++iter)
    {
        if(!iter->get_name().compare(ui->deleteVertex->currentText().toStdString())){
            ui->vertexFrom->removeItem(ui->deleteVertex->currentIndex());
            ui->vertexTo->removeItem(ui->deleteVertex->currentIndex());
            ui->vertexFromDel->removeItem(ui->deleteVertex->currentIndex());
            ui->deleteVertex->removeItem(ui->deleteVertex->currentIndex());
            graph->delete_vertex(iter->get_id());
            break;
        }
    }
}

void MainWindow::on_vertexFromDel_currentIndexChanged(int index)
{
    QString tmpstr;
    ui->edgeSelecter->clear();
    vertexNameDel.clear();
    flyTimeDel.clear();
    for(auto iter = graph->getVertex(ui->vertexFromDel->currentText().toStdString())->get_edges()->begin();iter!=graph->getVertex(ui->vertexFromDel->currentText().toStdString())->get_edges()->end(); ++iter)
    {
        vertexNameDel.push_back(graph->getVertex(iter->get_to_id())->get_name());
        flyTimeDel.push_back(iter->get_fly_time());
        tmpstr = "TO: " + QString::fromStdString(graph->getVertex(iter->get_to_id())->get_name()) + ", fly time: " + QString::number(iter->get_fly_time());
        ui->edgeSelecter->addItem(tmpstr);
    }
}

void MainWindow::on_deleteEdgePushButton_clicked()
{
    qDebug()<<QString::fromStdString(vertexNameDel[ui->edgeSelecter->currentIndex()]);
    qDebug()<<QString::number(flyTimeDel[ui->edgeSelecter->currentIndex()]);
    graph->getVertex(ui->vertexFromDel->currentText().toStdString());
}
