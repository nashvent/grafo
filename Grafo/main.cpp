#include "mainwindow.h"
#include <QApplication>
#include "graph.h"

int main(int argc, char *argv[]){
    int tam[2]={100,100};
    Graph *grafo=new Graph(tam);
    int pos[2]={1,2};
    int pos2[2]={3,3};

    grafo->insertNode(pos);
    grafo->insertNode(pos2);
    grafo->insertEdge(2,pos,pos2);
    grafo->print();
    //grafo->deleteNode(pos2);
    grafo->deleteEdge(pos,pos2);
    grafo->print();

    grafo->randomInsert(5);
    grafo->print();
    cout<<"ADD EDGES"<<endl;
    //grafo->cuadricular();
    grafo->print();
    int e,b,c,d;
    cout<<"llena: ";
    cin>>e>>b>>c>>d;
    cout<<"listo ";
    int p1[2]={e,b};
    int p2[2]={c,d};

    grafo->searchBlind(p1,p2);

/*******************Parte grafica********************/
/*    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
}
