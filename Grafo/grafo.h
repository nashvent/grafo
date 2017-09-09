#ifndef GRAFO_H
#define GRAFO_H
#include <bits/stdc++.h>
using namespace std;

bool checkDimension(int*A,int*B){ //A es el tamaño de la matriz, y B es el tamaño a comprobar
    return (A[0]>B[0] and A[1]>B[1]);
}

struct Edge;
struct Node{
    int coord[2];
    vector<Edge*> edges;
    Node(); //Cuando se crea un nodo sentinela, sin posicion
    Node(int*); //Cuando ya se crea un nodo con posicion
    void printNode(); //Imprime la posicion del Nodo
    void printEdges(); //Imprime a todas las aristas que le pertenecen
    Edge* shareEdge(Node*); //Consulta si ese nodo comparte arista con otro nodeX
    bool deleteEdge(Node*); //Elimina la arista con tal nodo
};

struct Edge{
    int weight; // Peso de la arista
    vector<Node*>e_nodes; //Lista de tamaño 2  de nodos A y B
    Edge(int,Node*,Node*); //La arista recibe peso y dos nodos (A y B)
    void printEdge(Node*); //Imprime la informacion de la arista NodoA - peso - Nodo B
    bool belongNode(Node*); //Consulta si un nodo nodeX pertenece a la arista
};

struct Graph{
    vector<vector<Node*>>nodes;
    int size[2];
    //list<Node*>nodes;
    Graph(int*); //Constructor del grafo recibe las dimesiones en un array
    Node* searchNode(int*); //Busqueda si existe el Nodo dentro del grafo (NULL o Nodo*)
    Edge* searchEdge(int*,int*); //Busqueda si existe la arista entre dos Nodos (Null o Edge*)
    bool insertNode(int*); //Inserta un nodo, recibe las coordenadas en un array int*
    bool insertEdge(int,int*,int*); // Inserta una arista, recibe : peso, coord A, coord B
    bool deleteEdge(int*,int*); //Elimina una arista, recibe: coord A, coord B
    bool deleteNode(int*); //Elimina un nodo, recibe : coord Nodo
    void print();
};



/*Implementacion Nodo*/
Node::Node(){
    coord[0]=coord[1]=-1;
}

Node::Node(int*position){
    coord[0]=position[0];
    coord[1]=position[1];
}

void Node::printNode(){
    cout<<"["<<coord[0]<<"]["<<coord[1]<<"] ";
}

void Node::printEdges(){
    for(int x=0;x<edges.size();x++){
        edges[x]->printEdge(this);
    }
}

Edge* Node::shareEdge(Node*nodeX){
    Edge*resp=NULL;
    for(int x=0;x<edges.size();x++){
        if(edges[x]->belongNode(nodeX)){
            resp=edges[x];
        }
    }
    return resp;
}

bool Node::deleteEdge(Node *nodeX){
    for(int x=0;x<edges.size();x++){
        if(edges[x]->belongNode(nodeX)){
            edges.erase(edges.begin()+x);
            return true;
        }
    }
    return false;
}

/** Implementacion Arista **/

Edge::Edge(int peso,Node*nodeA,Node*nodeB){
    e_nodes.push_back(nodeA);
    e_nodes.push_back(nodeB);
    weight=peso;
}
void Edge::printEdge(Node*cNode){
    cout<<" -"<<weight<<"-> ";
    if(e_nodes[0]==cNode){
        e_nodes[1]->printNode();
    }
    else{
        e_nodes[0]->printNode();
    }


}

bool Edge::belongNode(Node* nodeX){
    if(e_nodes[0]==nodeX or e_nodes[1]==nodeX)
        return true;
    return false;
}

/* Implementacion grafo */
Graph::Graph(int*tam){
    size[0]=tam[0];
    size[1]=tam[1];
    vector<vector<Node*> > A(tam[0], vector<Node*>(tam[1],NULL));
    nodes= A;
}

Node* Graph::searchNode(int *pos){
    Node* resp=NULL;
    if(checkDimension(size,pos))
        resp=nodes[pos[0]][pos[1]];
    /*   for(int x=0;x<nodes.size();x++){
           if(nodes[x]->coord[0]==pos[0] and nodes[x]->coord[1]==pos[1]){
               resp=nodes[x];
               break;
           }
       }*/
    return resp;
}

Edge* Graph::searchEdge(int *nA, int *nB){
    Edge* resp=NULL;
    Node* nodeA=searchNode(nA);
    Node* nodeB=searchNode(nB);
    if(nodeA!=NULL and nodeB!=NULL){
        resp=nodeA->shareEdge(nodeB);
    }
    return resp;
}

bool Graph::insertNode(int *posNode){
    if(searchNode(posNode)==NULL){
        Node* tempNode=new Node(posNode);
        nodes[posNode[0]][posNode[1]]=tempNode;
        return true;
    }
    return false;
}

bool Graph::insertEdge(int peso,int *nA, int *nB){
    Node* nodeA=searchNode(nA);
    Node* nodeB=searchNode(nB);
    if(nodeA!=NULL and nodeB!=NULL){
        Edge* tempEdge=new Edge(peso,nodeA,nodeB);
        nodeA->edges.push_back(tempEdge);
        nodeB->edges.push_back(tempEdge);
        return true;
    }
    else
        return false;
}

bool Graph::deleteEdge(int *nA, int *nB){
    Edge* edgeTemp;
    Node* nodeA=searchNode(nA);
    Node* nodeB=searchNode(nB);
    if(nodeA!=NULL and nodeB!=NULL){
        edgeTemp=nodeA->shareEdge(nodeB);
        if(edgeTemp!=NULL){
            nodeB->deleteEdge(nodeA);
            nodeA->deleteEdge(nodeB);
            delete(edgeTemp);
        }
        else
            return false;
    }
}

void Graph::print() {
    for(int x=0;x<nodes.size();x++){
        for (int y = 0; y <nodes[0].size();y++) {
            Node*temp=nodes[x][y];
            if(temp!=NULL){
                temp->printNode();
                cout<<"aristassss: ";
                temp->printEdges();
                cout<<endl;
            }
        }

    }
}
#endif // GRAFO_H
