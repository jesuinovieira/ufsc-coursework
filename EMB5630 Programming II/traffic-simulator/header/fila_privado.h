#ifndef fila_privado_h
#define fila_privado_h

#include "fila_interface.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct celula
{
    void *dado;                     // Dado armazenado na celula. A alocacao de memoria eh responsabilidade do usuario
    struct celula *prox;         // Proxima celula na fila encadeada
} celula_t;

struct fila
{
    celula_t *cabeca;            // Ponteiro para a celula cabeca da fila
    celula_t *cauda;              // Ponteiro para a celula cauda da fila
    int tamanho;                   // Tamanho da fila
    void (*destruir)(void *);  // Ponteiro de funcao usado na funcao de destruir a fila, caso seja valida
    void (*imprime)(const void *); // Ponteiro de funcao para imprimir os dados armazenados na fila. Implementacao eh responsabilidade do usuario do TDA
    int (*compara)(const void *, const void *);  // Ponteiro de funcao para comparar dois dados armazenados na fila. Retorna -1 se o primeiro eh menor que o segundo, 0 se forem iguais, ou 1 se o primeiro for maior que o segundo
};

/* Funções privadas */
int insereCabeca(fila_t *f, const void *elem)
{
    if(!f || !elem)
        return 0;

    celula_t *new = (celula_t *) malloc(sizeof(celula_t));

    if(!new)
        return 0;

    /* Salvamos o endereço da antiga cabeca */
    celula_t *oldHead = f->cabeca;

    /* Caso a fila for vazia, atualizamos o ponteiro da cauda */
    if(fila_vazia(f) != 0)
        f->cauda = new;

    /* Atualizamos os ponteiros */
    f->cabeca = new;
    new->dado = (void *)elem;
    new->prox = oldHead;

    f->tamanho++;
    return 1;
}

#endif