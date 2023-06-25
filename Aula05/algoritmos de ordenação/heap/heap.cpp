#include "heap.h" //inclui o arquivo
#include <iostream>


//////////São as implementações///////////
using namespace std;

Heap* criaHeap()
{
	Heap *h = new Heap; //cria na memoria
	h->qt = 0;			//Aloca memória para uma estrutura do tipo Heap, inicializa sua quantidade de elementos em 0 e retorna um ponteiro para essa estrutura.
	return h;
}

void destroiHeap(Heap* h)
{
	delete h;
}

void insere(Heap* h, int x) //recebe um ponteiro para uma estrutura do tipo Heap e um inteiro x a ser inserido na Heap. 
{
	int pai, filho, aux;

	filho = h->qt; 
	h->elementos[filho] = x;  //Ela insere o elemento x na posição h->qt (a última posição do array)
	h->qt++; //incrementa a quantidade de elementos qt

	/*h->elementos[h->qt] = x; // coloca novo no final do array
	filho = h->qt; // indice do filho
	h->qt++;*/

	while(filho > 0) // ela verifica se o pai desse elemento é menor que ele
	{
		pai = ((filho+1)/2)-1; //indice do pai
		if(h->elementos[pai] < h->elementos[filho]) //se o pai for menor que o filho --> troca
		{ //Ela troca o pai com o elemento e atualiza o índice do filho para o índice do pai, 
		//verificando novamente se o pai desse novo elemento é menor que ele. 
			aux = h->elementos[pai];
			h->elementos[pai] = h->elementos[filho];
			h->elementos[filho] = aux;
			filho = pai; //filho vira pai
		}
		else
		{
			break;
		}
		//Esse processo é repetido até que o elemento esteja em sua posição correta na Heap.
	}
}

int remove(Heap* h) //A função remove() remove o elemento de maior valor (raiz da Heap) e retorna o valor removido
{
	int resposta, pai, filho1, filho2, maiorFilho, aux;
	//Ela substitui a raiz pelo último elemento da Heap, decrementa a quantidade de elementos qt e rearranja a Heap a partir da raiz. 
	resposta = h->elementos[0]; //elemento 0 porque o maior elemento está no inicio MaxHeap
	h->elementos[0] = h->elementos[h->qt-1]; //ultimo elemento que ocupa o 1º lugar
	h->elementos[h->qt-1] = resposta; //armazena no array que está na memoria e sai do heap
	h->qt--;
	// Esse rearranjo envolve verificar se o filho da esquerda e da direita da raiz são maiores que ela. Se um dos filhos for maior, 
	//ela troca a posição do maior filho com a posição da raiz, atualiza o índice da raiz para o índice do maior filho e continua verificando 
	//e trocando até que a Heap esteja novamente em sua forma correta.
	pai = 0; //ajuste de cima para baixo
	filho1 = 2*(pai+1)-1; //conversão de quadro para codigo 
	filho2 = filho1+1;
	while(filho1<h->qt) //tenho um filho
	{
		if(filho2<h->qt) //tenho dois filhos
		{
			if(h->elementos[filho1]>h->elementos[filho2]) //candidato a subir é o maior filho entre os dois
			{
				maiorFilho = filho1;
			}
			else
			{
				maiorFilho = filho2;
			}
		}
		else //nao tenho filho2, logo filho1 é o maiorfilho
		{
			maiorFilho = filho1;
		}
		if(h->elementos[pai]<h->elementos[maiorFilho]) //verificar se o maiorfilho é maior que o pai --> troca se for
		{
			aux = h->elementos[pai]; //pai passa a ser o maiorfilho
			h->elementos[pai] = h->elementos[maiorFilho];
			h->elementos[maiorFilho] = aux;
			pai = maiorFilho;
			filho1 = 2*(pai+1)-1;
			filho2 = filho1+1;
		}
		else
		{
			break;
		}
	}

	return resposta;
}

void imprimeHeap(Heap *h) //A função imprimeHeap() recebe um ponteiro para uma estrutura do tipo Heap e imprime seus elementos em ordem.
{
	int i;
	for(i=0; i<h->qt; i++)
	{
		cout << h->elementos[i] << ", ";
	}
	cout << endl;

}

//Por fim, há a diretiva de fim do arquivo #endif, que fecha o bloco #ifndef/HEAP_H. Essa diretiva serve para garantir que o arquivo header "heap.h" 
//só será incluído uma vez em cada arquivo fonte.