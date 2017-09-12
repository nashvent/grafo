#include "graph.h"

int distanciaEuclidiana(int *A, int *B){
    return abs(A[0]-B[0])+abs(A[1]-B[1]);
}

void printVectorNodo(vector<Node*>V){
    for(int x=0;x<V.size();x++){
        V[x]->printNode();
        cout<<" ";
    }
    cout<<endl;
}

Node*globalTemp;
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

void Graph::randomInsert(QGraphicsScene * scene,QBrush redBrush,QPen outlinePen,int total){
    int x,y;
    srand (time(NULL));
    for (int i = 0; i < total; i++) {
        x=rand() % size[0];
        y=rand() % size[1];
        int coord[2]={x,y};
        scene->addEllipse(coord[1]*len,coord[0]*len,10,10,outlinePen,redBrush);
        insertNode(coord);     
    }
    cout<<endl;
}


void Graph::cuadricular(QGraphicsScene * scene,QPen outlinePen){
    vector<Node*>nStaticTemp=nStatic;
    while(nStaticTemp.size()>0){
        globalTemp=nStaticTemp[0];
        nStaticTemp=sortStaticTemp(nStaticTemp);
        printVectorNodo(nStaticTemp);
        for(int x=1;x<maxEdge and x<nStaticTemp.size();x++){
            if(nStaticTemp[0]->edges.size()<maxEdge and nStaticTemp[x]->edges.size()<maxEdge){
                insertEdge(0,nStaticTemp[0]->coord,nStaticTemp[x]->coord);
                scene->addLine(nStaticTemp[0]->coord[1]*len,nStaticTemp[0]->coord[0]*len,
                               nStaticTemp[x]->coord[1]*len,nStaticTemp[x]->coord[0]*len,
                               outlinePen);
            }
        }
        nStaticTemp.erase(nStaticTemp.begin());
    }   
}

