#include "arvore_de_busca.h"

int main () {
    Arvore *a = NULL;
    a = inserir (a, 20);
    a = inserir (a, 8);
    a = inserir (a, 4);
    a = inserir (a, 12);
    a = inserir (a, 10);
    a = inserir (a, 14);
    a = inserir (a, 22);

    printf("%d", ancestral(a, 10, 14));
}