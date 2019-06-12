#include<iostream>
#include "kruskal.h"
#include <fstream>

using namespace std;

int main()
{
    ifstream infile("exemplo.in");
    Grafo g;
    infile >> g.n;
    int a, b, c,cont=0;
    while (infile >> a >> b >> c)
    {
        g.grafo[cont].vertice1 = a;
        g.grafo[cont].vertice2 = b;
        g.grafo[cont].peso = c;
        cont++;
    }
    g.m = cont;

    Kruskal(g, g.m,g.n);

}