string Graph::searchBlind(QGraphicsScene * scene,QPen outlinePen,int * begin, int * end){
    string label;
    vector<Node*> result;
    Node * x=searchNode(begin);
    Node * y=searchNode(end);
    result.push_back(x);
    label="1.  {("+to_string(x->coord[0])+","+to_string(x->coord[1])+")}\n";
    Node * temp;
    int cont=1;
    while(result[0]->coord != y->coord){
        temp=result[0];
        temp->visit=true;
        result.erase(result.begin());
        for (int i = 0; i < temp->edges.size(); i++) {
            Node * p=temp->edges[i]->whoBelongEdge(temp);
            if(p->visit==false){
                p->visit=true;
                scene->addLine(temp->coord[1]*len,temp->coord[0]*len,p->coord[1]*len,p->coord[0]*len,outlinePen);
                result.push_back(p);
            }
        }
        //imprime la lista de aplitud
        label+=to_string(++cont)+".  {";
        for (int k = 0; k < result.size(); ++k) {
            label+="("+to_string(result[k]->coord[0])+","+to_string(result[k]->coord[1])+") ";
        }
        label+="}\n";
    }
    delVisit();
    return label;
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
    int positionBase[2]={0,0};
    if(searchNode(posNode)==NULL){
        Node* tempNode=new Node(posNode);
        nodes[posNode[0]][posNode[1]]=tempNode;
        /* Insercion a nStatic ordenado*/
        Node* tempAnterior=NULL;
        int size=nStatic.size();
        if(size>0)
            tempAnterior=nStatic[nStatic.size()-1];
        while(size!=0 and distanciaEuclidiana(posNode,positionBase)<distanciaEuclidiana(tempAnterior->coord,positionBase)){
            size--;
            tempAnterior=nStatic[size-1];
        }

        nStatic.insert(nStatic.begin()+size,tempNode);
        /*Solo usado para cuadricular*/

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
    else{

        return false;

    }
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
                cout<<"*";
            }
            else{
                cout<<"-";
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

void Graph::colorNode(QGraphicsScene *scene,QPen outlinePen, QBrush ini, QBrush fin, int *x, int *y)
{
    Node *inicio=searchNode(x);
    Node *final=searchNode(y);
    scene->addEllipse(inicio->coord[1]*len,inicio->coord[0]*len,10,10,outlinePen,ini);
    scene->addEllipse(final->coord[1]*len,final->coord[0]*len,10,10,outlinePen,fin);
}

void Graph::delVisit()
{
    for (int i = 0; i < nStatic.size(); i++) {
        nStatic[i]->visit=false;
    }
}

void Graph::delColor(QGraphicsScene * scene,QBrush redBrush,QPen outlinePen)
{
    for (int i = 0; i < nStatic.size(); i++) {
        scene->addEllipse(nStatic[i]->coord[1]*len,nStatic[i]->coord[0]*len,10,10,outlinePen,redBrush);
        for (int j = 0; j < nStatic[i]->edges.size();j++) {
            Node * belong=nStatic[i]->edges[j]->whoBelongEdge(nStatic[i]);
            scene->addLine(nStatic[i]->coord[1]*len,nStatic[i]->coord[0]*len,
                           belong->coord[1]*len,belong->coord[0]*len,
                           outlinePen);
        }
    }
}
/*
void Graph::graphicsNode(QGraphicsScene * scene,int* var)
{
    redBrush(Qt::red);
    outlinePen(Qt::black);
    outlinePen.setWidth(2);
    scene->addEllipse(var[0],var[1],20,20,outlinePen,redBrush);
}*/

template<class T>
bool existeEnVector(vector<T>V,T elemento){
    for(int x=0;x<V.size();x++){
        if(V[x]==elemento)
            return true;
    }
    return false;
}


string Graph::aStar(QGraphicsScene * scene,QPen outlinePen,int *inicio, int *final){
    Node* current=searchNode(inicio);
    Node* fin=searchNode(final);
    vector<Node*>openList,closeList;
    openList.push_back(current);
    while(openList.size()>0){
        openList.erase(openList.begin());
        closeList.insert(closeList.begin(),current);
        /*cout<<"______________"<<endl;
        cout<<"NuevaPasada"<<endl;
        cout<<"______________"<<endl;

        cout<<"current: ";
        current->printNode();
        cout<<endl;*/
        for(int x=0;x<current->edges.size();x++){
            Node*vecino=current->edges[x]->whoBelongEdge(current);
            if(existeEnVector(closeList,vecino)==false){
                int gN=current->edges[x]->weight+(distanciaEuclidiana(vecino->coord,current->coord));
                int hN=distanciaEuclidiana(vecino->coord,fin->coord);
                int fN=gN+hN+current->fN;
                /*cout<<"Vecino:";
                vecino->printNode();
                cout<<"gN actual:"<<vecino->gN<<endl;
                cout<<"gN nuevo: "<<gN<<endl;
                */
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

/*
        cout<<"open list"<<endl;
        printVectorNodo(openList);
        cout<<"Close list"<<endl;
        printVectorNodo(closeList);
*/
        if(closeList[0]==fin)
            break;

        current->aStarVisit=true;
        current=openList[0];


    }
    string camino="";
    if(openList.size()==0 and closeList[0]!=fin){
        cout<<"No hay camino"<<endl;
    }
    else{
        cout<<"encontre camino"<<endl;
        current=closeList[0];
        while(current!=NULL){
            camino=current->printNode()+camino  ;
            if(current->padre!=NULL){
                cout<<" <- ";
                camino=" -> "+camino;

                scene->addLine(current->coord[1]*len,current->coord[0]*len,current->padre->coord[1]*len,current->padre->coord[0]*len,outlinePen);
            }
            current=current->padre;
        }
    }
    return camino;
}



bool compareEuclidiana(Node*A,Node*B){
    return distanciaEuclidiana(A->coord,globalTemp->coord)<distanciaEuclidiana(B->coord,globalTemp->coord);
}

vector<Node*> Graph::sortStaticTemp(vector<Node *>V){
    stable_sort(V.begin(),V.end(),compareEuclidiana);
    return V;
}
