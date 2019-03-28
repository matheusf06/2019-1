
#include "arvore.h"

Arvore *constroi_arv(char info, Arvore* esq, Arvore* dir){
    Arvore *a = (Arvore*)malloc(sizeof (Arvore));
    a->info = info;
    a->esq = esq;
    a->dir = dir;

    return a;
}

Arvore *cria_arv_vazia(){
    return NULL;
}

void imprimir_arv_pre(Arvore* a){
    //printa recursivamente a info do 
    //proprio, esquerdo, direito

    if(a){
        printf("%c, ", a->info);
        imprimir_arv_pre(a->esq);
        imprimir_arv_pre(a->dir);
    }
}

void imprimir_arv_in(Arvore* a){
    //printa recursivamente a info do 
    //esquerdo, proprio, direito

    if(a){
        imprimir_arv_in(a->esq);
        printf("%c, ", a->info);
        imprimir_arv_in(a->dir);
    }
}

void imprimir_arv_pos(Arvore* a){
    //printa recursivamente a info do 
    //esquerdo, direito, proprio  

    if(a){
        imprimir_arv_pos(a->esq);
        imprimir_arv_pos(a->dir);
        printf("%c, ", a->info);
    }
}   

void imprimir_arv_marcadores(Arvore* a){
    //printa recursivamente a info do 
    //proprio, esquerdo, direito   
    //com < ao inicio da chamada recursiva
    //e > ao termino. 
    
    printf("<");
    if(a){
        printf("%c", a->info);
        imprimir_arv_marcadores(a->esq);
        imprimir_arv_marcadores(a->dir);
    }
    printf(">");
}

int pertence_arv(Arvore* a, char c){
    //percorre recursivamente a arvore
    //procurando a info no proprio no
    //entao nos filhos e caso encontre,
    //é gerado uma reaçao encadeada de
    //retornos 1.
    
    if(a){
        if(a->info == c ||
           pertence_arv(a->esq, c) ||
           pertence_arv(a->dir, c)){
            return 1;
        }
    }
    return 0;
}

int conta_nos(Arvore* a){
    //percorre recursivamente a arvore
    //acrescentando 1 ou 0 (caso o nó seja nulo)
    //a cada chamada 

    if(a){
        return (conta_nos(a->esq) + conta_nos(a->dir) + 1);
    }
    return 0;
}

int calcula_altura_arvore(Arvore* a){
    //percorre recursivamente a arvore 
    //até encontrar o nó mais profundo 
    //da esquerda e direita entao,
    //começando em -1 é acrescentado +1
    //a cada retorno da funçao, até a 
    //primeira chamada.

    if(a){
        int alt_esq = calcula_altura_arvore(a->esq);
        int alt_dir = calcula_altura_arvore(a->dir);
        if(alt_esq > alt_dir){
            return alt_esq + 1;
        }
        else{
            return alt_dir + 1;
        }
    }
    return -1;
}   

int calcula_nos_folha(Arvore* a){
    //percorre recursivamente a arvore
    //acrescentando 1 no valor de retorno
    //para todos os nós sem filhos.
    
    if(a){
        if(!a->esq && !a->dir){
            return 1;
        }
        else{
            return calcula_nos_folha(a->esq) + 
            calcula_nos_folha(a->dir);
        }    
    }
    return 0;
}   