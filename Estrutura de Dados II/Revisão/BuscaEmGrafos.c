#include <stdio.h>
#include <stdlib.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define NIL -1

/*Estrutura para um nó em uma lista encadeada: */
typedef struct _DFS {
   int cor;
   int pai;
   int d;
   int f;
} DFS;

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

/*-------------------------------*/
void inicializar_grafo_mat (GrafoM *G) {
   int u, v; 
   for (u = 0; u < G->V; u++) {
      for (v = 0; v < G->V; v++) {
         G->Mat[u][v].peso = 0;
      }
   } 
}

/*-------------------------------*/
void imprimir_grafo_mat (GrafoM *G) {
   int u, v; 
   printf ("Grafo (matriz adjacência):\n");
   printf ("    ");
   for (u = 0; u < G->V; u++) {
      printf ("%2d ", u);
   }
   printf ("\n\n");
   for (u = 0; u < G->V; u++) {
      printf ("%2d  ", u);
      for (v = 0; v < G->V; v++) {
         printf ("%2d ", G->Mat[u][v].peso);
      }
      printf ("\n");
   } 
   printf ("\n");
}

/*-------------------------------*/
void imprimir_grafo_adj (GrafoA *G) {
   int u; 
   printf ("Grafo (lista adjacência):\n");
   for (u = 0; u < G->V; u++) {
      printf ("%2d -> ", u);
      NoA *v;
      for (v = G->Adj[u]; v != NULL; v = v->next) {
         printf ("%2d ", v->id);
      }
      printf ("\n");
   } 
   printf ("\n");
}


/*-------------------------------*/
void _adicionar_aresta_grafo_mat (int u, int v, GrafoM *G) {
   if (G->Mat[u][v].peso == 0) {
      G->Mat[u][v].peso = 1;
   }
   else {
      printf("a aresta (%d,%d) já existe!!!", u, v);
   }
}

void adicionar_aresta_grafo_mat (int u, int v, GrafoM *G) {
   _adicionar_aresta_grafo_mat (u, v, G);
   _adicionar_aresta_grafo_mat (v, u, G);
   G->E++;
}

/*-------------------------------*/
void _adicionar_aresta_grafo_adj (int u, int v, GrafoA *G) {
   NoA *aux, *ultimo = NULL;
   for (aux = G->Adj[u]; aux != NULL; aux = aux->next) {
      if (aux->id == v) {
         printf("a aresta (%d,%d) já existe!!!", u, v);
         return;
      } 
      ultimo = aux;
   } 
   NoA *novo = (NoA *)malloc(sizeof(NoA));
   novo->id = v;
   novo->next = NULL;
   if (ultimo != NULL) {
      ultimo->next = novo;
   }
   else {
      G->Adj[u] = novo;
   }
}

void adicionar_aresta_grafo_adj (int u, int v, GrafoA *G) {
   _adicionar_aresta_grafo_adj (u, v, G);
   G->E++;
}

void DFS_Visit (GrafoA *G, int s, DFS *V, int *tempo) {
   NoA* aux;
   V[s].cor = CINZA;
   (*tempo) += 1;
   V[s].d = (*tempo);
   for(aux = G->Adj[s]; aux != NULL; aux = aux->next){
       if(V[aux->id].cor == BRANCO){
           printf("Aresta arvore: ( %d - %d )\n", s, aux->id);
           V[aux->id].pai = s;
           DFS_Visit(G, aux->id, V, tempo);
       }
       else{
           printf("Aresta outra : ( %d - %d )\n", s, aux->id);
       }
   }
   V[s].cor = PRETO;
   (*tempo) += 1;
   V[s].f = (*tempo);
}

void Caminho_DFS (int u, DFS *V) {
    printf("Caminho começando em %d: ", u);
    while(u != NIL){
        printf("%d ", u);
        u = V[u].pai;
    }
    printf("\n");
}

void Busca_Profundidade (GrafoA *G) {
   int u;

   DFS *V = (DFS *)malloc(G->V * sizeof(DFS));

   for (u = 0; u < G->V; u++) {
      V[u].cor = BRANCO; 
      V[u].pai = NIL; 
   }
    int tempo = 0;
    for (u = 0; u < G->V; u++) {
        if (V[u].cor == BRANCO) {
            DFS_Visit (G, u, V, &tempo);
        }
    }
   Caminho_DFS (3,V);
   Caminho_DFS (8,V);
   Caminho_DFS (11,V);
}

/* */
int main () {

   int V = 12; /*Número de vértices*/
   GrafoA* G = criar_grafo_adj (V);
   
   adicionar_aresta_grafo_adj (0, 1, G);
   adicionar_aresta_grafo_adj (0, 3, G);
   adicionar_aresta_grafo_adj (1, 2, G);
   adicionar_aresta_grafo_adj (2, 5, G);
   adicionar_aresta_grafo_adj (4, 1, G);
   adicionar_aresta_grafo_adj (5, 4, G);
   adicionar_aresta_grafo_adj (5, 6, G);
   adicionar_aresta_grafo_adj (6, 0, G);
   adicionar_aresta_grafo_adj (6, 3, G);
   adicionar_aresta_grafo_adj (6, 4, G);
   adicionar_aresta_grafo_adj (7, 8, G);
   adicionar_aresta_grafo_adj (9, 10, G);
   adicionar_aresta_grafo_adj (10, 11, G);
   adicionar_aresta_grafo_adj (11, 9, G);   

   Busca_Profundidade (G);  
 
   imprimir_grafo_adj (G);
   liberar_grafo_adj (G);

   return 0;
}
