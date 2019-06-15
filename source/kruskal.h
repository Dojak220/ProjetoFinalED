#ifndef KRUSKAL
#define KRUSKAL
#include "kruskal.cpp"

// Inicia cada v�rtice como representante de si pr�prio.
void iniciaPai(int n);
// Checa se dois v�rtices pertencem ao mesmo subset. Isso indica que, caso uma aresta seja colocada entre
// esses v�rtices, formar� um ciclo, deixando, assim, de ser uma �rvore.
bool same_set(int x, int y);
// Faz com que o pai de y seja pai tamb�m de x e de todos os v�rtices que eram representados por x.
void join(int x, int y, int n);
// Merge gen�rico funcional
// Complexidade(O(n))
void merge(Aresta *grafo, int p, int q, int r) ;

void mergeSort(Aresta *grafo, int comeco, int fim);
//função responsavel pela obtenção da arvore geradora mínima
void Kruskal();

#endif
