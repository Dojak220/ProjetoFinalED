#ifndef PARTICAO
#define PARTICAO
#include "ParticaoGrafo.cpp"
using namespace std;
//verifica se o grafo é conexo
bool connect(int tam, int (*matAdj)[35]);

//Função responsavel pela copia do Grafo2 no Grafo1
void clona_grafo(Grafo &grafo1, Grafo grafo2, int tamanho);

//A Matriz representa as ligações de cada aresta. exemplo, uma aresta (3,4), na matrizo o par
//(linha, coluna) vai estar representado com o valor 1
//A função em si posiciona esses valores de acordo com o grafo de entrada
void mudaMatriz(int tam, int (*matAdj)[35], Aresta aresta, int mat[35][35]);

//Função responsavel por verificar quantas arestas opcionais existem na arvore geradora minima
int num_op(Grafo grafo);

void Particao(char *infile);
#endif