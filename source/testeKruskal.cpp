#include <iostream>
#include "kruskal.h"
#include <fstream>

using namespace std;

int main()
{
    ifstream infile("../completo/22completo.in");
    Grafo g;
    g.aresta = (Aresta*)malloc(sizeof(Aresta));
    infile >> g.n;
    int a, b, c, d, cont = 0;
    while (infile >> a >> b >> c >>d)
    {
        g.aresta = (Aresta*)realloc(g.aresta,(cont+1)*sizeof(Aresta));
        g.aresta[cont].vertice1 = a;
        g.aresta[cont].vertice2 = b;
        g.aresta[cont].peso = c;
        cont++;
    }
    g.m = cont;
    
   Grafo resultado = Kruskal(g, g.m,g.n);

    int tamanho =sizeof(resultado)/sizeof(int);
    cout<<tamanho<<endl;
    cout << "\n\nÁrvore geradora: \n";
    for (int i = 0; i < g.n-1; i++)
    {
        cout << "(" << resultado.aresta[i].vertice1 << " , " << resultado.aresta[i].vertice2 << ")"
             << " = " << resultado.aresta[i].peso << endl;
    }
    free(g.aresta);
}
