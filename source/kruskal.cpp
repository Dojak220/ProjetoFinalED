/*
	Implementação do algoritmo de Kruskal
	Para detectar ciclos iremos utilizar o algoritmo Union-Find que detecta
	ciclos em grafos NÃO direcionados.
*/

#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
#define nVerticesMax 100


class Aresta
{
	int vertice1, vertice2;
    int peso;

public:

	Aresta(int v1 = 0, int v2 = 0, int peso = 0)
	{
		vertice1 = v1;
		vertice2 = v2;
		this->peso = peso;
	}

	int obterVertice1()
	{
		return vertice1;
	}

	int obterVertice2()
	{
		return vertice2;
	}

	int obterPeso()
	{
		return peso;
	}

    
        // sobrescrita do operador "<"
        bool operator < (const Aresta& aresta2) const
        {
            return (peso < aresta2.peso);
        }
    
	
};

class Grafo
{
	int N; // número de vértices
	//vector<Aresta> arestas; // vetor de arestas
    Aresta grafo[nVerticesMax];
	int N_atual;
	int pai[nVerticesMax];
	

public:

	Grafo(int N)
	{
		this->N = N;
	}

	int obterNumVertices()
	{
		return N;
	}

	// função que adiciona uma aresta
	void adicionarAresta(int v1, int v2, int peso){
		Aresta aresta_aux(v1, v2, peso);
		if(N_atual < N)
            grafo[N_atual++] = aresta_aux;
	}

    void inicializaPai(int pai[nVerticesMax]){
	   
	   	for(int i = 0; i < N; i++) {
		   pai[i] = i;
   		}
    }
	bool same_set(int x, int y){
    	if(pai[x] == pai[y]) return true;
    	else return false;
	}
	void join(int x, int y){
		int aux = pai[x];
		if(!same_set(x,y))
		{
			for (int i = 0; i < N; i++)
			{
				if (pai[i] == aux)
				{
					pai[i] = pai[y];
				}
			}
		}
	}

	static void merge (int p, int q, int r, Aresta grafo[]){
		Aresta *w;                                 //  1
		w = (Aresta *)malloc ((r-p) * sizeof (Aresta));     //  2
		int i = p, j = q;                       //  3
		int k = 0;                              //  4

		while (i < q && j < r) {                //  5
			if (grafo[i].obterPeso() <= grafo[j].obterPeso())  w[k++] = grafo[i++];  //  6
			else  w[k++] = grafo[j++];               //  7
		}                                       //  8
		while (i < q)  w[k++] = grafo[j++];         //  9
		while (j < r)  w[k++] = grafo[j++];         // 10
		for (i = p; i < r; ++i)  grafo[i] = w[i-p]; // 11
		free (w);                               // 12
	}
	void mergesort (int p, int r, Aresta grafo[]){
		if (p < r-1) {                 // 1
			int q = (p + r)/2;          // 2
			mergesort (p, q, grafo);        // 3
			mergesort (q, r, grafo);        // 4
			merge (p, q, r, grafo);     // 5
		}
	}

	/// função que roda o algoritmo de Kruskal
	void kruskal()
	{
		Aresta arvore[100];
		int size_arestas = obterNumVertices();

		int pai[nVerticesMax];
		inicializaPai(pai);
        
		// ordena as arestas pelo menor peso
		mergesort(0,N,this->grafo); //sort(arestas.begin(), arestas.end());

		int size = 0;
        for(int i = 0; i < size_arestas; i++)
		{
			
			if(!same_set(Grafo::grafo[i].obterVertice1(),Grafo::grafo[i].obterVertice2()))
			{
				// se forem diferentes é porque NÃO forma ciclo, insere no vetor
				arvore[++size] = this->grafo[i];
				join(this->grafo[i].obterVertice1(),Grafo::grafo[i].obterVertice2()); // faz a união
			}
		}

		//int size_arvore = arvore.size();

		// mostra as arestas selecionadas com seus respectivos pesos
		for(int i = 0; i < size; i++)
		{
			char v1 = 'A' + arvore[i].obterVertice1();
			char v2 = 'A' + arvore[i].obterVertice2();
			cout << "(" << v1 << ", " << v2 << ") = " << arvore[i].obterPeso() << endl;
		}
	}
};



int main(int argc, char *argv[])
{
	Grafo g(7); // grafo
	
	// adiciona as arestas
	g.adicionarAresta(0, 1, 7);
	g.adicionarAresta(0, 3, 5);
	g.adicionarAresta(1, 2, 8);
	g.adicionarAresta(1, 3, 9);
	g.adicionarAresta(1, 4, 7);
	g.adicionarAresta(2, 4, 5);
	g.adicionarAresta(3, 4, 15);
	g.adicionarAresta(3, 5, 6);
	g.adicionarAresta(4, 5, 8);
	g.adicionarAresta(4, 6, 9);
	g.adicionarAresta(5, 6, 11);
	
	g.kruskal(); // roda o algoritmo de Kruskal
	
	return 0;
}