#include <iostream>
#include "kruskal.h"
#include "ParticaoGrafo.h"
#include <fstream>

using namespace std;

int main()
{
    cout<<"Obtendo arvores geradoras para um grafo completo ..."<<endl;
    Particao("../completo/9completo.in");
    cout<<endl<<endl;
    cout<<"Obtendo arvores geradoras para um grafo Grid ..."<<endl;
    Particao("../grid/6grid.in");
    return 0;
}
