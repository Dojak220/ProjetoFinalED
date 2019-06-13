#include <iostream>
#include <stdio.h>
#include <fstream>
#include "kruskal.h"
using namespace std;

int main()
{
    Grafo grafo1, grafo2, resultado, final[4], final2[100];
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
    memcpy(cpy, a, ele * sizeof *cpy);
    grafo2 = grafo3;
    grafo1 = grafo3;
    int soma = 0;
    int tamanho = sizeof(grafo3)/sizeof(int);
    cout << tamanho << endl;

    
    for (int i = 0; i < tamanho; i++)
    {
        if (grafo3.grafo[i].marcacao == 0)
        {

            grafo1.grafo[i].marcacao = 2;

            for (int j = 0; j < 4; j++)
            {
                g.grafo[i].marcacao = grafo1.grafo[i].marcacao;
                cout << grafo1.grafo[j].marcacao << " ";
            }
            cout << endl;

            for (int i = 0; i < cont; i++)
            {
                cout << "(" << g.grafo[i].vertice1 << " , " << g.grafo[i].vertice2 << ")"
                     << " = " << g.grafo[i].peso << " m " << g.grafo[i].marcacao << endl;
            }
            //final2[cont] = Kruskal(grafo1, g.m, g.n);
            //cont++;

            grafo2.grafo[i].marcacao = 1;

            grafo1 = grafo2;
        }
    }

    // for (int j = 0; j < cont; j++)
    // {
    //     for (int i = 0; i < 4; i++)
    //     {
    //         soma = soma + final2[j].grafo[i].peso;
    //     }
    //     cout << soma << endl;
    //     soma = 0;
    // }

    free(g.grafo);
}