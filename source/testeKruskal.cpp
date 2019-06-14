#include <iostream>
#include "kruskal.h"
#include <fstream>

using namespace std;

int main()
{
    ifstream infile("../completo/22completo.in");
    Grafo g;
    g.grafo = (Aresta*)malloc(sizeof(Aresta));
    infile >> g.n;
    int a, b, c, d, cont = 0;
    while (infile >> a >> b >> c)
    {
        g.grafo = (Aresta*)realloc(g.grafo,(cont+1)*sizeof(Aresta));
        g.grafo[cont].vertice1 = a;
        g.grafo[cont].vertice2 = b;
        g.grafo[cont].peso = c;
        cont++;
    }
    g.m = cont;
    
   Grafo resultado = Kruskal(g, g.m,g.n);

    int tamanho =sizeof(resultado)/sizeof(int);
    cout<<tamanho<<endl;
    cout << "\n\nÁrvore geradora: \n";
    for (int i = 0; i < g.n-1; i++)
    {
        cout << "(" << resultado.grafo[i].vertice1 << " , " << resultado.grafo[i].vertice2 << ")"
             << " = " << resultado.grafo[i].peso << endl;
    }
    free(g.grafo);
}
