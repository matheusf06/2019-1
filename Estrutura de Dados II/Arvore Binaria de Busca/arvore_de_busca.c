#include "arvore_de_busca.h"

int buscar(Arvore* a, int v){
    if(!a){
        return 0;
    }else if(v < a->info){
        return buscar(a->esq, v);
    }else if(v > a->info){
        return buscar(a->dir, v);
    }else{
        return 1;
    }
    //asdasd

}

Arvore* inserir(Arvore* a, int v){
    if(!a){
        a = (Arvore*)malloc(sizeof(Arvore));
        a->info = v;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if(v < a->info){
        a->esq = inserir(a->esq, v);
    }
    else{
        a->dir = inserir(a->dir, v);
    }
    return a;
}

Arvore* removerExata(Arvore* a, int v){
    if(!a){
        return NULL;
    }
    else{
        if(a->info > v){
            a->esq = removerExata(a->esq, v);
        }
        else if(a->info < v){
            a->dir = removerExata(a->dir, v);
        }
        else{
            if((a->esq == NULL) && a->dir == NULL){
                free (a);
                a = NULL;
            }
            else if(a->dir == NULL){
                Arvore* tmp = a;
                a = a->esq;
                free(tmp);
            }
            else if(a->esq == NULL){
                Arvore* tmp = a;
                a = a->dir;
                free(tmp);
            }
            else{
                Arvore* tmp = a->esq;
                while(tmp->dir != NULL){
                    tmp = tmp->dir;
                }
                a->info = v;
                tmp->info = v;
                a->esq = removerExata(a->esq, v);
            }
        }
        return a;
    }
}

Arvore* remover(Arvore* a, int v){
    if(a != NULL){
        if(a->info > v){
            //estou em um no maior que a chave
            a->esq = remover(a->esq, v);
            //vou para esquerda
        }
        else if(a->info < v){
            //estou em um no menor que a chave
            a->dir = remover(a->dir, v);
            //vou para a direita
        }
        else{
            //encontrei o no da chave
            //se ele tem dois filhos
            if(a->dir && a->esq){
                //procurar pelo menor filho a direita 
                Arvore* tmp = a->esq;
                //ir até o pai do ultimo no para a esquerda
                while(tmp->dir){
                    tmp = tmp->dir;
                }
                a->info = tmp->info;
                tmp->info = v;
                a->esq = remover(a->esq, v);
            }
            //se ele so tem o filho da direita
            else if(a->dir){
                //limpar o no
                //retornar seu unico filho
                Arvore* tmp = a->dir;
                free (a);
                a = tmp;
            }
            //se ele so tem o filho da esquerda
            else if(a->esq){
                //limpar o no
                //retornar seu unico filho
                Arvore* tmp = a->esq;
                free(a);
                a = tmp;
            }
            //se ele nao tem filho
            else{
                //limpar o no
                //retornar nulo
                free(a);
                a = NULL;
            }
        } 
        return a;
    }
    return NULL;
}

void imprime_pre_ordem(Arvore* a){

	if(a){
		printf("%d, ", a->info);
		imprime_pre_ordem(a->esq);
		imprime_pre_ordem(a->dir);
	}	 
}

void imprime_decrescente(Arvore* a){
    if(!a){
        return;
    }
    else{
        imprime_decrescente(a->dir);
        printf("%d, ", a->info);
        imprime_decrescente(a->esq);
    }
}

int min_(Arvore* a){
    if(!a){
        return 0;
    }
    else{
        if(!min_(a->esq)){
            printf("%d", a->info);
        }
        return 1;
    }
}

int max_(Arvore* a){
    if(!a){
        return 0;
    }
    else{
        if(!max_(a->dir)){
            printf("%d", a->info);
        }
        return 1;
    }
}

Arvore* preencheNElementos(int n){
    int i;
    Arvore* a = NULL;
    for(i = 0; i < n; i++){
        a = inserir(a, i);
    }
    return a;
}

Arvore* preencheNAleatorios(int n){
    int i;
    Arvore* a = NULL;
    srand(time(NULL));
    for(i = 0; i < n; i++){
        a = inserir(a, rand()%n);
    }
    return a;
}

int maior_ramo(Arvore* a){
    if(a){
        int s_esq = maior_ramo(a->esq);
        int s_dir = maior_ramo(a->dir);

        if(s_dir >= s_esq){
            return a->info + s_dir;
        }
        else{
            return a->info + s_esq;
        }
    }
    return 0;
}

int ancestral(Arvore* a, int e1, int e2){

    if(a){
        int esq = ancestral(a->esq, e1, e2);
        int dir = ancestral(a->dir, e1, e2);
        if(esq || dir){
            return esq + dir;
        }
        if(buscar(a, e1) && buscar(a, e2)){
            return a->info;
        }
    }
    return 0;
}
