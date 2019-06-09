#include <stdio.h>
#include <stdlib.h>

/*Estrutura para um nó em uma lista encadeada: */
typedef struct noA {
   int id;          /*Identificador armazenado no nó. */
	int peso;
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


/* */
int main () {

   int Va = 6; /*Número de vértices*/
   GrafoA* Ga = criar_grafo_adj (Va);
	adicionarPesoArestaGrafoAdjDirecionado(0, 1, 1, Ga);	
	adicionarPesoArestaGrafoAdjDirecionado(0, 3, 5, Ga);
	adicionarPesoArestaGrafoAdjDirecionado(1, 3, 8, Ga);
	adicionarPesoArestaGrafoAdjDirecionado(2, 0, 5, Ga);
	adicionarPesoArestaGrafoAdjDirecionado(2, 3, 4, Ga);
	adicionarPesoArestaGrafoAdjDirecionado(3, 3, 6, Ga);
	adicionarPesoArestaGrafoAdjDirecionado(3, 4, 3, Ga);
	adicionarPesoArestaGrafoAdjDirecionado(4, 2, 7, Ga);
	adicionarPesoArestaGrafoAdjDirecionado(4, 5, 9, Ga);
	adicionarPesoArestaGrafoAdjDirecionado(5, 0, 2, Ga);

	printGrafoAPesos(Ga);
	printf("%d incidentes sobre %d\n", numeroDeArestasIncidentesSobreGrafoA(3, Ga), 3);
	printf("%d saem de %d\n", numeroDeArestasSaindoDeVerticeGrafoA(4, Ga), 4);
	printf("vertices adjacentes ao vertice 2: ");
	verticesAdjacentesAoVerticeGrafoA(2, Ga);
	printf("\n");
   liberar_grafo_adj (Ga);


   int Vm = 6; /*Número de vértices*/
   GrafoM* Gm = criar_grafo_mat (Vm);
	adicionarPesoArestaGrafoMatDirecionado(0, 1, 1, Gm);	
	adicionarPesoArestaGrafoMatDirecionado(0, 3, 5, Gm);
	adicionarPesoArestaGrafoMatDirecionado(1, 3, 8, Gm);
	adicionarPesoArestaGrafoMatDirecionado(2, 0, 5, Gm);
	adicionarPesoArestaGrafoMatDirecionado(2, 3, 4, Gm);
	adicionarPesoArestaGrafoMatDirecionado(3, 3, 6, Gm);
	adicionarPesoArestaGrafoMatDirecionado(3, 4, 3, Gm);
	adicionarPesoArestaGrafoMatDirecionado(4, 2, 7, Gm);
	adicionarPesoArestaGrafoMatDirecionado(4, 5, 9, Gm);
	adicionarPesoArestaGrafoMatDirecionado(5, 0, 2, Gm);

	printGrafoM(Gm);
	printf("%d incidentes sobre %d\n", numeroDeArestasIncidentesSobreGrafoM(3, Gm), 3);
	printf("%d saem de %d\n", numeroDeArestasSaidoDeVerticeGrafoM(4, Gm), 4);
	printf("vertices adjacentes ao vertice 2: ");
	verticesAdjacentesAoVerticeGrafoM(2, Gm);
	printf("\n");

   liberar_grafo_mat (Gm);

   return 0;
}