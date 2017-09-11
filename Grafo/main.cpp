#include "mainwindow.h"
#include <QApplication>
#include "graph.h"

int main(int argc, char *argv[]){


/*******************Parte grafica********************/
    QApplication a(argc, argv);
    MainWindow w;
    w.graphicsNode(7,10); // int n_nodes, int tamanio grafo
    w.show();

    return a.exec();
}
