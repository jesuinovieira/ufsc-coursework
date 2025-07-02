#include "../header/fila_privado.h"

// Implementacao das operacoes do TDA fila generico

fila_t *fila_cria(void (*imp)(const void *), void (*libera)(void *), int (*comparar)(const void *, const void *))
{
    fila_t *f = (fila_t *) malloc(sizeof(fila_t));

    if(!f)
        return NULL;

    f->cabeca = NULL;
    f->cauda = NULL;
    f->tamanho = 0;

    f->imprime = imp;
    f->destruir = libera;
    f->compara = comparar;

    return f;
}

void fila_destroi(fila_t **f)
{
    if(!f)
        return;

    celula_t *atualNode = (*f)->cabeca;
    celula_t *proxNode;

    while(atualNode != NULL){

        if((*f)->destruir != NULL)
            (*f)->destruir(atualNode->dado);

        proxNode = atualNode->prox;
        free(atualNode);
        atualNode = proxNode;
    }

    (*f)->cabeca = NULL;
    (*f)->cauda = NULL;

    free(*f);
    *f = NULL;
}

int fila_vazia(fila_t *f)
{
    if(!f)
        return -1;

    return (f->tamanho == 0);
}

int fila_tamanho(fila_t *f)
{
    if(!f)
        return -1;

    return f->tamanho;
}

int fila_enfileira(fila_t *f, void *elem)
{
    if(!f || !elem)
        return 0;

    celula_t *new = (celula_t *) malloc(sizeof(celula_t));
    if(!new)
        return 0;

    celula_t *oldTail = f->cauda;

    if(fila_vazia(f) != 0)
        f->cabeca = new;
    else
        oldTail->prox = new;

    f->cauda = new;

    new->dado = (void *)elem;
    new->prox = NULL;
    f->tamanho++;

    return 1;
}

int fila_enfileira_ordenado(fila_t *f, void *elem)
{
    if(!f || !elem)
        return 0;

    /* Caso o ponteiro de comparacao for NULL ou caso a fila estiver vazia, insere na cauda */
    if(!f->compara || fila_vazia(f))
        return fila_enfileira(f,elem);

    if(f->compara(f->cabeca->dado, elem) == 1)
        return insereCabeca(f, elem);

    celula_t *new, *tmp = f->cabeca;

    while(tmp->prox != NULL){

        if(f->compara(tmp->prox->dado, elem) == 1 || f->compara(tmp->dado, elem) == 0){

            new = (celula_t *) malloc(sizeof(celula_t));

            new->dado = elem;
            new->prox = tmp->prox;
            tmp->prox = new;
            f->tamanho++;

            return 1;
        }

        tmp = tmp->prox;
    }

    /* Caso o elemento a ser inserido seja maior que todos da fila, insere na cauda */
    return fila_enfileira(f, elem);
}

int fila_desenfileira(fila_t *f, void **elem)
{
    if(fila_vazia(f) != 0)
        return 0;

    celula_t *tmp = f->cabeca;
    celula_t *newHead = tmp->prox;

    if(f->cabeca == f->cauda){
        f->cabeca = NULL;
        f->cauda = NULL;
    }else{
        f->cabeca = newHead;
    }

    *elem = tmp->dado;

    free(tmp);
    f->tamanho--;

    return 1;
}

int fila_cabeca(fila_t *f, void **elem)
{
    if(!f || !elem || fila_vazia(f))
        return 0;

    *elem = f->cabeca->dado;

    return 1;
}

int fila_cauda(fila_t *f, void **elem)
{
    if(!f || !elem || fila_vazia(f))
        return 0;

    *elem = f->cauda->dado;

    return 1;
}

void fila_imprime(fila_t *f)
{
    if(!f || !f->imprime)
        return;

    celula_t *tmp = f->cabeca;

    while(tmp != NULL){
        f->imprime(tmp->dado);
        tmp = tmp->prox;
    }
}