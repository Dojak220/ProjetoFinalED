#include <iostream>

#include <fstream>
#include "kruskal.h"
using namespace std;
typedef struct GrafoFinal
{
    Grafo final;
    int matAdj[35][35] = {0};
} GrafoFinal;


bool connect(GrafoFinal verif, int tam)
{
    int ver = true;
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (verif.matAdj[i][j] == 1)
            {
                ver = true;
                break;
            }
            else
                ver = false;
        }
    }
    return ver;
}
void clona_grafo(Grafo &grafo, Grafo &grafo3, int tamanho)
{
    for (int i = 0; i <= tamanho; i++)
    {
        grafo.grafo = (Aresta *)realloc(grafo.grafo, (i + 1) * sizeof(Aresta));
        grafo.grafo[i].vertice1 = grafo3.grafo[i].vertice1;
        grafo.grafo[i].vertice2 = grafo3.grafo[i].vertice2;
        grafo.grafo[i].peso = grafo3.grafo[i].peso;
        grafo.grafo[i].marcacao = grafo3.grafo[i].marcacao;
    }
    grafo.n = grafo3.n;
    grafo.m = grafo3.m;
}
void mudaMatriz(int tam, GrafoFinal &GF, Aresta aresta, int mat[35][35], int muda)
{

    // for (int i = 0; i < tam; i++)
    // {
    //     for (int j = 0; j < tam; j++)
    //     {
    //         cout << mat[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    if (muda == 0)
    {
        for (int i = 0; i < tam - 1; i++)
        {
            for (int j = 0; j < tam - 1; j++)
            {
                GF.matAdj[i][j] = mat[i][j];
            }
        }
        GF.matAdj[aresta.vertice1][aresta.vertice2] = 0;
        GF.matAdj[aresta.vertice2][aresta.vertice1] = 0;
    }
    if (muda == 1)
    {
        GF.matAdj[aresta.vertice1][aresta.vertice2] = 1;
        GF.matAdj[aresta.vertice2][aresta.vertice1] = 1;
    }
    // for (int i = 0; i < tam; i++)
    // {
    //     for (int j = 0; j < tam; j++)
    //     {
    //         cout << GF.matAdj[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;
}
int num_op(Grafo grafo)
{
    int num = 0;
    for (int i = 0; i < grafo.n; i++)
    {
        if (grafo.grafo[i].marcacao == 0)
            num++;
    }
    return num - 1;
}
void adicionar(){}
int main()
{
    Grafo grafo1, grafo2;
    int contMat = 1;

    ofstream tree;
    tree.open("Trees.txt");
    ifstream infile2("ex2.in");

    Grafo g;
    g.grafo = (Aresta *)malloc(sizeof(Aresta));

    GrafoFinal *GF = (GrafoFinal *)malloc(2*sizeof(GrafoFinal));;

    infile2 >> g.n;
    int a, b, c, d, cont = 0;
    int matrizOriginal[35][35];

    while (infile2 >> a >> b >> c >> d)
    {
        g.grafo = (Aresta *)realloc(g.grafo, (cont + 1) * sizeof(Aresta));
        g.grafo[cont].vertice1 = a;
        g.grafo[cont].vertice2 = b;
        matrizOriginal[a][b] = 1;
        matrizOriginal[b][a] = 1;
        g.grafo[cont].peso = c;
        g.grafo[cont].marcacao = d;
        cont++;
    }

    g.m = cont;

    tree << g.n << " " << g.m << endl;

    Grafo original;
    original.grafo = (Aresta *)malloc(sizeof(Aresta));

    Grafo grafo3 = Kruskal(g, g.m, g.n);
    clona_grafo(original, g, g.m);

    grafo2.grafo = (Aresta *)malloc(sizeof(Aresta));
    grafo1.grafo = (Aresta *)malloc(sizeof(Aresta));
    clona_grafo(grafo1, grafo3, num_op(grafo3));
    clona_grafo(grafo2, grafo3, num_op(grafo3));

    cont = 0;
    clona_grafo(GF[cont].final,original,num_op(original));
    
    for (int i = 0; i < num_op(grafo3); i++)
    {
        if (grafo3.grafo[i].marcacao == 0)
        {
            grafo1.grafo[i].marcacao = 2;

            for (int j = 0; j < grafo3.n-1; j++)
            {
                original.grafo[j].marcacao = grafo1.grafo[j].marcacao;
            }

            Grafo mst = Kruskal(original, 10, 5);
            clona_grafo(GF[cont].final, mst, mst.n-1);
            mudaMatriz(original.m, GF[cont], grafo1.grafo[i], matrizOriginal, 0);

            if (connect(GF[cont], original.n))
            {
                for (int j = 0; j < grafo3.n-1; j++)
                {
                    if (original.grafo[j].marcacao == 2)
                    {
                        GF[cont].final.grafo[j].marcacao = 2;
                    }
                }
                cont++;
                GF = (GrafoFinal *)realloc(GF, (cont + 1) * sizeof(GrafoFinal));
                mudaMatriz(original.m, GF[cont - 1], grafo1.grafo[i], GF[cont - 1].matAdj, 1);
            }

            grafo2.grafo[i].marcacao = 1;
            clona_grafo(grafo1, grafo2, (sizeof(grafo2) / sizeof(int)));
        }
    }
    int soma = 0;
    for (int i = 0; i < cont; i++)
    {
        for (int j = 0; j < cont; j++)
        {
            tree << GF[i].final.grafo[j].vertice1 << " " << GF[i].final.grafo[j].vertice2 << " " << GF[i].final.grafo[j].peso << " " << GF[i].final.grafo[j].marcacao << endl;
            soma = soma + GF[i].final.grafo[j].peso;
        }
        tree << soma << endl;
        soma = 0;
        tree << "-1" << endl
             << endl;
    }

    tree.close();
    free(g.grafo);
    free(original.grafo);
}