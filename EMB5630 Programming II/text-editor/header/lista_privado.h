#ifndef lista_privado_h
#define lista_privado_h

/* Bibliotecas */
#include "lista_interface.h"
#include <stdlib.h>
#include <string.h>

/* Estrutura dos nós da lista */
struct celula {
	void *dado;                                                  // Dado armazenado na celula. A alocacao de memoria eh responsabilidade do usuario
	struct celula *prox;                                      // Proxima celula na lista encadeada
	struct celula *ant;                                        // Celula anterior na lista encadeada
};

/* Estrutura da lista */
struct lista {
	celula_t *cabeca;                                         // Ponteiro para a celula cabeca da lista
	celula_t *cauda;                                           // Ponteiro para a celula cauda da lista
	int tamanho;
	void (*destruir)(void *);                               // Ponteiro de funcao usado na funcao de destruir a lista, caso seja valida
	void (*imprime)(const void *);                    // Ponteiro de funcao para imprimir os dados armazenados na lista. Implementacao eh responsabilidade do usuario do TDA
	int (*compara)(const void *, const void *); // Ponteiro de funcao para comparar dois dados armazenados na lista. Retorna -1 se o primeiro eh menor que o segundo, 0 se forem iguais, ou 1 se o primeiro for maior que o segundo
};

/* ************************************************* FUNCOES PRIVADAS ************************************************* */

/*
 * Função: remove um elemento da cabeca da lista.
 * Pré: a lista deve existir e não deve estar vazia.
 * Pós: a cabeça da lista é removida e seus ponteiros são atualizados conforme o necessário.
 */
void * removeCabeca(lista_t *l)
{
    // Verifica se a lista existe ou se ela esta vazia
    if(!l || lista_vazia(l) != 0)
        return NULL;

    // Salvamos o endereco da cabeca atual e da nova cabeca
    celula_t *tmp = l->cabeca;
    celula_t *newHead = tmp->prox;

    // Verificamos se a lista possui um unico elemento
    if(l->cabeca == l->cauda){
        l->cabeca = NULL;
        l->cauda = NULL;
    }else{
        l->cabeca = newHead;
        newHead->ant = NULL;
    }

    // Salvamos o dado para retorna-lo, liberamos a memoria do no e reduzimos o tamanho da lista
    void *dado = tmp->dado;
    free(tmp);
    l->tamanho--;

    return dado;
}

/*
 * Função: remove um elemento da cauda da lista.
 * Pré: a lista deve existir e não deve estar vazia.
 * Pós: a cauda da lista é removida e seus ponteiros são atualizados conforme o necessário.
 */
void * removeCauda(lista_t *l)
{
    // Verifica se a lista existe ou se ela esta vazia
    if(!l || lista_vazia(l) != 0)
        return NULL;

    // Salvamos o endereco da cauda atual e da nova cauda
    celula_t *tmp = l->cauda;
    celula_t *newTail = tmp->ant;

    // Verificamos se a lista possui um unico elemento
    if(l->cauda == l->cabeca){
        l->cabeca = NULL;
        l->cauda = NULL;
    }else{
        l->cauda = newTail;
        newTail->prox = NULL;
    }

    // Salvamos o dado para retorna-lo, liberamos a memoria do no e reduzimos o tamanho da lista
    void *dado = tmp->dado;
    free(tmp);
    l->tamanho--;

    return dado;
}

#endif