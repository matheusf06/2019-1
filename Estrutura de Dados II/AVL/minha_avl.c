#include <stdlib.h>
#include <stdio.h>

typedef struct AVL{
    int chave;
    int altura;
    struct AVL* esq;
    struct AVL* dir;
}AVL;

int maior(int a, int b){
    return (a > b ? a : b);
}

int altura(AVL* a){
    //se for nula retorna -1
    //se nao retorna a propria altura
    return (a == NULL ? -1 : a->altura);
}

int atualizar(AVL* a){
    //atualizar altura da arvore
    //sera o maior entre altura dos filhos + 1
    return(maior(altura(a->esq), altura(a->dir)) + 1);
}

int balanceamento(AVL* a){
    //retono altura direita - altura esquerda
    return(altura(a->dir) - altura(a->esq));
}

AVL* rotacao_s_dir(AVL* a){
    AVL* nroot = a->esq;
    a->esq = nroot->dir;
    nroot->dir = a;
    a->altura = atualizar(a);
    nroot->altura = atualizar(nroot);
    return nroot;
}

AVL* rotacao_s_esq(AVL* a){
    AVL* nroot = a->dir;
    a->dir = nroot->esq;
    nroot->esq = a;
    a->altura = atualizar(a);
    nroot->altura = atualizar(nroot);
    return nroot;
}

AVL* rotacao_d_dir(AVL* a){
    a->esq = rotacao_s_esq(a->esq);
    a = rotacao_s_dir(a);
    return a;
}

AVL* rotacao_d_esq(AVL* a){
    a->dir = rotacao_s_dir(a->dir);
    a = rotacao_s_esq(a);
    return a;
}

AVL* atualizar_esq(AVL* a){
    //atualizar altura da arvore
    a->altura = atualizar(a);
    //caso balanceamento da arvore seja -2
    if(balanceamento(a) == -2){
        //caso balanceamento do filho esquerdo positivo
        if(balanceamento(a->esq) > 0){
            //arvore = rotacao dupla direita
            a = rotacao_d_dir(a);
        }
        //caso negativo como o da arvore
        else{
            //arvore = rotacao simples direita
            a = rotacao_s_dir(a);
        }
    }
    return a;
}

AVL* atualizar_dir(AVL* a){
    //atualizar altura da arvore
    a->altura = atualizar(a);
    //caso balanceamento da arvore seja 2
    if(balanceamento(a) == 2){
        //caso balanceamento do filho direito negativo
        if(balanceamento(a->dir) < 0){
           //arvore = rotacao dupla esquerda
            a = rotacao_d_esq(a);
        }
        //caso positivo como o da arvore
        else{
            //arvore = rotacao simples esquerda
            a = rotacao_s_esq(a);
        }
    }
    return a;
}

AVL* inserir(AVL* a, int c){
    //caso arvore vazia, criar novo nó com altura 0 sem filhos
    if(a == NULL){
        a = (AVL*) malloc (sizeof (AVL));
        a->chave = c;
        a->dir = a->esq = NULL;
        a->altura = 0;
    }
    //caso arvore maior que chave
    else if(a->chave > c){
        //esperar retorno da insercao na arvore a esquerda
        a->esq = inserir(a->esq, c);
        //atualizar dados do ramo a esqerda da arvore que entrou
        a = atualizar_esq(a);
    }
    //caso arvore menor que chave
    else{
        //esperar retorno da insercao na arvore a direita
        a->dir = inserir(a->dir, c);
        //atualizar dados do ramo a direita da arvore que entrou
        a = atualizar_dir(a);
    }
    //retornar arvore que entrou
    return a;
}

void imprimir_in_order (AVL* a, int nivel) {
   if (a != NULL) {
      int i;
      for (i = 0; i < nivel; i++) {
         printf("      ");
      }
      printf("Chave: %d (altura: %d, fb: %d) no nível: %d\n", a->chave, a->altura, balanceamento(a), nivel);
      imprimir_in_order (a->esq, nivel + 1);
      imprimir_in_order (a->dir, nivel + 1);
   }
}


int main(){
    AVL* a = NULL;
    a = inserir(a, 1);
    a = inserir(a, 0);
    a = inserir(a, 3);
    a = inserir(a, 2);
    a = inserir(a, 4);
    a = inserir(a, 5);
    imprimir_in_order(a, 0);
    
    return 1;
}   