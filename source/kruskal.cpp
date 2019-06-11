#include <iostream>
#include <algorithm>
#define MAX 100

using namespace std;

typedef struct Aresta{
    int vertice1, vertice2, peso;
}Aresta;

typedef struct Grafo{
    int n = 0, m = 0, N_atual = 0;// n -> n° vertices, m -> n° arestas
    Aresta grafo[MAX];
    int i = 0;

    void setNM(int n, int m){
        this->n = n;
        this->m = m;
    }
    void setAresta(int v1, int v2,int peso){
        if(N_atual > n)
            grafo[i].vertice1 = v1;
            grafo[i].vertice2 = v2;
            grafo[i].peso = peso;
            i++; N_atual++;
    }

}Grafo;

int pai[MAX];


// Inicia cada vértice como representante de si próprio.
void iniciaPai(int n){
    for(int i = 0; i <= n; i++){
        pai[i] = i;
    }
}
// Checa se dois vértices pertencem ao mesmo subset. Isso indica que, caso uma aresta seja colocada entre
// esses vértices, formará um ciclo, deixando, assim, de ser uma árvore.
bool same_set(int x, int y){
        cout << "\nEntrou same-set\n";
        if(pai[x] == pai[y]) return true;
        else return false;
}
// Faz com que o pai de y seja pai também de x e de todos os vértices que eram representados por x.
void join(int x, int y, int n){
    cout << "\nEntrou join\n";
    int aux = pai[x];
    for (int i = 0; i < n; i++) {
        if (pai[i] == aux) {
            pai[i] = pai[y];
        }
    }
}

// Merge genérico funcional
// Complexidade(O(n))
void merge(Aresta grafo[MAX], int p, int q, int r) {
    int n1 = q - p + 1; // limite do vetor esquerdo (L)
    int n2 = r - q; // limite do vetor direito (R)
    Aresta L[n1+1], R[n2+1];

    // preenche os vetores auxiliares
    // L = vetor[p...q]
    // R = vetor[q+1...r]
    for (int i = 0; i < n1; i++){
        L[i].peso = grafo[p+i].peso; // sem o -1
        L[i].vertice1 = grafo[p+i].vertice1;
        L[i].vertice2 = grafo[p+i].vertice2;
    }

    for (int i=0; i < n2; i++){
        R[i].peso = grafo[q+i+1].peso; // com o +1
        R[i].vertice1 = grafo[q+i+1].vertice1;
        R[i].vertice2 = grafo[q+i+1].vertice2;
    }

    // o ultimo elemento dos vetores auxiliares é infinito (apenas para fins de parada)
    L[n1].peso = __INT_MAX__; L[n1].vertice1 = __INT_MAX__; L[n1].vertice2 = __INT_MAX__;
    R[n2].peso = __INT_MAX__; R[n2].vertice1 = __INT_MAX__; R[n2].vertice2 = __INT_MAX__;

    int i=0; // começa de 0
    int j=0; // começa de 0

    for (int k=p; k<=r; k++){
        if (L[i].peso <= R[j].peso){ // se o i-ésimo elemento de L é menor, inserimos no vetor
            grafo[k].peso = L[i].peso;
            grafo[k].vertice1 = L[i].vertice1;
            grafo[k].vertice2 = L[i].vertice2;
            i++;
        } else {
            grafo[k].peso = R[j].peso;
            grafo[k].vertice1 = R[j].vertice1;
            grafo[k].vertice2 = R[j].vertice2;
            j++;
        }
    }
}
// complexidade = O(nlogn)
void mergeSort(Aresta grafo[MAX], int comeco, int fim){
    if (comeco < fim) {
        int meio = (fim+comeco)/2;

        mergeSort(grafo, comeco, meio);
        mergeSort(grafo, meio+1, fim);
        merge(grafo, comeco, meio, fim); // O(n)
    }
}

int main(){

    Grafo g;
    Grafo arvore;

    g.setNM(10,15);

    g.setAresta(0, 1, 6);
    g.setAresta(0, 3, 1);
    g.setAresta(0, 4, 4);
    g.setAresta(1, 2, 5);
    g.setAresta(1, 4, 1);
    g.setAresta(2, 5, 2);
    g.setAresta(3, 4, 8);
    g.setAresta(3, 6, 8);
    g.setAresta(4, 5, 5);
    g.setAresta(4, 6, 7);
    g.setAresta(4, 7, 1);
    g.setAresta(5, 8, 6);
    g.setAresta(6, 7, 10);
    g.setAresta(7, 8, 12);
    g.setAresta(7, 9, 7);

    for(int i = 0; i < g.m; i++){
        cout << "(" << g.grafo[i].vertice1 << " , " << g.grafo[i].vertice2 << ")" << " = " << g.grafo[i].peso << endl;
    }

    cout << endl << endl;

    mergeSort(g.grafo,0,g.m - 1);

    for(int i = 0; i < g.m; i++){
        cout << "(" << g.grafo[i].vertice1 << " , " << g.grafo[i].vertice2 << ")" << " = " << g.grafo[i].peso << endl;
    }

    int size_arvore = 0;

    iniciaPai(g.n);

    for(int i = 0; i < g.m; i++)
    {
        if(!same_set(g.grafo[i].vertice1,g.grafo[i].vertice2))
        {
            // se forem diferentes é porque NÃO forma ciclo, insere no vetor
            arvore.grafo[size_arvore].vertice1 = g.grafo[i].vertice1;
            arvore.grafo[size_arvore].vertice2 = g.grafo[i].vertice2;
            arvore.grafo[size_arvore].peso = g.grafo[i].peso;
            size_arvore++;

            join(g.grafo[i].vertice1,g.grafo[i].vertice2,g.n); // faz a união
        }
    }
    for(int i = 0; i < size_arvore; i++){
        cout << "(" << arvore.grafo[i].vertice1 << " , " << arvore.grafo[i].vertice2 << ")" << " = " << arvore.grafo[i].peso << endl;
    }
}
