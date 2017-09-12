#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
struct Graph{
    vector<vector<Node*>>nodes;
    int size[2];
    int maxEdge=4;
    int len=10;
    vector<Node*> nStatic;

    //list<Node*>nodes;
    Graph(int*); //Constructor del grafo recibe las dimesiones en un array
    Node* searchNode(int*); //Busqueda si existe el Nodo dentro del grafo (NULL o Nodo*)
    Edge* searchEdge(int*,int*); //Busqueda si existe la arista entre dos Nodos (Null o Edge*)
    bool insertNode(int*); //Inserta un nodo, recibe las coordenadas en un array int*
    bool insertEdge(int,int*,int*); // Inserta una arista, recibe : peso, coord A, coord B
    bool deleteEdge(int*,int*); //Elimina una arista, recibe: coord A, coord B
    bool deleteNode(int*); //Elimina un nodo, recibe : coord Nodo
    bool checkDimension(int*,int*);
    void randomInsert(QGraphicsScene *,QBrush,QPen,int);//Inserta una cantidad de nodos
    void cuadricular(QGraphicsScene *,QPen);
    string searchBlind(QGraphicsScene *,QPen,int*,int*);
    void print();
    void printStatic();
    void colorNode(QGraphicsScene *,QPen,QBrush,QBrush,int*,int*);
    void delVisit(); //quita visit de todos los nodos
    void delColor(QGraphicsScene *,QBrush,QPen);//colorea todos normalmente

    string aStar(QGraphicsScene *,QPen,int*,int*);//Busqueda desde un nodo inicial y final
    //int distanciaEuclidiana(int*,int*);
    vector<Node*> sortStaticTemp(vector<Node*>);
};




#endif // GRAPH_H
