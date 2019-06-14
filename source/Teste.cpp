#include <iostream>
#include "kruskal.h"
#include <fstream>
#include <string.h>

using namespace std;

typedef struct GrafoFinal
{
    Grafo final;
    int matAdj[35][35] = {0};
} GrafoFinal;

int main()
{
    ifstream infile("ex2.in");
    Grafo g;
    GrafoFinal gf = (GrafoFinal)malloc(sizeof(GrafoFinal));
    gf.final.grafo = (Aresta*)malloc(sizeof(Aresta));
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
    
    gf.final.grafo[0].marcacao=20;
    gf = (GrafoFinal*)realloc(gf,2*sizeof(GrafoFinal));
    gf[1].final.grafo = (Aresta*)malloc(sizeof(Aresta));
    gf[1].final.grafo[0].marcacao=20;
    gf = (GrafoFinal*)realloc(gf,3*sizeof(GrafoFinal));
    gf[2].final.grafo = (Aresta*)malloc(sizeof(Aresta));
    gf[2].final.grafo[0].marcacao=20;


}