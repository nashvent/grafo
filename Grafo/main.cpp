#include "mainwindow.h"
#include <QApplication>
#include "graph.h"

int main(int argc, char *argv[]){
    int tam[2]={7,7};
    Graph *grafo=new Graph(tam);

    grafo->randomInsert(7);
    //grafo->randomInsert(100);
    cout<<"ADD EDGES"<<endl;
    grafo->cuadricular();
    grafo->printStatic();
    grafo->print();
    //grafo->searchBlind(grafo->nStatic[0]->coord,grafo->nStatic[4]->coord);
    cout<<"inicio: ";
    grafo->nStatic[0]->printNode();
    cout<<endl;
    cout<<"fin: ";
    grafo->nStatic[1]->printNode();
    cout<<endl;
    grafo->aStar(grafo->nStatic[0]->coord,grafo->nStatic[4]->coord);


/*******************Parte grafica********************/
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
