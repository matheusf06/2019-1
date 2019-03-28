#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct arvore{
    int info;
    struct arvore* esq;
    struct arvore* dir;
} Arvore;

Arvore* inserir(Arvore* a, int v);
Arvore* remover(Arvore* a, int v);

void imprime_decrescente(Arvore* a);

Arvore* preencheNElementos(int n);
Arvore* preencheNAleatorios(int n);

int ancestral(Arvore* a, int e1, int e2);
int maior_ramo(Arvore* a);
int min_(Arvore* a);
int max_(Arvore* a);
int buscar(Arvore* a, int v);
//40 segundos para 100000 elementos ordenados
//0.4 segundos para 100000 elementos aleatorios

