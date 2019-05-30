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
    ui->graphicsView->setScene(graph->draw());

    for(auto iter = graph->getVertices()->begin();iter!=graph->getVertices()->end(); ++iter)
    {
        ui->vertexFrom->addItem(QString::fromStdString(iter->get_name()));
        ui->vertexTo->addItem(QString::fromStdString(iter->get_name()));
        ui->deleteVertex->addItem(QString::fromStdString(iter->get_name()));
        ui->vertexFromDel->addItem(QString::fromStdString(iter->get_name()));
        ui->fromFind->addItem(QString::fromStdString(iter->get_name()));
        ui->toFind->addItem(QString::fromStdString(iter->get_name()));
    }
    ui->flyTimeBox->setMinimum(1);
    ui->flyTimeBox->setButtonSymbols( QAbstractSpinBox::NoButtons );
    ui->wayLabel->setVisible(false);
};
MainWindow::~MainWindow()
{
    Serializer::Serialize<GraphLib::Graph<Vertex,Edge>>& serializer = Serializer::Serialize<GraphLib::Graph<Vertex,Edge>>::instance();
    serializer.exportToJson(graph);
    delete ui;
};

void MainWindow::on_vertexAddPushButton_clicked()
{
    if(graph->getVertex(ui->VertexNameLine->text().toStdString()) == nullptr){
        QString vertexName = ui->VertexNameLine->text();
        graph->add_vertex(new Vertex<Edge>(vertexName.toStdString(),1.1,2.2));
        ui->vertexFrom->addItem(ui->VertexNameLine->text());
        ui->vertexTo->addItem(ui->VertexNameLine->text());
        ui->deleteVertex->addItem(ui->VertexNameLine->text());
        ui->vertexFromDel->addItem(ui->VertexNameLine->text());
        ui->fromFind->addItem(ui->VertexNameLine->text());
        ui->toFind->addItem(ui->VertexNameLine->text());
        ui->graphicsView->setScene(graph->draw());
        QMessageBox::information(0, "INFO", "Airport added!");
        ui->VertexNameLine->clear();
    }
    else {
        QMessageBox::information(0, "INFO", "This airport has already been added!");
        ui->VertexNameLine->clear();
    }
}

void MainWindow::on_addEdgePushButton_clicked()
{
    int from_id=-1, to_id=-1;
    QString tmpstr;
    from_id = graph->getVertex(ui->vertexFrom->currentText().toStdString())->get_id();
    to_id = graph->getVertex(ui->vertexTo->currentText().toStdString())->get_id();
    if((from_id==-1)||(to_id==-1)){
        QMessageBox::information(0, "ERROR", "Airport not found!");
    }
    else if (from_id == to_id) {
        QMessageBox::information(0, "ERROR", "Start and end airport match!");
    }
    else{
        try {
            graph->add_edge(from_id,new Edge(to_id,ui->flyTimeBox->text().toInt()));
            tmpstr = "TO: " + QString::fromStdString(graph->getVertex(to_id)->get_name()) + ", fly time: " + ui->flyTimeBox->text();
            ui->edgeSelecter->addItem(tmpstr);
            vertexNameDel.push_back(graph->getVertex(to_id)->get_name());
            flyTimeDel.push_back(ui->flyTimeBox->text().toInt());
            ui->graphicsView->setScene(graph->draw());
            QMessageBox::information(0, "INFO", "Flight added!");
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
            ui->fromFind->removeItem(ui->deleteVertex->currentIndex());
            ui->toFind->removeItem(ui->deleteVertex->currentIndex());
            ui->deleteVertex->removeItem(ui->deleteVertex->currentIndex());
            graph->delete_vertex(iter->get_id());
            this->on_vertexFromDel_currentIndexChanged(1);
            ui->graphicsView->setScene(graph->draw());
            QMessageBox::information(0, "INFO", "Airport removed!");
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
    try {
      graph->getVertex(ui->vertexFromDel->currentText().toStdString())->
              delete_edge(graph->getVertex(vertexNameDel[ui->edgeSelecter->currentIndex()])->get_id(),
              flyTimeDel[ui->edgeSelecter->currentIndex()]);
      int i = ui->edgeSelecter->currentIndex();
      vertexNameDel.erase(vertexNameDel.begin() + i);
      flyTimeDel.erase(flyTimeDel.begin() + i);
      ui->edgeSelecter->removeItem(ui->edgeSelecter->currentIndex());
        ui->graphicsView->setScene(graph->draw());
      QMessageBox::information(0, "INFO", "Flight deleted!");
    } catch (EdgeDeletingException e) {
        std::cerr<<"Edge deleting error"<<std::endl;
    }
}

void MainWindow::on_findRoutePushButton_clicked()
{
    ui->wayLabel->clear();
    if(!ui->fromFind->currentText().compare(ui->toFind->currentText())){
        ui->wayLabel->setText("The starting and ending airport are the same.\n Why do you need to fly?\n Take advantage of your legs.");
    }
    else {
        std::string way = graph->find_way(graph->getVertex(ui->fromFind->currentText().toStdString())->get_id(),
                        graph->getVertex(ui->toFind->currentText().toStdString())->get_id());
        ui->wayLabel->setText(QString::fromStdString(way));
    }
    ui->wayLabel->setVisible(true);
}
