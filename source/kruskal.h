#ifndef KRUSKAL
#define KRUSKAL
#define MAX 100
#include "kruskal.cpp"
using namespace std;
// Inicia cada vértice como representante de si próprio.
void iniciaPai(int n);
// Checa se dois vértices pertencem ao mesmo subset. Isso indica que, caso uma aresta seja colocada entre
// esses vértices, formará um ciclo, deixando, assim, de ser uma árvore.
bool same_set(int x, int y);
// Faz com que o pai de y seja pai também de x e de todos os vértices que eram representados por x.
void join(int x, int y, int n);
// Merge genérico funcional
// Complexidade(O(n))
void merge(Aresta grafo[MAX], int p, int q, int r) ;

void mergeSort(Aresta grafo[MAX], int comeco, int fim);

void Kruskal();

#endif
