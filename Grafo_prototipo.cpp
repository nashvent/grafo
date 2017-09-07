#include <list>
#include <iostream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
#include <vector>
#include <queue>  
using namespace std;
//Ya no usaremos std ...

class CEdge; //declaracion previa de la clase de aristas

//Clase nodo
class CNode
{
public:
	int en_x; //coordenada en el eje x
	int en_y; //coordenada en el eje y
	list<CEdge*> aristas; //lista de aristas del nodo
	CNode(int x, int y) //constructor
	{
		en_x = x;
		en_y = y;
	}
};

///Bloque de clases para implementar el recorrido entre nodos
class Cam_nodo //nodos para la cola de aristas
{
public:
	CNode* nodo; //nodo
	int distancia; //distancia vectorial
	Cam_nodo(CNode* n, int d)
	{
		nodo = n;
		distancia = d;
	}
	Cam_nodo()
	{
		nodo = 0;
		distancia = 0;
	}
};
class mycomparison //comparacion para ordenar la cola de aristas
{
public:
	bool operator() (const Cam_nodo& left, const Cam_nodo&rigth) const
	{
		return (left.distancia > rigth.distancia);
	}
};





//Clase arista
class CEdge
{
public:
	int data; //dato de la arista
	CNode *nodos[2]; //nodos a los que apunta
	bool sentido; //sentido de la arista 0<-> , 1->
	CEdge(CNode *a, CNode *b, int dato, bool dir) //constructor
	{
		data = dato;
		sentido = dir;
		nodos[0] = a;
		nodos[1] = b;
	}
};



//Clase grafo
class CGraph
{
public:
	vector<CNode*> nodos;

	//Funcion que busca un nodo(x,y) en el grafo
	bool searchNode(int x, int y, int &posicion)
	{
		for (auto cursor : nodos)
		{
			if (cursor->en_x == x && cursor->en_y == y)
			{
				return true;
			}
			posicion++;
		}
		return false;
	}

	//Funcion que inserta un nuevo nodo(x,y)
	bool addNode(int x, int y)
	{
		int tabique = 0;//apoyo que requiere la funcion searchNode
		if (searchNode(x, y, tabique)) //posicion irrelevante
		{
			return false;
		}
		nodos.push_back(new CNode(x, y)); //si no existe, lo insertamos
		return true;
	}

	//Funcion que inserta una arista de a->b con peso y direccion determinadas
	bool addEdge(CNode *a, CNode *b, int peso, bool dir)
	{
		CEdge* arista = new CEdge(a, b, peso, dir); //creamos la arista
		a->aristas.push_back(arista);
		b->aristas.push_back(arista);//la vinculamos con a y con b
		return true;
	}


	//Funcion auxiliar que borra una arista de a->b con peso determinado
	bool delEdge(CNode *a, CNode *b, int peso)
	{
		typename list<CEdge*>::iterator cursor1; //para moverse en las aristas de a
		typename list<CEdge*>::iterator cursor2; //para moverse en las aristas de b
		for (cursor1 = a->aristas.begin(); cursor1 != a->aristas.end();)
		{
			if ((*cursor1)->nodos[1] == b && (*cursor1)->data == peso) //si encontramos la arista...
			{
				cursor1 = a->aristas.erase(cursor1); //...la borramos
			}
			else
			{
				++cursor1; //de lo contrario, seguimos avanzando
			}
		}
		for (cursor2 = b->aristas.begin(); cursor2 != b->aristas.end();) //lo mismo para b
		{
			if ((*cursor2)->nodos[0] == a && (*cursor2)->data == peso)
			{
				cursor2 = b->aristas.erase(cursor2);
			}
			else
			{
				++cursor2;
			}
		}
		return true;
	}


	//Funcion que borra un nodo(x,y)
	bool delNode(int x, int y)
	{
		int posicion = 0;
		if (searchNode(x, y, posicion) == false)
		{
			return false; //si no existe, no se puede borrar
		}
		typename list<CEdge*>::iterator cursor;
		while (nodos[posicion]->aristas.empty() == false) //mientras haya aristas en el nodo...
		{
			cursor = nodos[posicion]->aristas.begin();
			delEdge((*cursor)->nodos[0], (*cursor)->nodos[1], (*cursor)->data);//borramos arista por arista
		}
		nodos.erase(nodos.begin() + posicion); //borramos el nodo
		return true;
	}

