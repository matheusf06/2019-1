#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY -99999

/* */
typedef struct _hash {
   int key;
   char *data;
} Hash;

/* Transforma uma chave em um índice no intervalo 0..M-1. */
int funcao_hash (int chave, int M) {
   return (chave % M);
}

int linear_probing (int chave, int iter, int M) {
   /*Completar!*/
   return (funcao_hash(chave, M) + iter) % M;
}

int quadratic_probing (int chave, int iter, int M) {
   /*Completar!*/
   int c1 = 1;
   int c2 = 2;
   return (funcao_hash(chave, M) + iter*c1 + iter*iter*c2)%M;
}

int double_hash (int chave, int iter, int M) {
   /*Completar!*/
   return (funcao_hash(chave, M) + iter*(1 + funcao_hash(chave, M-1)))%M;
}

/* */
Hash* create_hash (int M) { 
   int h;
   Hash *H = (Hash *)malloc(M * sizeof(Hash));
   for (h = 0; h < M; h++) {
      H[h].key = EMPTY;
      H[h].data = (char *)malloc(256 * sizeof(char));
      sprintf(H[h].data, " ");
   }
   return H;
}

/* */
void free_hash (Hash *H, int M) {
   int h;
   for (h = 0; h < M; h++) {
      free(H[h].data);
   }
   free(H);
}

/* */
int hash_search (Hash *H, int M, int key) {
   int j, i = 0;
   do {
      j = linear_probing (key, i, M);
      printf("Testando chave: %d\n", j);
      char skey[256];
      sprintf(skey, "%d", key);
      if (H[j].key == key) {
         return j;
      }
      i++;
   } while ((i != M) || strcmp(H[j].data,"") == 0);
}

int hash_delete (Hash *H, int M, int key) {
   int j = hash_search (H, M, key);
   sprintf(H[j].data, "DELETED");
}

/* */
int hash_insert (Hash *H, int M, int key, int *colisoes) {
   int j, i = 0;
   do {
      j = linear_probing (key, i, M);
      //j = quadratic_probing (key, i, M);
      //j = double_hash (key, i, M);
      if ((strcmp(H[j].data,"") == 0) || (strcmp(H[j].data,"DELETED") == 0)) {
         H[j].key = key;
         sprintf(H[j].data, "%d", key);
         return j;
      }
      else {
         *colisoes = *colisoes + 1;
      }
      i++;
   } while (i != M);
}

/* */
void hash_print (Hash *H, int M) {
   int i;
   for (i = 0; i < M; i++) {
      if (strcmp(H[i].data,"") != 0) {
         printf("%2d - %s\n", i, H[i].data);
      } 
   }
}

int main () {
   int colisoes = 0;
   int M = 11;
   Hash *H = create_hash (M);
   hash_insert (H, M, 10, &colisoes);
   hash_insert (H, M, 22, &colisoes);
   hash_insert (H, M, 31, &colisoes);
   hash_insert (H, M, 4, &colisoes);
   hash_insert (H, M, 15, &colisoes);
   hash_insert (H, M, 28, &colisoes);
   hash_insert (H, M, 17, &colisoes);
   hash_insert (H, M, 88, &colisoes);
   hash_insert (H, M, 59, &colisoes);
   printf("Número de colisões: %d\n", colisoes);
   //hash_delete (H, M, 59);
   //hash_insert (H, M, 59);
   hash_print (H, M);
   free_hash (H, M);
   return 0;
}