#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "graph.h"
#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QGraphicsScene *scene;
    QGraphicsEllipseItem *circle;
    QGraphicsTextItem *text;
    QGraphicsLineItem *line;
    Graph *g;
    explicit MainWindow(QWidget *parent = 0);
    void graphicsNode(int,int);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
