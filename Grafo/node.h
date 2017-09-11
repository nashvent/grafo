#ifndef NODE_H
#define NODE_H

#include "bits/stdc++.h"
using namespace std;

struct Edge;
struct Node{
    int coord[2];
    vector<Edge*> edges;
    bool visit; //Si el nodo ha sido visitado
    Node* padre; // para A*
    int gN,hN,fN; // para A*
    bool aStarVisit;

    Node(); //Cuando se crea un nodo sentinela, sin posicion
    Node(int*); //Cuando ya se crea un nodo con posicion
    string printNode(); //Imprime la posicion del Nodo
    void printEdges(); //Imprime a todas las aristas que le pertenecen
    Edge* shareEdge(Node*); //Consulta si ese nodo comparte arista con otro nodeX
    bool deleteEdge(Node*); //Elimina la arista con el nodo input nodo
    bool deleteEdges();
};

struct Edge{
    int weight; // Peso de la arista
    Node* eNodes[2]; //Lista de tamaño 2  de nodos A y B
    Edge(int,Node*,Node*); //La arista recibe peso y dos nodos (A y B)
    void printEdge(Node*); //Imprime la informacion de la arista NodoA - peso - Nodo B
    bool belongNode(Node*); //Consulta si un nodo nodeX pertenece a la arista
    Node* whoBelongEdge(Node*); //Quien comparte esta arista
    bool autoRemove();
};

#endif // NODE_H
