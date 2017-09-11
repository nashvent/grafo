#include "mainwindow.h"
#include <QApplication>
#include "graph.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    int tam[2]={20,20};
    Graph *grafo=new Graph(tam);

    grafo->randomInsert(7);
    grafo->cuadricular();

    grafo->print();
    cout<<"print Static"<<endl;
    grafo->printStatic();

/*******************Parte grafica********************/
    MainWindow w;
    w.show();
    return a.exec();
}