	//Llena el grafo con el numero de nodos indicado, simulando triangulacion
	void llenar(int tam)
	{
		srand(time(NULL));
		int x = rand() % 10 + 1;
		int y = rand() % 10 + 1;
		addNode(x, y);
		if ((x & 1) == 0)
		{
			x += rand() % 10 + 1;
		}
		else
		{
			x -= rand() % 10 + 1;
		}
		if ((y & 1) == 0)
		{
			y += rand() % 10 + 1;
		}
		else
		{
			y -= rand() % 10 + 1;
		}
		addNode(x, y);
		addEdge(nodos[nodos.size() - 1], nodos[nodos.size() - 2], 1, 0);
		while (nodos.size() != tam)
		{
			if ((x & 1) == 0)
			{
				x += rand() % 10 + 1;
			}
			else
			{
				x -= rand() % 10 + 1;
			}
			if ((y & 1) == 0)
			{
				y += rand() % 10 + 1;
			}
			else
			{
				y -= rand() % 10 + 1;
			}
			if(addNode(x, y))
			{ 
				addEdge(nodos[nodos.size() - 1], nodos[nodos.size() - 2], 1, 0);
				addEdge(nodos[nodos.size() - 1], nodos[nodos.size() - 3], 1, 0);
			}
		}
	}

	//Algoritmo para hallar un camino entre a y b en base a la heuristica de distancia vectorial
	bool recorrido(CNode *a, CNode *b, vector<CNode*> &ruta)
	{
		for (auto cursor : ruta)//si ya se paso por este nodo... 
		{
			if (cursor == a)
			{
				return false;//el camino se detiene
			}
		}
		ruta.push_back(a);//el camino continua
		if (a == b)//si llegue a  mi destino, hubo exito
		{
			return true;
		}
		priority_queue <Cam_nodo,vector<Cam_nodo>,mycomparison> caminos; //cola de aristas ordenadas segun su distancia vectorial
		int distancia = 0;
		CNode *opcion;
		for (CEdge* cursor : a->aristas) //recorremos las aristas del nodo
		{
			opcion = cursor->nodos[cursor->nodos[0] == a];
			distancia = (b->en_x - opcion->en_x)*(b->en_x - opcion->en_x) + (b->en_y - opcion->en_y)*(b->en_y - opcion->en_y);//calculamos la distancia
			caminos.push( Cam_nodo(opcion,distancia) ); //insertamos en la cola, se ordena poniendo el menor al tope
		}
		while(caminos.empty() != true) //recorremos las aristas
		{
			if (recorrido(caminos.top().nodo, b, ruta) == true) //llamamos de nuevo a la funcion, si hubo exito, es un camino correcto
			{
				return true;
			}
			caminos.pop();
		}
		ruta.pop_back(); //si ninguna de las aristas funciona, el nodo no nos sirve
		return false; //fin del camino, debemos retorceder
	}

	//Funcion que imprime el grafo
	void print()
	{
		for (CNode* cursor1 : nodos)
		{
			cout << "(" << (*cursor1).en_x << "," << (*cursor1).en_y << "): ";
			for (CEdge* cursor2 : cursor1->aristas)
			{
				if (cursor2->sentido == 1 && cursor2->nodos[0] == cursor1)
				{
					cout << cursor2->data << "(" << (cursor2->nodos[1])->en_x << "," << (cursor2->nodos[1])->en_y << ") ";
				}
				else if (cursor2->sentido == 0)
				{
					cout << cursor2->data << "(" << (cursor2->nodos[cursor2->nodos[0] == cursor1])->en_x << "," << (cursor2->nodos[cursor2->nodos[0] == cursor1])->en_y << ") ";
				}
			}
			cout << endl;

		}
	}
};

//Funcion auxiliar que imprime un camino entre nodos
void imprimir_camino(vector<CNode*> camino)
{
	for (auto cursor : camino)
	{
		cout << "(" << cursor->en_x << "," << cursor->en_y << ")" << " -> ";
	}
}


int main()
{
	CGraph grafo;
	grafo.llenar(5000);
	grafo.print();
	cout << endl;
	vector<CNode*> mi_camino;
	grafo.recorrido(grafo.nodos[2568], grafo.nodos[4325],mi_camino);
	imprimir_camino(mi_camino);
	getchar();
	return 0;
}
