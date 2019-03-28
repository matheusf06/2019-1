#include "arvore.h"

int main(int argc, char* argv[]){
    Arvore *a = constroi_arv ('a',
        constroi_arv('b',
        cria_arv_vazia(),
        constroi_arv('d',cria_arv_vazia(),cria_arv_vazia())
        ),
        constroi_arv('c',
        constroi_arv('e',cria_arv_vazia(),cria_arv_vazia()),
        constroi_arv('f',cria_arv_vazia(),cria_arv_vazia()))
    );

    imprimir_arv_pre(a);
    printf("\n");
    
    imprimir_arv_in(a);
    printf("\n");
    
    imprimir_arv_pos(a);
    printf("\n");
    
    imprimir_arv_marcadores(a);
    printf("\n");

    //printf("%d", pertence_arv(a, argv[1][0]));
    //printf("\n");

    printf("%d nos\n", conta_nos(a));
    printf("altura %d\n", calcula_altura_arvore(a));
    printf("%d nos folha\n", calcula_nos_folha(a));
    
    return 0;
}