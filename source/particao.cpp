#include <iostream>
#include <stdio.h>
#include <fstream>
#include "kruskal.h"
using namespace std;

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
    grafo2.grafo = (Aresta *)malloc(sizeof(Aresta));
    grafo1.grafo = (Aresta *)malloc(sizeof(Aresta));
    for (int i = 0; i <= g.m; i++)
    {
        grafo2.grafo = (Aresta *)realloc(grafo2.grafo, (i + 1) * sizeof(Aresta));
        grafo2.grafo[i].vertice1 = grafo3.grafo[i].vertice1;
        grafo2.grafo[i].vertice2 = grafo3.grafo[i].vertice2;
        grafo2.grafo[i].peso = grafo3.grafo[i].peso;
        grafo2.grafo[i].marcacao = grafo3.grafo[i].marcacao;
    }
    for (int i = 0; i <= g.m; i++)
    {
        grafo1.grafo = (Aresta *)realloc(grafo1.grafo, (i + 1) * sizeof(Aresta));
        grafo1.grafo[i].vertice1 = grafo3.grafo[i].vertice1;
        grafo1.grafo[i].vertice2 = grafo3.grafo[i].vertice2;
        grafo1.grafo[i].peso = grafo3.grafo[i].peso;
        grafo1.grafo[i].marcacao = grafo3.grafo[i].marcacao;
    }

    int soma = 0;
    int tamanho = sizeof(grafo3)/sizeof(int);
    cout << tamanho << endl;
    Grafo final2[35];
    cont=0;

    grafo1.grafo[0].marcacao = 2;
    g.grafo[0].marcacao = grafo1.grafo[0].marcacao;
    for (int j = 0; j < 4; j++)
        {
            cout << g.grafo[j].marcacao << " ";
        }
        cout<<endl;
    for (int i = 0; i < tamanho-1; i++)
    {
        if (grafo3.grafo[i].marcacao == 0)
        {
            
            grafo1.grafo[i+1].marcacao = 2;
            grafo1.grafo[i].marcacao = 1;

            for (int j = 0; j < 4; j++)
            {
                g.grafo[j].marcacao = grafo1.grafo[j].marcacao;
            }
            for (int j = 0; j < 4; j++)
        {
            // g.grafo[i].marcacao = grafo1.grafo[i].marcacao;
            cout << g.grafo[j].marcacao << " ";
        }
        cout << endl;

            final2[cont] = Kruskal(grafo1, g.m, g.n);
            cont++;

            //grafo1.grafo[i].marcacao = grafo2.grafo[i].marcacao;
        }
    }
      
    free(g.grafo);
}