#include <stdio.h>
#include <stdlib.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define NIL -1


/*Estrutura para um nó em uma lista encadeada: */
typedef struct noA {
   int id;          /*Identificador armazenado no nó. */
	int peso;
	struct noA *next; /* Próximo nó na lista encadeada. */
} NoA;

/*Estrutura de Grafo com lista de adjacências: */
typedef struct grafoA {
   int E; /* Quantidade de arestas. */
	// tamanho
   int V; /* Quantidade de vértices. */
   NoA **Adj; /* Lista de adjacências. */
} GrafoA;

/*Estrutura para um nó em uma matriz de adjacências: */
typedef struct noM {
   int peso;       /*Peso armazenado na aresta. */
} NoM;

typedef struct dfs{
	int cor;
	int pai;
	int finalizado;
	int descoberto;
} DFS;

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
	if(u < G->V && v < G->V){
  		G->Mat[u][v].peso = 1;
		G->Mat[v][u].peso = 1;
		G->E++;
	}
	else{
		printf("erro inserindo %d %d grafo\n", u, v);
	}
}

void adicionarPesoArestaGrafoMat(int u, int v, int peso, GrafoM *G){
	if(u < G->V && v < G->V){
			G->Mat[u][v].peso = peso;
			G->Mat[v][u].peso = peso;
			G->E++;
		}
		else{
			printf("erro inserindo %d %d grafo\n", u, v);
		}
}

void adicionarPesoArestaGrafoMatDirecionado(int u, int v, int peso, GrafoM *G){
	if(u < G->V && v < G->V){
			G->Mat[u][v].peso = peso;
			G->E++;
		}
		else{
			printf("erro inserindo %d %d grafo\n", u, v);
		}
}

