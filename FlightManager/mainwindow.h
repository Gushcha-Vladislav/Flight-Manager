#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <graph.h>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Graph<Vertex,Edge> *graph;

private slots:
    void on_vertexAddPushButton_clicked();

    void on_addEdgePushButton_clicked();

    void on_deleteVertexPushButton_clicked();

    void on_vertexFromDel_currentIndexChanged(int index);

    void on_deleteEdgePushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<std::string> vertexNameDel;
    std::vector<int> flyTimeDel;
};

#endif // MAINWINDOW_H
