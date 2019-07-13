#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
   char k[256];
   struct node *next;
} Node;

typedef struct hash {
    Node** list;
    int M;
} Hash;

/*...*/ 

void print_hash (Hash *H) {
   int h;
   for (h = 0; h < H->M; h++) {
      Node *aux;
      for (aux = H->list[h]; aux != NULL; aux = aux->next) {
         printf ("| %s ", aux->k);
      }
      printf ("| \n");
   }
}

Hash* create_hash(int m){
    int i;
    Hash* new_hash = (Hash*)malloc(sizeof(Hash));
    new_hash->list = (Node**)malloc(sizeof(Node*) * m);
    new_hash->M = m;
    for(i = 0; i < m; i++){
        new_hash->list[i] = NULL;
    }
    return new_hash;
}

void free_hash (Hash *H) {
   int h;
   for (h = 0; h < H->M; h++) {
      free (H->list[h]);
   }
   free(H->list);
   free (H);
}


int hash_function (char*v, int M){
    int i, h = v[0];
    for(i = 0; v[i] != '\0'; i++){
        h = (h*256 + v[i]) % M;
    }
    return h;
}


void insert_chained(Hash* h, char* str){
    int pos;
    Node* aux;
    pos = hash_function(str, h->M);
    aux = (Node*)malloc(sizeof(Node));
    aux->next =  h->list[pos];
    h->list[pos] = aux;
    strcpy(aux->k, str);
}

int main () {

   int M = 7;

   Hash *H = create_hash (M);
  
   insert_chained (H, "Marina");
   insert_chained (H, "Pedro");
   insert_chained (H, "Joana");
   insert_chained (H, "Thais");
   insert_chained (H, "Fabio");
   insert_chained (H, "Jonas");
   insert_chained (H, "Henrique");
   
   /*...*/ 
   
   print_hash (H);

   free_hash (H);
 
   return 0;
}