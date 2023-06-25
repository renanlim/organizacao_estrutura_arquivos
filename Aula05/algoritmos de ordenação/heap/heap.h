#ifndef __HEAP_H__
#define __HEAP_H__ 
// A primeira linha utiliza uma diretiva de pré-processador "#ifndef" que verifica se a macro "HEAP_H" já foi definida previamente. Se não foi definida, a diretiva 
//"#define" define a macro "HEAP_H" para evitar que esse arquivo seja incluído novamente caso já tenha sido incluído em outro lugar do código.

#define N 2000

struct Heap
{
	int elementos[N];
	int qt;
};

Heap* criaHeap(); //A função "criaHeap" aloca memória para um novo heap e retorna um ponteiro para essa memória. 
void destroiHeap(Heap* h); //A função "destroiHeap" libera a memória alocada para um heap.
void insere(Heap* h, int x); //As funções "insere" e "remove" adicionam e removem elementos do heap, respectivamente. 
int remove(Heap* h);
void imprimeHeap(Heap* h); //E a função "imprimeHeap" imprime os elementos do heap.

#endif //a última linha fecha a diretiva "#ifndef" aberta no início do arquivo.


