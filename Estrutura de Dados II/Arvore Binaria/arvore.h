#include <stdio.h>
#include <stdlib.h>

typedef struct arvore{
    char info;
    struct arvore *dir;
    struct arvore *esq;
} Arvore;

Arvore* cria_arv_vazia();
Arvore* constroi_arv(char info, Arvore* esq, Arvore* dir);

int pertence_arv(Arvore* a, char info);
int conta_nos(Arvore* a);
int calcula_altura_arvore(Arvore* a);
int calcula_nos_folha(Arvore* a);

void imprimir_arv_pre(Arvore* a);
void imprimir_arv_in(Arvore* a);
void imprimir_arv_pos(Arvore* a);
void imprimir_arv_marcadores(Arvore* a);
