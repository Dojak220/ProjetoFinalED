#include <iostream>

using namespace std;

#define MAX1 1000



//questao a)
// complexidade O(logn)
void descer(int n, int heap[MAX1], int i){
	int filho = i*2;
	if (filho>0 && filho<=n){
		if (filho!=n){
			if (heap[filho+1]<heap[filho]) filho++;
		}
		if (heap[i]>heap[filho]){
			int aux = heap[i];
			heap[i] = heap[filho];
			heap[filho] = aux;
			descer(n, heap, filho);
		}
	}
}

// questao b)
// complexidade O(n)
void constroi(int n, int heap[MAX1]){
	for (int i=n/2; i>0; i--){
		descer(n, heap, i);
	}
}

// um teste simples
int main(int argc, char const *argv[])
{
	int heap[MAX1] = {-1,3,93,14,31,29,41,5,38};
	// a posiçao heap[0] é desconsiderada
	int n = 8;
	constroi(n,heap);
	for (int i=1; i<=n; i++){
		cout<<heap[i]<<" ";
	}
	cout<<endl;
	return 0;
}