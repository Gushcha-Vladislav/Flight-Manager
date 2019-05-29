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
    graph = new GraphLib::Graph<Vertex,Edge>();

    Serializer::Serialize<GraphLib::Graph<Vertex,Edge>>& serializer = Serializer::Serialize<GraphLib::Graph<Vertex,Edge>>::instance();
    serializer.importFromJson(graph);

    ui->setupUi(this);

    for(auto iter = graph->getVertices()->begin();iter!=graph->getVertices()->end(); ++iter)
    {
        ui->vertexFrom->addItem(QString::fromStdString(iter->get_name()));
        ui->vertexTo->addItem(QString::fromStdString(iter->get_name()));
        ui->deleteVertex->addItem(QString::fromStdString(iter->get_name()));
        ui->vertexFromDel->addItem(QString::fromStdString(iter->get_name()));
    }
    ui->flyTimeBox->setMinimum(1);
    ui->flyTimeBox->setButtonSymbols( QAbstractSpinBox::NoButtons );

};
MainWindow::~MainWindow()
{
    Serializer::Serialize<GraphLib::Graph<Vertex,Edge>>& serializer = Serializer::Serialize<GraphLib::Graph<Vertex,Edge>>::instance();
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
    QMessageBox::information(0, "INFO", "Аэропорт добавлен!");
    ui->VertexNameLine->clear();
}

void MainWindow::on_addEdgePushButton_clicked()
{
    int from_id=-1, to_id=-1;
    QString tmpstr;
    from_id = graph->getVertex(ui->vertexFrom->currentText().toStdString())->get_id();
    to_id = graph->getVertex(ui->vertexTo->currentText().toStdString())->get_id();
    if((from_id==-1)||(to_id==-1)){
        QMessageBox::information(0, "ERROR", "Аэропорт не найден!");
    }
    else if (from_id == to_id) {
        QMessageBox::information(0, "ERROR", "Начальный и конечный аэропорт совпадают!");
    }
    else{
        try {
            graph->add_edge(from_id,new Edge(to_id,ui->flyTimeBox->text().toInt()));
            tmpstr = "TO: " + QString::fromStdString(graph->getVertex(to_id)->get_name()) + ", fly time: " + ui->flyTimeBox->text();
            ui->edgeSelecter->addItem(tmpstr);
            vertexNameDel.push_back(graph->getVertex(to_id)->get_name());
            flyTimeDel.push_back(ui->flyTimeBox->text().toInt());
            QMessageBox::information(0, "INFO", "Рейс добавлен!");
            ui->flyTimeBox->setValue(1);
        } catch (EdgeLoopException e) {
            std::cerr<<"Edge adding error"<<std::endl;
        }

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
            QMessageBox::information(0, "INFO", "Аэропорт удалён!");
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
//    qDebug()<<QString::fromStdString(vertexNameDel[ui->edgeSelecter->currentIndex()]);
//    qDebug()<<QString::number(flyTimeDel[ui->edgeSelecter->currentIndex()]);
//    for (int i = 0; i < vertexNameDel.size();i++) {
//        qDebug()<<i<<" "<<QString::fromStdString(vertexNameDel[i])<<QString::number(flyTimeDel[i]);
//    }
    try {
      graph->getVertex(ui->vertexFromDel->currentText().toStdString())->
              delete_edge(graph->getVertex(vertexNameDel[ui->edgeSelecter->currentIndex()])->get_id(),
              flyTimeDel[ui->edgeSelecter->currentIndex()]);
      int i = ui->edgeSelecter->currentIndex();
      vertexNameDel.erase(vertexNameDel.begin() + i);
      flyTimeDel.erase(flyTimeDel.begin() + i);
      ui->edgeSelecter->removeItem(ui->edgeSelecter->currentIndex());
      QMessageBox::information(0, "INFO", "Рейс удалён!");
    } catch (EdgeDeletingException e) {
        std::cerr<<"Edge deleting error"<<std::endl;
    }
}
