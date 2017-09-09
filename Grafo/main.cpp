#include "mainwindow.h"
#include <QApplication>
#include "graph.h"

int main(int argc, char *argv[]){
    int tam[2]={100,100};
    Graph *grafo=new Graph(tam);
    int pos[2]={1,2};

    grafo->insertNode(pos);
    int pos2[2]={3,3};
    grafo->insertNode(pos2);
    grafo->insertEdge(2,pos,pos2);
    grafo->print();
    //grafo->deleteNode(pos2);
    grafo->deleteEdge(pos,pos2);
    grafo->print();

    /*Parte grafica*/
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
