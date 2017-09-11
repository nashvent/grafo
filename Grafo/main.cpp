#include "mainwindow.h"
#include <QApplication>
#include "graph.h"

int main(){
    int tam[2]={20,20};
    Graph *grafo=new Graph(tam);
    int pos[2]={1,2};
    int pos2[2]={3,3};

    grafo->randomInsert(7);

    cout<<"ADD EDGES"<<endl;
    grafo->cuadricular();

    grafo->print();
    cout<<"print Static"<<endl;
    grafo->printStatic();
    int x;
    x=getchar();
    cout<<x<<endl;
/*******************Parte grafica********************/
    return 0;
}
