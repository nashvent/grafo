#include "node.h"


/*Implementacion Nodo*/
Node::Node(){
    coord[0]=coord[1]=-1;
    visit=false;
}

Node::Node(int*position){
    coord[0]=position[0];
    coord[1]=position[1];
    visit=false;
    aStarVisit=false;
    padre=NULL;
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

bool Node::deleteEdges() {
    for(int x=0;x<edges.size();x++)
        edges[x]->autoRemove();
}

/** Implementacion Arista **/

Edge::Edge(int peso,Node*nodeA,Node*nodeB){
    eNodes[0]=nodeA;
    eNodes[1]=nodeB;
    weight=peso;
}
void Edge::printEdge(Node*cNode){
    cout<<" | ";
    cout<<" -"<<weight<<"-> ";
    if(eNodes[0]==cNode){
        eNodes[1]->printNode();
    }
    else{
        eNodes[0]->printNode();
    }

}
Node* Edge::whoBelongEdge(Node*cNode){

    if(eNodes[0]==cNode){
        return eNodes[1];
    }
    else if(eNodes[1]==cNode){
        return eNodes[0];
    }
    return NULL;

}

bool Edge::belongNode(Node* nodeX){
    if(eNodes[0]==nodeX or eNodes[1]==nodeX)
        return true;
    return false;
}

bool Edge::autoRemove() {
    eNodes[0]->deleteEdge(eNodes[1]);
    eNodes[1]->deleteEdge(eNodes[0]);
    delete (this);
}

