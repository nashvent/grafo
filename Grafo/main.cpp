#include "mainwindow.h"
#include <QApplication>
#include "graph.h"

int main(int argc, char *argv[]){
    int tam[2]={10,10};
    Graph *grafo=new Graph(tam);

    grafo->randomInsert(7);
    grafo->cuadricular();
    grafo->printStatic();
    grafo->searchBlind(grafo->nStatic[0]->coord,grafo->nStatic[4]->coord);

/*******************Parte grafica********************/
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
