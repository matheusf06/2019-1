#include <stdio.h>
#include "arvore_de_busca.h"

int main () {
    Arvore *b = NULL;
    b = inserir (b, 10);
    b = inserir (b, 15);
    b = inserir (b, 16);
    b = inserir (b, 11);
    b = inserir (b, 12);
    b = inserir (b, 14);
    b = inserir (b, 13);
    b = remover(b, 15);
    //imprime_pre_ordem(a); 
    //printf("\n");	
    imprime_pre_ordem(b);	
}
