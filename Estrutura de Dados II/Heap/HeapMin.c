#include <stdio.h>

int pai (int i) {
   return (i - 1)/2; 
}

void trocar (int V[], int a, int b) {
   int aux = V[a];
   V[a] = V[b];
   V[b] = aux;
}

void imprimir (int V[], int size) {
   int i;
   for (i = 0; i < size; i++) {
      printf("%d ", V[i]);
   }
   printf("\n");
}

int esquerda(int i){
	return ((i*2)+1);	
}

int direita(int i){
	return ((i*2)+2);
}

void maxHeapify(int v[], int size, int i){
	int esq = esquerda(i);
	int dir = direita(i);
	int maior = i;
	if((esq < size) && (v[esq] > v[i])){
		maior = esq;
	}
	else{
		maior = i;	
	}
	if((dir < size) && (v[dir] > v[maior])){
		maior = dir;
	}
	if(maior != i){
		trocar(v, i, maior);
		maxHeapify(v, size, maior);
	}
}

void buildMaxHeapify(int v[], int size){
	printf("Iniciando build max heapify\n");
	int i;
	for(i = (size/2) - 1; i >= 0; i--){
		maxHeapify(v, size, i);
	}
	printf("Build max heapify finalizdo.\n");
}

void heapSort(int v[], int size){
	printf("Iniciando heap sort.\n");
	int i;
	buildMaxHeapify(v, size);
	for(i = size-1; i > 0; i--){
		trocar(v, 0, i);
		size = i;
		maxHeapify(v, size, 0);
	}
	printf("Heap sort finalizado.\n");
}

void minHeapify(int v[], int size, int i){
	int esq = esquerda(i);
	int dir = direita(i);
	int menor = i;
	if((esq < size) && (v[esq] < v[i])){
		menor = esq;
	}
	else{
		menor = i;	
	}
	if((dir < size) && (v[dir] < v[menor])){
		menor = dir;
	}
	if(menor != i){
		trocar(v, i, menor);
		minHeapify(v, size, menor);
	}
}

void buildMinHeapify(int v[], int size){
	//printf("Iniciando build min heapify\n");
	int i;
	for(i = (size/2) - 1; i >= 0; i--){
		minHeapify(v, size, i);
	}
	//printf("Build min heapify finalizdo.\n");
}

int heapMinExtractMin(int v[], int size){
	if (size < 1){
		printf("erro: heap underflow.\n");
	}
	int min = v[0];
	v[0] = v[size -1];
	size = size-1;
	minHeapify(v, size, 0);
	return min;
}

int heapMinimum(int v[]){
	return v[0];
}

void heapMaxDecreaseKey(int v[], int size, int pos, int n_chave){
	if(n_chave > v[pos]){
		printf("Erro, nova chave menor que antiga.\n");
		return;
	}
	v[pos] = n_chave;
	maxHeapify(v, size, pos);
}

void heapMinDecreaseKey(int v[], int size, int pos, int n_chave){
	if(n_chave > v[pos]){
		printf("Erro, nova chave maior que antiga.\n");
		return;
	}
	v[pos] = n_chave;
	while(pos > 0 && v[pai(pos)] > v[pos]){
		trocar(v, pos, pai(pos));
		pos = pai(pos);
	}
}

void minHeapInsert(int v[], int size, int pos, int chave){
	 if(pos >= size){
		 printf("Erro em Min Heap Insert. Posicao maior que tamanho.\n");
		 return;
	 }
	 v[pos] = chave;
	 while(pos > 0 && v[pai(pos)] > v[pos]){
		trocar(v, pos, pai(pos));
		pos = pai(pos);
	}
}

int main () {
   int size = 10;

   int V[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
   printf("Vetor inicial : ");
   imprimir (V, size);
   
	buildMinHeapify(V, size);
	printf("Vetor apos Build Min Heapify : ");
   imprimir (V, size);
   
	/*
	heapSort (V, size);
	printf("Vetor ordenado: ");
   imprimir (V, size);
	*/

	heapMinExtractMin(V, size);
	size--;
	printf("Vetor apos Extract Min: ");
	imprimir(V, size);

	size++;
	heapMinDecreaseKey(V, size, 8, 1);
	printf("Vetor apos decreaseKey: ");
	imprimir(V, size);

	minHeapInsert(V, size, 9, 0);
	printf("Vetor apos Min Heap Insert 0 na posicao 9: ");
	imprimir(V, size);

   return 0;
}