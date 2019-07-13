#include <stdio.h>
#include <stdlib.h>

/*Estrutura para um nó em uma lista encadeada: */
typedef struct noA {
   int id;          /*Identificador armazenado no nó. */
   struct noA *next; /* Próximo nó na lista encadeada. */
   int peso;
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
   GrafoM *G = (GrafoM *)malloc(sizeof(GrafoM));
   G->E = 0;
   G->V = tamanho;
   G->Mat = (NoM **)malloc(tamanho * sizeof(NoM *));
   for (v = 0; v < G->V; v++) {
      G->Mat[v] = (NoM *)malloc(tamanho * sizeof(NoM));
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

void _arestaAdj(int u, int v, int peso, GrafoA *g){
   NoA* aux;
   NoA* ultimo;
   for(aux = g->Adj[u]; aux != NULL; aux = aux->next){
      if(aux->id == v){
         return;
      }
      ultimo = aux;
   }
   aux = (NoA*)malloc(sizeof(NoA));
   aux->id = v;
   aux->next = NULL;
   aux->peso = peso;
   if(g->Adj[u] == NULL){
      g->Adj[u] = aux;
   }
   else{
      ultimo->next = aux;
   }
   g->E++;
}

void arestaGrafoM(int u, int v, GrafoM *g){
   if(u < g->V && v < g->V){
      g->Mat[u][v].peso = 1;
      g->Mat[v][u].peso = 1;
      g->E++;
   }
}

void arestaDirecionalGrafoM(int u, int v, GrafoM*g){
   if(u < g->V && v < g->V){
      g->Mat[u][v].peso = 1;
      g->E++;
   }
}

void arestaGrafoAdj(int u, int v, GrafoA *g){
   _arestaAdj(u, v, 1, g);
   _arestaAdj(v, u, 1, g);
}

void pesoGrafoAdj(int u, int v, int peso, GrafoA *g){
   _arestaAdj(u, v, peso, g);
}

void pesoGrafoM(int u, int v, int peso, GrafoM *g){
   if(u < g->V && v < g->V){
      g->Mat[u][v].peso = peso;
      g->E++;
   }
}

void arestaDirecionalGrafoAdj(int u, int v, GrafoA *g){
   _arestaAdj(u, v, 1, g);
}

void printarAdj(GrafoA *g){
   int i;
   NoA* aux;
   for(i = 0; i < g->V; i++){
      aux = g->Adj[i];
      printf("%d -> ", i);
      while(aux != NULL){
         printf("%d (w:%d)  ", aux->id, aux->peso);
         aux = aux->next;
      }
      printf("\n");
   }
}

void printarMat(GrafoM *g){
   int i, j;
   printf("    ");
   for(i = 0; i < g->V; i++){
      printf("%d  ", i);
   }
   printf("\n\n");
   for(i = 0; i < g->V; i++){
      printf("%d   ", i);
      for(j = 0; j < g->V; j++){
         printf("%d  ", g->Mat[i][j].peso);
      }
      printf("\n");
   }
}

int incidentesAoVerticeAdj(int u, GrafoA *g){
   NoA* aux;
   int i;
   int contador = 0;
   if(u >= g->V){
      return -1;
   }
   
   for(i = 0; i < g->V; i++){
      for(aux = g->Adj[i]; aux != NULL; aux = aux->next){
         if(aux->id == u){
            contador++;
         }
      }
   }
   return contador;
}

int incidentesAoVerticeM(int u, GrafoM* g){
   int i;
   int contador = 0;
   if(u >= g->V){
      return -1;
   }
   
   for(i = 0; i < g->V; i++){
      if(g->Mat[i][u].peso != 0){
         contador++;
      }
   }
   return contador;
}

int adjacentesAoVerticeAdj(int u, GrafoA*g){
   NoA* aux;
   int contador = 0;
   if(u >= g->V){
      return -1;
   }
   for(aux = g->Adj[u]; aux != NULL; aux = aux->next){
      contador++;
   }
   return contador;
}

int adjacentesAoVerticeM(int u, GrafoM* g){
   int i;
   int contador = 0;
   if(u >= g->V){
      return -1;
   }
   
   for(i = 0; i < g->V; i++){
      if(g->Mat[u][i].peso != 0){
         contador++;
      }
   }
   return contador;
}

void printarAdjacentesM(int u, GrafoM*g){
   int i; 
   if(u >= g->V){
      return;
   }
   printf("Adjacentes ao vertice %d: ", u);
   for(i = 0; i < g->V; i++){
      if(g->Mat[u][i].peso != 0){
         printf("%d ", i);
      }
   }
}


void printarAdjacentesAdj(int u, GrafoA*g){
   NoA* aux;
   if(u >= g->V){
      return;
   }
   printf("Ajdacentes ao vertice %d: ", u);
   for(aux = g->Adj[u]; aux != NULL; aux = aux->next){
      printf("%d ", aux->id);
   }
}

GrafoA* criarTranspostoAdj(GrafoA* in){
   GrafoA* out = criar_grafo_adj(in->V);
   int i;
   NoA* aux;
   for(i = 0; i < in->V; i++){
      for(aux = in->Adj[i]; aux != NULL; aux = aux->next){
         pesoGrafoAdj(aux->id, i, aux->peso, out);
      }
   }
   return out;
}

GrafoM* criarTranspostoMat(GrafoM* in){
   GrafoM* out = criar_grafo_mat(in->V);
   int i, j;
   for(i = 0; i < in->V; i++){
      for(j = 0; j < in->V; j++){
         pesoGrafoM(j, i, in->Mat[i][j].peso, out);
      }
   }
   return out;
}

/* */
int main () {
   int va = 6;
   int vm = 6;
   GrafoA* ga= criar_grafo_adj(va);
   GrafoM* gm= criar_grafo_mat(vm);
   GrafoA* gat;
   GrafoM* gmt;

   pesoGrafoAdj(0, 1, 1, ga);
   pesoGrafoAdj(0, 5, 1, ga);
   pesoGrafoAdj(1, 2, 1, ga);
   pesoGrafoAdj(1, 3, 1, ga);
   pesoGrafoAdj(2, 0, 1, ga);
   pesoGrafoAdj(2, 4, 1, ga);
   pesoGrafoAdj(3, 2, 1, ga);
   pesoGrafoAdj(4, 3, 1, ga);
   pesoGrafoAdj(5, 4, 1, ga);

   pesoGrafoM(0, 1, 1, gm);
   pesoGrafoM(0, 5, 1, gm);
   pesoGrafoM(1, 2, 1, gm);
   pesoGrafoM(1, 3, 1, gm);
   pesoGrafoM(2, 0, 1, gm);
   pesoGrafoM(2, 4, 1, gm);
   pesoGrafoM(3, 2, 1, gm);
   pesoGrafoM(4, 3, 1, gm);
   pesoGrafoM(5, 4, 1, gm);
   
   printarAdj(ga);
   printarMat(gm);
  
   /* 
   printf("incidentes a 3 adj: %d\n", incidentesAoVerticeAdj(3, ga));
   printf("incidentes a 3 mat: %d\n", incidentesAoVerticeM(3, gm));
   printf("saem de 4 adj: %d\n", adjacentesAoVerticeAdj(4, ga));
   printf("saem de 4 mat: %d\n", adjacentesAoVerticeM(4, gm));
   printf("os adjacentes a 2 adj:");
   printarAdjacentesAdj(2, ga);
   printf("\nos adjacentes a 2 mat:");
   printarAdjacentesM(2, gm);
   */

   gat = criarTranspostoAdj(ga);
   gmt = criarTranspostoMat(gm);

   printarAdj(gat);
   printarMat(gmt);

   liberar_grafo_adj(ga);
   liberar_grafo_mat(gm);
   liberar_grafo_adj(gat);
   liberar_grafo_mat(gmt);

   return 0;
}
