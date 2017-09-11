#include "graph.h"


/* Implementacion grafo */
Graph::Graph(int*tam){
    size[0]=tam[0];
    size[1]=tam[1];
    vector<vector<Node*> > A(tam[0], vector<Node*>(tam[1],NULL));
    nodes= A;
}

bool Graph::checkDimension(int*A,int*B){ //A es el tamaño de la matriz, y B es el tamaño a comprobar
    return (A[0]>B[0] and A[1]>B[1]);
}

void Graph::randomInsert(int total){
    int x,y;
    srand (time(NULL));
    for (int i = 0; i < total; i++) {
        x=rand() % size[0];
        y=rand() % size[1];
        int coord[2]={x,y};
        insertNode(coord);     
    }
    cout<<endl;
}

void Graph::cuadricular(){
    srand (time(NULL));
    vector<Node*>nStaticTemp=nStatic;
    while (nStaticTemp.size()>1) {
        Node* temp=nStaticTemp[0];
        if(temp->edges.size()<maxEdge){
            while ( temp->edges.size()<maxEdge and nStaticTemp.size()>0) {
                cout<<"hola"<<endl;
                int rd=rand()% nStaticTemp.size();
                if(nStaticTemp[rd]->edges.size()<maxEdge){
                    insertEdge(0,temp->coord,nStaticTemp[rd]->coord);
                }
                else
                    nStaticTemp.erase(nStaticTemp.begin()+rd);
            }
            nStaticTemp.erase(nStaticTemp.begin());
        }
        else
            nStaticTemp.erase(nStaticTemp.begin());
    }
}

vector<Node *> Graph::searchBlind(int * begin, int * end){
    vector<Node*> result;
    Node * x=searchNode(begin);
    Node * y=searchNode(end);
    cout<<endl;
    x->printNode();
    y->printNode();
    cout<<"recorre"<<endl;
    result.push_back(x);

    while(result[0]->coord != y->coord){
        Node * temp=result[0];
        temp->visit=true;
        result.erase(result.begin());
        for (int i = 0; i < temp->edges.size(); i++) {
            Node * p=temp->edges[i]->whoBelongEdge(temp);
            if(p->visit==false){
                p->visit=true;
                result.push_back(p);
            }
        }
        for (int k = 0; k < result.size(); ++k) {
            result[k]->printNode();
        }
        cout<<endl;

    }

    return result;
}

Node* Graph::searchNode(int *pos){
    Node* resp=NULL;
    if(checkDimension(size,pos))
        resp=nodes[pos[0]][pos[1]];
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
        nStatic.push_back(tempNode);
        tempNode->printNode();
        return true;
    }
    return false;
}

bool Graph::insertEdge(int peso,int *nA, int *nB){
    Node* nodeA=searchNode(nA);
    Node* nodeB=searchNode(nB);
    if(nodeA!=NULL and nodeB!=NULL and nodeA->shareEdge(nodeB)==NULL and nodeA!=nodeB){
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
            edgeTemp->autoRemove();
            return true;
        }
        else
            return false;
    }
}

bool Graph::deleteNode(int *coordNode) { //Falta aun
    Node* temp=searchNode(coordNode);
    if(temp!=NULL){
        temp->deleteEdges();
        nodes[coordNode[0]][coordNode[1]]=NULL;
        delete(temp);
    }
}

void Graph::print() {
    for(int x=0;x<nodes.size();x++){
        cout<<x;
        if(x<10)
            cout<<":   ";
        if(x>=10 and x<100)
            cout<<":  ";
        if(x>=100)
            cout<<": ";

        for (int y = 0; y <nodes[0].size();y++) {
            Node*temp=nodes[x][y];
            if(temp!=NULL){
                cout<<" * ";
            }
            else{
                cout<<" - ";
            }
        }
        cout<<endl;
    }
}

void Graph::printStatic(){
    for(int x=0;x<nStatic.size();x++){
        nStatic[x]->printNode();
        if(nStatic[x]->edges.size()>0){
            cout<<"aristas: ";
            nStatic[x]->printEdges();
        }
        cout<<endl;
    }
}

template<class T>
bool existeEnVector(vector<T>V,T elemento){
    for(int x=0;x<V.size();x++){
        if(V[x]==elemento)
            return true;
    }
    return false;
}


void Graph::aStar(int *inicio, int *final){
    Node* current=searchNode(inicio);
    Node* fin=searchNode(final);
    vector<Node*>openList,closeList;
    openList.push_back(current);
    while(openList.size()>0 and current!=fin){
        current=openList[0];
        for(int x=0;x<current->edges.size();x++){
            Node*vecino=current->edges[x]->whoBelongEdge(current);
            if(vecino->aStarVisit==false){
                int gN=current->edges[x]->weight;
                int hN=distanciaEuclidiana(vecino->coord,fin->coord);
                int fN=gN+hN;
                if(existeEnVector(openList,vecino)){
                    if(fN<vecino->fN){
                        vecino->padre=current;
                        vecino->gN=gN;
                        vecino->fN=fN;
                    }
                }
                else{
                    openList.push_back(vecino);
                    vecino->gN=gN;
                    vecino->hN=hN;
                    vecino->fN=fN;
                    vecino->padre=current;
                }
            }
        }
        current->aStarVisit=true;
        openList.erase(openList.begin());

    }
    if(openList.size()==0){
        cout<<"No hay camino"<<endl;
    }
    else{
        while(current!=NULL){
            current->printNode();
            cout<<" <- ";
            current=current->padre;
        }
    }
}

int Graph::distanciaEuclidiana(int *A, int *B){
    return abs(A[0]-B[0])+abs(A[1]-B[1]);
}

