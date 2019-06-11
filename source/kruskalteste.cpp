#include <iostream>
#include <vector>
using namespace std;
#define nVerticesMax 100

typedef struct Aresta{
    int v1, v2;
    int peso;
}Aresta;

typedef struct Grafo{
    int N, N_atual;
    Aresta arestas[nVerticesMax];
}Grafo;

void adicionarAresta(int v1, int v2, int peso, Grafo G){
	Aresta aresta_aux;
    aresta_aux.v1 = v1;
    aresta_aux.v2 = v2;
    aresta_aux.peso = peso;

	if(G.N_atual < G.N) 
        G.arestas[G.N_atual++] = aresta_aux;
}