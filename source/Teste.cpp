#include <iostream>
#include "kruskal.h"
#include <fstream>

using namespace std;

int main()
{
    ifstream infile("ex2.in");
    Grafo g;
    g.grafo = (Aresta*)malloc(sizeof(Aresta));
    infile >> g.n;
    int a, b, c, d, cont = 0;
    while (infile >> a >> b >> c >>d)
    {
        g.grafo = (Aresta*)realloc(g.grafo,(cont+1)*sizeof(Aresta));
        g.grafo[cont].vertice1 = a;
        g.grafo[cont].vertice2 = b;
        g.grafo[cont].peso = c;
        g.grafo[cont].marcacao = d; 
        cont++;
        
    }
    g.m = cont;
    
    for (int i = 0; i < g.m; i++)
    {
        cout << "(" << g.grafo[i].vertice1 << " , " << g.grafo[i].vertice2 << ")"
             << " = " << g.grafo[i].peso << endl;
    }
}
