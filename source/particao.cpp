#include <iostream>
#include <stdio.h>
#include <fstream>
#include "kruskal.h"
using namespace std;
void set_grafo(Grafo &grafo, Grafo &grafo3){
    for (int i = 0; i <= grafo.m; i++)
    {
        grafo.grafo = (Aresta *)realloc(grafo.grafo, (i + 1) * sizeof(Aresta));
        grafo.grafo[i].vertice1 = grafo3.grafo[i].vertice1;
        grafo.grafo[i].vertice2 = grafo3.grafo[i].vertice2;
        grafo.grafo[i].peso = grafo3.grafo[i].peso;
        grafo.grafo[i].marcacao = grafo3.grafo[i].marcacao;
    }
}
int main()
{
    Grafo grafo1, grafo2;
    ifstream infile2("ex2.in");
    Grafo g;
    g.grafo = (Aresta *)malloc(sizeof(Aresta));
    infile2 >> g.n;
    int a, b, c, d, cont = 0;
    while (infile2 >> a >> b >> c >> d)
    {
        g.grafo = (Aresta *)realloc(g.grafo, (cont + 1) * sizeof(Aresta));
        g.grafo[cont].vertice1 = a;
        g.grafo[cont].vertice2 = b;
        g.grafo[cont].peso = c;
        g.grafo[cont].marcacao = d;
        cont++;
    }
    g.m = cont;

    Grafo grafo3 = Kruskal(g, g.m, g.n);
    grafo2.grafo = (Aresta*)malloc(sizeof(Aresta));
    grafo1.grafo = (Aresta*)malloc(sizeof(Aresta));
    Grafo *lista = (Grafo*)malloc(sizeof(Grafo));

    set_grafo(grafo2,grafo3);
    set_grafo(grafo1,grafo3);
    
    int soma = 0;
    int tamanho = sizeof(grafo3) / sizeof(int);
    cout << tamanho << endl;
    cont = 0;
    grafo1.grafo[0].marcacao = 2;
    g.grafo[0].marcacao = grafo1.grafo[0].marcacao;
    Grafo hhhh;
    hhhh.grafo = (Aresta*)malloc(sizeof(Aresta));
    set_grafo(hhhh,grafo3);
    for (int j = 0; j < tamanho; j++)
            {
                cout << hhhh.grafo[j].peso << " ";
            }
    cout << endl;
    for (int i = 0; i < tamanho - 1; i++)
    {
        if (grafo3.grafo[i].marcacao == 0)
        {

            grafo1.grafo[i + 1].marcacao = 2;
            grafo1.grafo[i].marcacao = 1;

            for (int j = 0; j < 4; j++)
            {
                g.grafo[j].marcacao = grafo1.grafo[j].marcacao;
            }
        }
        
    }
    
            
            
    free(g.grafo);
}