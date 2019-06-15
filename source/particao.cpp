#include <iostream>

#include <fstream>
#include "kruskal.h"
using namespace std;

bool connect(int tam, int (*matAdj)[35])
{
    
    int ver = true;
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if (matAdj[i][j] == 1)
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
void clona_grafo(Grafo &grafo, Grafo grafo3, int tamanho)
{
    for (int i = 0; i <= tamanho; i++)
    {
        grafo.aresta = (Aresta *)realloc(grafo.aresta, (i + 1) * sizeof(Aresta));
        grafo.aresta[i].vertice1 = grafo3.aresta[i].vertice1;
        grafo.aresta[i].vertice2 = grafo3.aresta[i].vertice2;
        grafo.aresta[i].peso = grafo3.aresta[i].peso;
        grafo.aresta[i].marcacao = grafo3.aresta[i].marcacao;
    }
    grafo.n = grafo3.n;
    grafo.m = grafo3.m;
}
void mudaMatriz(int tam, int (*matAdj)[35], Aresta aresta, int mat[35][35])
{
    for (int i = 0; i < tam - 1; i++)
    {
        for (int j = 0; j < tam - 1; j++)
        {
            matAdj[i][j] = mat[i][j];
        }
    }
    matAdj[aresta.vertice1][aresta.vertice2] = 0;
    matAdj[aresta.vertice2][aresta.vertice1] = 0;
}
int num_op(Grafo grafo)
{
    int num = 0;
    for (int i = 0; i < grafo.n; i++)
    {
        if (grafo.aresta[i].marcacao == 0)
            num++;
    }
    return num - 1;
}

void mudarOrdem(Grafo *&pilha, int &cont, int tamanho)
{

    for (int i = 0; i < cont; i++)
    {
        clona_grafo(pilha[i], pilha[i + 1], tamanho);
    }
    cont--;
}

void imprimir(ofstream &tree, Grafo *final, Grafo *mst, int i)
{
    int soma = 0;

    for (int j = 0; j < final[i].n - 1; j++)
    {
        tree << final[i].aresta[j].vertice1 << " " << final[i].aresta[j].vertice2 << " "
             << final[i].aresta[j].peso << " " << final[i].aresta[j].marcacao << endl;
    }
    for (int j = 0; j < final[i].n - 1; j++)
        soma = soma + mst[i].aresta[j].peso;
    tree << soma << endl
         << endl;
    soma = 0;
}

int main()
{
    Grafo grafo1, grafo2;
    int contMat = 1;
    ofstream tree, tree2, ordemt;
    tree.open("Trees.txt");
    tree2.open("Trees2.txt");
    ordemt.open("ordemt.txt");
    ifstream infile2("ex2.in");

    Grafo g;

    infile2 >> g.n;
    int a, b, c, d, cont = 0;
    int matrizOriginal[35][35];

    while (infile2 >> a >> b >> c >> d)
    {
        g.aresta = (Aresta *)realloc(g.aresta, (cont + 1) * sizeof(Aresta));
        g.aresta[cont].vertice1 = a;
        g.aresta[cont].vertice2 = b;
        matrizOriginal[a][b] = 1;
        matrizOriginal[b][a] = 1;
        g.aresta[cont].peso = c;
        g.aresta[cont].marcacao = d;
        cont++;
    }

    g.m = cont;

    Grafo original;
    Grafo grafo3 = Kruskal(g, g.m, g.n);

    clona_grafo(original, g, g.m);
    free(g.aresta);

    cont = 0;

    Grafo *final = (Grafo *)malloc(2 * sizeof(Grafo));
    Grafo *pilha = (Grafo *)malloc(2 * sizeof(Grafo));
    clona_grafo(final[cont], grafo3, num_op(grafo3));
    clona_grafo(pilha[cont], grafo3, num_op(grafo3));

    do
    {

        clona_grafo(grafo1, pilha[0], num_op(pilha[0]));
        clona_grafo(grafo2, pilha[0], num_op(pilha[0]));
        cout<<"pilha[0] "<<num_op(pilha[0])<<endl;
        
        // for (int j = 0; j < original.n - 1; j++)
        // {
        //     cout << pilha[0].aresta[j].vertice1 << " " << pilha[0].aresta[j].vertice2 << " "
        //          << pilha[0].aresta[j].peso << " " << pilha[0].aresta[j].marcacao << endl;
        // }
        // cout << endl;
        
        for (int i = 0; i < 4; i++)
        {
            int matrizVerif[35][35] = {0};

            if (pilha[0].aresta[i].marcacao == 0 )
            {
                grafo1.aresta[i].marcacao = 2;
                cout<<"grafo1 "<<i<<endl;
                for (int j = 0; j < original.n - 1; j++)
                {
                    cout << grafo1.aresta[j].vertice1 << " " << grafo1.aresta[j].vertice2 << " "
                         << grafo1.aresta[j].peso << " " << grafo1.aresta[j].marcacao << endl;
                }
                cout << endl;

                for (int j = 0; j < pilha[0].n-1; j++)
                {
                        original.aresta[j].marcacao = grafo1.aresta[j].marcacao;
                }

                mudaMatriz(original.m, matrizVerif, original.aresta[i], matrizOriginal);

                Grafo mst = Kruskal(original, original.m, original.n);

                for (int j = 0; j < pilha[0].n-1; j++)
                {
                    if (original.aresta[j].marcacao == 2)
                        mst.aresta[j].marcacao = 2;
                }

                if (connect(original.n, matrizVerif))
                {
                    cout << "entrou salvar" << endl;
                    cont++;

                    pilha = (Grafo *)realloc(pilha, (cont + 1) * sizeof(Grafo));
                    clona_grafo(pilha[cont], original, original.n);

                    final = (Grafo *)realloc(final, (cont + 1) * sizeof(Grafo));
                    clona_grafo(final[cont], mst, num_op(final[0]));

                    imprimir(tree2, pilha, pilha, i + 1);
                    imprimir(tree, final, final, i + 1);
                }
                
                cout<<cont <<" "<<num_op(pilha[0])<<endl;
                
                    grafo2.aresta[i].marcacao = 1;
                    clona_grafo(grafo1, grafo2, pilha[0].n-1);
                
            }
            
        }

        mudarOrdem(pilha, cont, original.n - 1);

    } while (cont != 1);

    cont++;

    // for (int i = 0; i < cont; i++)
    // {
    //     for (int j = 0; j < cont - 1; j++)
    //     {
    //         cout << pilha[i].aresta[j].vertice1 << " " << pilha[i].aresta[j].vertice2 << " " << pilha[i].aresta[j].peso
    //              << " " << pilha[i].aresta[j].marcacao << endl;
    //     }
    //     cout << endl;
    // }

    tree.close();
    tree2.close();
    free(g.aresta);
    free(final);
    free(pilha);
    free(original.aresta);
}