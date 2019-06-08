#include <stdio.h>
#include <stdlib.h>

/*Estrutura para um nó em uma lista encadeada: */
typedef struct noA {
   int id;          /*Identificador armazenado no nó. */
   struct noA *next; /* Próximo nó na lista encadeada. */
} NoA;

/*Estrutura de Grafo com lista de adjacências: */
typedef struct grafoA {
   int E; /* Quantidade de arestas. */
   int V; /* Quantidade de vértices. */
   NoA **Adj; /* Lista de adjacências. */
} GrafoA;

/*Estrutura para um nó em uma matriz de adjacências: */
typedef struct noM {
   int peso;       /*Peso armazenado na aresta. */
} NoM;

/*Estrutura de Grafo com matriz de adjacências: */
typedef struct grafoM {
   int E; /* Quantidade de arestas. */
   int V; /* Quantidade de vértices. */
   NoM **Mat; /* Matrix de adjacências. */
} GrafoM;

/*Função para criar um grafo com lista de adjacências.*/
GrafoA* criar_grafo_adj (int tamanho) {
   int v;
   GrafoA *G = (GrafoA *)malloc(sizeof(GrafoA));
   G->E = 0;
   G->V = tamanho;
   G->Adj = (NoA **)malloc(tamanho * sizeof(NoA *));
   for (v = 0; v < G->V; v++) {
      G->Adj[v] = NULL;
   }
   return G;
}

/*Função para criar um grafo com matriz de adjacências.*/
GrafoM* criar_grafo_mat (int tamanho) {
   int v;
   int i;
	GrafoM *G = (GrafoM *)malloc(sizeof(GrafoM));
   G->E = 0;
   G->V = tamanho;
   G->Mat = (NoM **)malloc(tamanho * sizeof(NoM *));
   for (v = 0; v < G->V; v++) {
      G->Mat[v] = (NoM *)malloc(tamanho * sizeof(NoM));
		for(i = 0; i < tamanho; i++){
			G->Mat[v][i].peso = 0;
		}
   }
   return G;
}

/*Função para destruir um grafo construído com lista de adjacências.*/
void liberar_grafo_adj (GrafoA *G) {
   int v;
   for (v = 0; v < G->V; v++) {
      if (G->Adj[v] != NULL) {
         free(G->Adj[v]);
      }
   }
   free(G->Adj);
   free(G);
}

/*Função para destruir um grafo construído com lista de adjacências.*/
void liberar_grafo_mat (GrafoM *G) {
   int v;
   for (v = 0; v < G->V; v++) {
      if (G->Mat[v] != NULL) {
         free(G->Mat[v]);
      }
   }
   free(G->Mat);
   free(G);
}

void adicionarArestaGrafoMat(int u, int v, GrafoM *G){
	if(G->Mat[u][v] < G->V && G->Mat[v][u] < G->V){
  		G->Mat[u][v].peso = 1;
		G->Mat[v][u].peso = 1;
		G->E++;
	}
	else{
		printf("erro inserindo %d %d grafo\n", u, v);
	}
}

void _adicionarArestaGrafoAdj(int u, int v, GrafoA *G){
	NoA *aux, *ultimo = NULL;
	for (aux = G->Adj[u]; aux != NULL; aux = aux->next){
		if(aux -> id == v){
			printf("a aresta (%d, %d) já existe!!!", u, v);
			return;
		}
		ultimo = aux;
	}
	NoA *novo = (NoA*)malloc(sizeof(NoA));
	novo->id = v;
	novo->next = NULL;
	if(ultimo != NULL){
		ultimo->next = novo;
	}
	else{
		 G->Adj[u] = novo;
	}
}

void adicionarArestaGrafoAdj(int u, int v, GrafoA *G){
	_adicionarArestaGrafoAdj(u, v, G);
	_adicionarArestaGrafoAdj(v, u, G);
}

void printGrafoM(GrafoM *G){
	int i;
	int j;
	printf("\t");
	
	for(i = 0; i < G->V; i++){
		printf("%d ", i);
	}
	printf("\n\n");


	for(i = 0; i < G->V; i++){
		printf("%d\t", i);

		for(j = 0; j < G->V; j++){
			printf("%d ", G->Mat[i][j].peso);
		}
		printf("\n");
	}		
}

void printGrafoA(GrafoA *G){
	int i;
	for(i = 0; i < G->V

/* */
int main () {

   int Va = 10; /*Número de vértices*/
   //GrafoA* Ga = criar_grafo_adj (Va);
  

   int Vm = 6; /*Número de vértices*/
   GrafoM* Gm = criar_grafo_mat (Vm);
	adicionarArestaGrafoAdj(1, 0, Ga);	
	adicionarArestaGrafoAdj(2, 0, Ga);
	adicionarArestaGrafoAdj(5, 0, Ga);
	adicionarArestaGrafoAdj(2, 1, Ga);
	adicionarArestaGrafoAdj(3, 1, Ga);
	adicionarArestaGrafoAdj(3, 2, Ga);
	adicionarArestaGrafoAdj(4, 2, Ga);
	adicionarArestaGrafoAdj(4, 3, Ga);
	adicionarArestaGrafoAdj(5, 4, Ga);

	printGrafoM(Gm);

   //liberar_grafo_adj (Ga);
   liberar_grafo_mat (Gm);

   return 0;
}

