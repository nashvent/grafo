#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
struct Graph{
    vector<vector<Node*>>nodes;
    int size[2];
    int maxEdge=4;
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
    void randomInsert(int);//Inserta una cantidad de nodos
    void cuadricular();
    void searchBlind(int*,int*);
    void print();
    void printStatic();
};


#endif // GRAPH_H
