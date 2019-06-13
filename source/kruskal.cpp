#include <iostream>
#include <algorithm>

using namespace std;

typedef struct Aresta
{
    int vertice1, vertice2, peso, marcacao=0;
} Aresta;

typedef struct Grafo
{
    int n, m; // n -> n° vertices, m -> n° arestas
    Aresta *grafo;
} Grafo;

int *pai;

// Inicia cada vértice como representante de si próprio.
void iniciaPai(int n)
{
    pai = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
    {
        pai[i] = i;
    }
}
// Checa se dois vértices pertencem ao mesmo subset. Isso indica que, caso uma aresta seja colocada entre
// esses vértices, formará um ciclo, deixando, assim, de ser uma árvore.
bool same_set(int x, int y)
{
    if (pai[x] == pai[y])
        return true;
    else
        return false;
}
// Faz com que o pai de y seja pai também de x e de todos os vértices que eram representados por x.
void join(int x, int y, int n)
{
    int aux = pai[x];
    for (int i = 0; i < n; i++)
    {
        if (pai[i] == aux)
        {
            pai[i] = pai[y];
        }
    }
}

// Merge genérico funcional
// Complexidade(O(n))
void merge(Aresta *grafo, int p, int q, int r)
{
    int n1 = q - p + 1; // limite do vetor esquerdo (L)
    int n2 = r - q;     // limite do vetor direito (R)
    Aresta L[n1 + 1], R[n2 + 1];

    // preenche os vetores auxiliares
    // L = vetor[p...q]
    // R = vetor[q+1...r]
    for (int i = 0; i < n1; i++)
    {
        L[i].peso = grafo[p + i].peso; // sem o -1
        L[i].vertice1 = grafo[p + i].vertice1;
        L[i].vertice2 = grafo[p + i].vertice2;
        L[i].marcacao = grafo[p + i].marcacao;
    }

    for (int i = 0; i < n2; i++)
    {
        R[i].peso = grafo[q + i + 1].peso; // com o +1
        R[i].vertice1 = grafo[q + i + 1].vertice1;
        R[i].vertice2 = grafo[q + i + 1].vertice2;
        R[i].marcacao = grafo[q + i + 1].marcacao;
    }

    // o ultimo elemento dos vetores auxiliares é infinito (apenas para fins de parada)
    L[n1].peso = __INT_MAX__;
    L[n1].vertice1 = __INT_MAX__;
    L[n1].vertice2 = __INT_MAX__;
    L[n1].marcacao = __INT_MAX__;

    R[n2].peso = __INT_MAX__;
    R[n2].vertice1 = __INT_MAX__;
    R[n2].vertice2 = __INT_MAX__;
    R[n2].marcacao = __INT_MAX__;

    int i = 0; // começa de 0
    int j = 0; // começa de 0

    for (int k = p; k <= r; k++)
    {
        if (L[i].peso <= R[j].peso)
        { // se o i-ésimo elemento de L é menor, inserimos no vetor
            grafo[k].peso = L[i].peso;
            grafo[k].vertice1 = L[i].vertice1;
            grafo[k].vertice2 = L[i].vertice2;
            grafo[k].marcacao = L[i].marcacao;
            
            i++;
        }
        else
        {
            grafo[k].peso = R[j].peso;
            grafo[k].vertice1 = R[j].vertice1;
            grafo[k].vertice2 = R[j].vertice2;
            grafo[k].marcacao = R[j].marcacao;
            j++;
        }
    }
}
// complexidade = O(nlogn)
void mergeSort(Aresta *grafo, int comeco, int fim)
{
    if (comeco < fim)
    {
        int meio = (fim + comeco) / 2;

        mergeSort(grafo, comeco, meio);
        mergeSort(grafo, meio + 1, fim);
        merge(grafo, comeco, meio, fim); // O(n)
    }
}

Grafo Kruskal(Grafo g, int arestas, int vertices)
{
      /*cout << "Grafo original: \n";
    for(int i = 0; i < arestas; i++){
        cout << "(" << g.grafo[i].vertice1 << " , " << g.grafo[i].vertice2 << ")" << " = " << g.grafo[i].peso << endl;
    }*/
    mergeSort(g.grafo, 0, arestas - 1);
     /*cout << "\n\nGrafo ordenado: \n";
    for(int i = 0; i < arestas; i++){
        cout << "(" << g.grafo[i].vertice1 << " , " << g.grafo[i].vertice2 << ")" << " = " << g.grafo[i].peso << endl;
    }*/

    Grafo arvore;
    arvore.grafo = (Aresta*)malloc(sizeof(Aresta));
    int size_arvore = 0;

    iniciaPai(vertices);

    for (int i = 0; i < arestas; i++)
    {
        if (g.grafo[i].marcacao == 1)
        {      
            arvore.grafo = (Aresta*)realloc(arvore.grafo,(size_arvore + 1)*sizeof(Aresta));    
            arvore.grafo[size_arvore].vertice1 = g.grafo[i].vertice1;
            arvore.grafo[size_arvore].vertice2 = g.grafo[i].vertice2;
            arvore.grafo[size_arvore].peso = g.grafo[i].peso;
            size_arvore++;        
            join(g.grafo[i].vertice1, g.grafo[i].vertice2, vertices); // faz a união
        }else if(!same_set(g.grafo[i].vertice1,g.grafo[i].vertice2) && g.grafo[i].marcacao == 0)
        {
            
            arvore.grafo = (Aresta*)realloc(arvore.grafo,(size_arvore+1)*sizeof(Aresta));
            // se forem diferentes é porque NÃO forma ciclo, insere no vetor
            arvore.grafo[size_arvore].vertice1 = g.grafo[i].vertice1;
            arvore.grafo[size_arvore].vertice2 = g.grafo[i].vertice2;
            arvore.grafo[size_arvore].peso = g.grafo[i].peso;
            size_arvore++;
            join(g.grafo[i].vertice1,g.grafo[i].vertice2,vertices); // faz a união
        }
        
    }
    free(g.grafo);
    free(pai);
    free(arvore.grafo);
    
  return arvore;
}
