#include<iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
ofstream grid, completo;

void GrafoCompleto(int n)
{
    string name = to_string(n) +"completo.in";
    completo.open(name);
    completo << n<<endl;

    for(int i=0; i<n; i++)
    {
        for(int j=i; j<n; j++)
        {
            completo << i + 1 <<" "<< j + 1 <<" "<< (rand() % 100) + 1 <<endl;
        }
    }
    completo.close();
}

void GrafoGrid(int n)
{

    string name = to_string(n) +"grid.in";
    grid.open(name);
    grid<<n<<endl;

    int meio = n/2;
    for(int i = 1; i<meio; i++)
    {
        grid<< i <<" "<<i+1<<" "<< (rand() % 100) + 1<<endl;
    }
    for(int i = meio+1; i<n; i++)
    {
        grid<< i <<" "<<i+1<<" "<< (rand() % 100) + 1<<endl;
    }
    for(int i = 0, meio2 = meio; i<meio; i++, meio2++)
    {
        grid<< i + 1 <<" "<<meio2+1<<" "<< (rand() % 100) + 1<<endl;
    }
    grid.close();
}

int main()
{


    for(int i=0; i<5;i++){
    int num = (rand() % 15) + 1;
    GrafoCompleto(num);
    }

     for(int i=0; i<10;i++){
    int num = (rand() % 15) + 1;
    GrafoGrid(num);
    }
    return 0;
}