void adicionarArestaGrafoMatDirecionado(int u, int v, GrafoM *G){
	if(u < G->V && v < G->V){
  		G->Mat[u][v].peso = 1;
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

void adicionarArestaGrafoAdjDirecionado(int u, int v, GrafoA *G){
	_adicionarArestaGrafoAdj(u, v, G);
}

void _adicionarPesoGrafoAdj(int u, int v, int peso, GrafoA *G){
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
	novo->peso = peso;
	novo->next = NULL;
	if(ultimo != NULL){
		ultimo->next = novo;
	}
	else{
		 G->Adj[u] = novo;
	}
}

void adicionarPesoArestaGrafoAdjDirecionado(int u, int v, int peso, GrafoA *G){
	_adicionarPesoGrafoAdj(u, v, peso, G);
}

void adicionarPesoArestaGrafoAdj(int u, int v, int peso, GrafoA *G){
	_adicionarPesoGrafoAdj(u, v, peso, G);
	_adicionarPesoGrafoAdj(v, u, peso, G);
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
	NoA* aux;
	for(i = 0; i < G->V; i++){
		printf("%d -> ", i);
		aux = G->Adj[i];
		while(aux != NULL){
			printf("%d ", aux->id);
			aux = aux->next;
		}
		printf("\n");
	}
}

void printGrafoAPesos(GrafoA *G){
	int i;
	NoA* aux;
	for(i = 0; i < G->V; i++){
		printf("%d -> ", i);
		aux = G->Adj[i];
		while(aux != NULL){
			printf("%d (w:%d)  ", aux->id, aux->peso);
			aux = aux->next;
		}
		printf("\n");
	}
}

int numeroDeArestasIncidentesSobreGrafoA(int u, GrafoA *G){
	int contador = 0;
	int i;
	NoA* aux;
	for(i = 0; i < G->V; i++){
		aux = G->Adj[i];
		while(aux != NULL){
			if(aux->id == u){
				contador++;
			}
			aux = aux->next;
		}
	}
	return contador;
}


int numeroDeArestasSaindoDeVerticeGrafoA(int u, GrafoA *G){
	int contador = 0;
	NoA* aux;
	aux = G->Adj[u];
	while(aux != NULL){
		contador++;
		aux = aux->next;
	}	
	return contador;
}

void verticesAdjacentesAoVerticeGrafoA(int u, GrafoA *G){
	NoA* aux;
	aux = G->Adj[u];
	while(aux != NULL){
		printf("%d, ", aux->id);
		aux = aux->next;
	}
}

void verticesAdjacentesAoVerticeGrafoM(int u, GrafoM *G){
	int i;
	for(i = 0; i < G->V; i++){
		if(G->Mat[u][i].peso != 0){
			printf("%d, ", i);
		}
	}
}

int numeroDeArestasIncidentesSobreGrafoM(int u, GrafoM *G){
	int contador = 0;
	int i;
	for(i = 0; i < G->V; i++){
		if(G->Mat[i][u].peso != 0){
			contador++;
		}
	}
	return contador;
}

int numeroDeArestasSaidoDeVerticeGrafoM(int u, GrafoM *G){
	int contador = 0;
	int i;
	for(i = 0; i < G->V; i++){
		if(G->Mat[u][i].peso != 0){
			contador++;
		}
	}
	return contador;
}

void Caminho_DFS(int NoInicial, DFS* V){
	int pai_do_inicial = V[NoInicial].pai;
	printf("Caminho: %d ", NoInicial);
	while(pai_do_inicial != NIL){
		printf("%d ", pai_do_inicial);
		pai_do_inicial = V[pai_do_inicial].pai;
	}
	printf("\n");
}

void DFS_Visit(GrafoA *G, int u, DFS* V, int *tempo){		
	V[u].cor = CINZA;
	(*tempo)++;
	V[u].descoberto = *tempo;
	NoA* hospede = G->Adj[u];
	while(hospede != NULL) {
		if(V[hospede->id].cor == BRANCO) {
			printf("Aresta arvore: ( %d -> %d )\n", u, hospede->id);
			V[hospede->id].pai = u;
			DFS_Visit(G, hospede->id, V, tempo);
		}
		else{
			printf("Aresta outra : ( %d -> %d )\n", u, hospede->id);
		}
		hospede = hospede->next;
	}
	(*tempo)++;
	V[u].cor = PRETO;
	V[u].finalizado = *tempo;
}

void Busca_Profundidade (GrafoA *G) {
	int u;
	DFS *V = (DFS *)malloc(G->V * sizeof(DFS)); 
		for (u = 0; u < G->V; u++) {
		V[u].cor = BRANCO;
		V[u].pai = NIL;
		V[u].descoberto = NIL;
		V[u].finalizado = NIL;
	}
	
	int tempo = 0;
	for (u = 0; u < G->V; u++) {
		if (V[u].cor == BRANCO) {
			DFS_Visit (G, u, V, &tempo);
		}
	}
	Caminho_DFS (3, V);
	Caminho_DFS (8, V);
	Caminho_DFS (11, V);
}


/* */
int main () {
	GrafoA* grafo = criar_grafo_adj(12);

	adicionarArestaGrafoAdjDirecionado(0, 1, grafo);
	adicionarArestaGrafoAdjDirecionado(0, 3, grafo);
	adicionarArestaGrafoAdjDirecionado(1, 2, grafo);
	adicionarArestaGrafoAdjDirecionado(2, 5, grafo);
	adicionarArestaGrafoAdjDirecionado(5, 4, grafo);
	adicionarArestaGrafoAdjDirecionado(5, 6, grafo);
	adicionarArestaGrafoAdjDirecionado(6, 4, grafo);
	adicionarArestaGrafoAdjDirecionado(6, 3, grafo);
	adicionarArestaGrafoAdjDirecionado(6, 0, grafo);
	adicionarArestaGrafoAdjDirecionado(4, 1, grafo);

	adicionarArestaGrafoAdjDirecionado(7, 8, grafo);

	adicionarArestaGrafoAdjDirecionado(9, 10, grafo);
	adicionarArestaGrafoAdjDirecionado(10, 11, grafo);
	adicionarArestaGrafoAdjDirecionado(11, 9, grafo);

	Busca_Profundidade(grafo);

	printGrafoA(grafo);

	liberar_grafo_adj(grafo);
}
	