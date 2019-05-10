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


int main () {

   int i;

   int size = 10;

   int V[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
  
   printf("Vetor inicial : ");
   imprimir (V, size);
   heapSort (V, size);
   printf("Vetor ordenado: ");
   imprimir (V, size);
  
   return 0;
}
