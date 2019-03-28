#include "arvore_de_busca.h"

int main () {
    Arvore *a = NULL;
    a = inserir (a, 50);
    a = inserir (a, 30);
    a = inserir (a, 90);
    a = inserir (a, 20);
    a = inserir (a, 40);
    a = inserir (a, 95);
    a = inserir (a, 10);
    a = inserir (a, 35);
    a = inserir (a, 45);

    printf("%d", ancestral(a, 10, 14));
}