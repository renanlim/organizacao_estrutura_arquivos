#include "heap.h"
#include <iostream>

using namespace std;


//comando: g++ -o testeheap testeheap.cpp heap.cpp
int main()
{
	Heap* h = criaHeap(); 
	//a função main() cria um ponteiro para Heap chamado h e chama a função criaHeap(), 
	//que aloca espaço na memória para a estrutura Heap e inicializa o campo qt como 0.

	insere(h,10);
	insere(h,20);
	insere(h,50);
	insere(h,1);
	insere(h,2);
	insere(h,3);

	imprimeHeap(h);

	cout << remove(h) << endl;	
	cout << remove(h) << endl;	
	cout << remove(h) << endl;	
	cout << remove(h) << endl;	
	cout << remove(h) << endl;	
	cout << remove(h) << endl;	

	for(int i=0; i<6; i++) {
		cout << h->elementos[i] << ",";
	}
	cout << endl;

	destroiHeap(h);
	return 0;
}