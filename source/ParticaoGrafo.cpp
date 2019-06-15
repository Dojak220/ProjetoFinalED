#include <iostream>
#include <fstream>
#include "kruskal.h"
using namespace std;

//verifica se o grafo é conexo
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

//Função responsavel pela copia do Grafo2 no Grafo1
void clona_grafo(Grafo &grafo1, Grafo grafo2, int tamanho)
{
    for (int i = 0; i <= tamanho; i++)
    {
        grafo1.aresta = (Aresta *)realloc(grafo1.aresta, (i + 1) * sizeof(Aresta));
        grafo1.aresta[i].vertice1 = grafo2.aresta[i].vertice1;
        grafo1.aresta[i].vertice2 = grafo2.aresta[i].vertice2;
        grafo1.aresta[i].peso = grafo2.aresta[i].peso;
        grafo1.aresta[i].marcacao = grafo2.aresta[i].marcacao;
    }
    grafo1.n = grafo2.n;
    grafo1.m = grafo2.m;
}

//A Matriz representa as ligações de cada aresta. exemplo, uma aresta (3,4), na matrizo o par
//(linha, coluna) vai estar representado com o valor 1
//A função em si posiciona esses valores de acordo com o grafo de entrada
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

//Função responsavel por verificar quantas arestas opcionais existem na arvore geradora minima
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

void Particao(char *name)
{
    Grafo grafo1, grafo2;
    //exemplo de grafo
    //arquivo se encontra na pasta completo
    Grafo g;
    ifstream infile(name);
    infile >> g.n;
    int a, b, c, d, cont = 0;
    int matrizOriginal[35][35];

    //A partir do arquivo lido pela variavel infile, obtemos nosso grafo g
    while (infile >> a >> b >> c)
    {
        g.aresta = (Aresta *)realloc(g.aresta, (cont + 1) * sizeof(Aresta));
        g.aresta[cont].vertice1 = a;
        g.aresta[cont].vertice2 = b;
        matrizOriginal[a][b] = 1;
        matrizOriginal[b][a] = 1;
        g.aresta[cont].peso = c;
        cont++;
    }

    g.m = cont;

    Grafo original;

    //retorna a arvore geradora minima do grafo g
    Grafo grafo3 = Kruskal(g, g.m, g.n);

    //O grafo original recebe uma copia do grafo g
    clona_grafo(original, g, g.m);

    cont = 0;

    Grafo *final = (Grafo *)malloc(2 * sizeof(Grafo));
    clona_grafo(final[cont], grafo3, num_op(grafo3));
    clona_grafo(grafo1, grafo3, num_op(grafo3));
    clona_grafo(grafo2, grafo3, num_op(grafo3));

    // Parte responsavel pela organização dos dados e obtençao da arvore geradora minima do grafo g
    //e de sua partições
    for (int i = 0; i < final[0].n-1; i++)
    {
        int matrizVerif[35][35] = {0};

        if (final[0].aresta[i].marcacao == 0)
        {
            //seta a aresta mais "leve" como proibiga para aobtençao das partcoes e suas
            //respectivas arvores geradoras
            grafo1.aresta[i].marcacao = 2;

            for (int j = 0; j < final[0].n - 1; j++)
            {
                original.aresta[j].marcacao = grafo1.aresta[j].marcacao;
            }

            mudaMatriz(original.m, matrizVerif, original.aresta[i], matrizOriginal);

            //retorna a arvore geradora minima do grafo original
            Grafo mst = Kruskal(original, original.m, original.n);

            for (int j = 0; j < final[0].n - 1; j++)
            {
                if (original.aresta[j].marcacao == 2)
                    mst.aresta[j].marcacao = 2;
            }

            //verifica se o grafo é conexo
            if (connect(original.n, matrizVerif))
            {

                cont++;
                final = (Grafo *)realloc(final, (cont + 1) * sizeof(Grafo));
                clona_grafo(final[cont], mst, num_op(final[0]));
            }
            grafo2.aresta[i].marcacao = 1;
            clona_grafo(grafo1, grafo2, final[0].n - 1);
        }
    }
    int soma ;
    cout << " Arvore Gradora minima do grafo" << endl;
    //mostra os pontos das arvoes obtidas e seus pesos
    for (int i = 0; i <= cont; i++)
    {
        soma = 0;
        for (int j = 0; j < final[i].n - 1; j++)
        {
            cout <<"( "<< final[i].aresta[j].vertice1 << ", " << final[i].aresta[j].vertice2 << ") peso = "
                 << final[i].aresta[j].peso << endl;
            soma = soma + final[i].aresta[j].peso;
        }
        cout <<"custo = "<< soma << endl;
        if(i<cont)cout<< " Arvore Gradora minima da "<<i+1<<" partição"<<endl;
    }

    //libera a memoria utilizada
    free(final);
    free(g.aresta);
    free(grafo1.aresta);
    free(grafo2.aresta);
    free(grafo3.aresta);
}