#include <stdio.h>
#include <stdlib.h>

typedef struct AVL{
    struct AVL* esq;
    struct AVL* dir;
    int chave;
    int altura;
} AVL;

int altura(AVL* a){
    return (a==NULL?-1:a->altura);
}

int maior(int a, int b){
    return (a>b?a:b);
}

int atualizar(AVL* a){
    return (maior(altura(a->esq), altura(a->dir)) + 1);
}

int balanceamento(AVL* a){
    return (altura(a->dir) - altura(a->esq));
}

AVL* rotacao_s_d(AVL* a){
    AVL* t = a->esq;
    a->esq = t->dir;
    t->dir = a;
    a->altura = atualizar(a);
    t->altura = atualizar(t);
    return t;
}

AVL* rotacao_s_e(AVL* a){
    AVL* t = a->dir;
    a->dir = t->esq;
    t->esq = a;
    a->altura = atualizar(a);
    t->altura = atualizar(t);
    return t;
}

AVL* rotacao_d_d(AVL* a){
    if(a != NULL){
        a->esq = rotacao_s_e(a->esq);
        a = rotacao_s_d(a);
    }
    return a;
}

AVL* rotacao_d_e(AVL* a){
    if(a != NULL){
        a->dir = rotacao_s_d(a->dir);
        a = rotacao_s_e(a);
    }
    return a;
}


AVL* atualizar_esq(AVL* a){
    if(a!=NULL){
        a->altura = atualizar(a);
        if(balanceamento(a) == -2){
            if(balanceamento(a->esq) > 0){
                a = rotacao_d_d(a);
            }
            else{
                a = rotacao_s_d(a);
            }
        }
    }
    return a;
}

AVL* atualizar_dir(AVL* a){
    if(a!=NULL){
        a->altura = atualizar(a);
        if(balanceamento(a) == 2){
            if(balanceamento(a->dir) < 0){
                a = rotacao_d_e(a);
            }
            else{
                a = rotacao_s_e(a);
            }
        }
    }
    return a;
}

AVL* inserir(AVL* a, int v){
    if(a == NULL){
        a = (AVL*)malloc(sizeof(AVL));
        a->altura = 0;
        a->chave = v;
        a->esq = a->dir = NULL;
    }
    else{
        if(a->chave > v){
            a->esq = inserir(a->esq, v);
            a = atualizar_esq(a);       
        }
        else{
            a->dir = inserir(a->dir, v);
            a = atualizar_dir(a);
        }
    }
    return a;
}

AVL* remover(AVL* a, int v){
    if(a==NULL){
        return NULL;
    }
    else{
        if(v < a->chave){
            a->esq = remover(a->esq, v);
            a = atualizar_dir(a);
        }
        else if(v > a->chave){
            a->dir = remover(a->dir, v);
            a = atualizar_esq(a);
        }
        else{
            if(a->esq == NULL && a->dir == NULL){
                free(a);
                a = NULL;
            }
            else if(a->esq == NULL){
                AVL* tmp = a;
                a = a->dir;
                free(tmp);
            }
            else if(a->dir == NULL){
                AVL* tmp = a;
                a = a->esq;
                free(tmp);
            }
            else{
                AVL* tmp = a->esq;
                while(tmp->dir != NULL){
                    tmp = tmp->dir;
                }
                a->chave = tmp->chave;
                tmp->chave = v;
                a->esq = remover(a->esq, v);
                a = atualizar_dir(a);
            }
        }
    }
    return a;
}