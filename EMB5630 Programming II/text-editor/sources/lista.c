    #include "../header/lista_privado.h"

/* Implementacao das funcoes do TDA lista duplamente encadeada generico */

lista_t *lista_cria(void (*imp)(const void *), void (*libera)(void *), int (*comparar)(const void *, const void *))
{

    // Alocando a estrutura da lista
    lista_t *l = (lista_t *) malloc(sizeof(lista_t));
    if(!l) return NULL;

    // A lista e inicializada vazia, portanto, setamos cabeca e cauda para NULL e tamanho recebe 0
    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;

    // Setamos as funcoes da lista (imprime, compara e destroi)
    l->imprime = imp;
    l->compara = comparar;
    l->destruir = libera;

    return l;
}

void lista_destroi(lista_t **l)
{

    if(!l) return;

    // Destruimos os nos
    celula_t *proxNode, *atualNode = (*l)->cabeca;

    // Percorre a lista
    while(atualNode != NULL){

        // Verifica se o ponteiro destruir e valido
        if((*l)->destruir != NULL){
            // Chamamos a funcao que sabe como destruir o dado do no
            (*l)->destruir(atualNode->dado);
        }

        proxNode = atualNode->prox;
        free(atualNode);
        atualNode = proxNode;
    }

    // Por seguranca, setamos a cabeca e a cauda para NULL
    (*l)->cabeca = NULL;
    (*l)->cauda = NULL;

    // Destruindo a lista e setando seu ponteiro para NULL
    free(*l);
    *l = NULL;
}

int lista_vazia(lista_t *l)
{

    if(!l) return -1;

    if(l->tamanho == 0){
        return 1;
    }else{
        return 0;
    }

}

int lista_tamanho(lista_t *l)
{
    if(!l) return -1;

    return l->tamanho;
}

celula_t *lista_cabeca(lista_t *l)
{
    if(lista_vazia(l) != 0){
        return NULL;
    }else{
        return l->cabeca;
    }
}

celula_t *lista_cauda(lista_t *l)
{
    if(lista_vazia(l) != 0){
        return NULL;
    }else{
        return l->cauda;
    }

}

void *lista_dado(celula_t *c)
{
    if(!c){
        return NULL;
    }else{
        return c->dado;
    }
}

celula_t *lista_proximo(celula_t *c)
{
    if(!c){
        return NULL;
    }else{
        return c->prox;
    }

}

celula_t *lista_anterior(celula_t *c)
{
    if(!c){
        return NULL;
    }else{
        return c->ant;
    }

}

int lista_eh_cabeca(lista_t *l, celula_t *c)
{
    if(lista_vazia(l) != 0 || !c){
        return -1;
    }else{
        return(l->cabeca == c);
    }

}

int lista_eh_cauda(lista_t *l, celula_t *c)
{
    if(lista_vazia(l) != 0 || !c){
        return -1;
    }else{
        return(l->cauda == c);
    }
}

int lista_insere_proximo(lista_t *l, celula_t *c, const void *elem)
{
    if(!l || !elem)
        return 0;

    // Caso esse parametro seja invalido, insere o novo elemento na cabeca da lista
    if(!c || lista_vazia(l) == 1){
        insereCabeca(l, elem);
        return 1;
    }

    // Caso o elemento for a cauda, insere na cauda
    if(l->cauda == c){
        insereCauda(l, elem);
        return 1;
    }

    // Caso contrario, o elemento sera inserido no meio da lista
    celula_t *new = (celula_t *) malloc(sizeof(celula_t));

    if(!new)
        return 0;

    // Atribui o elemento ao novo no
    new->dado = (void *)elem;

    // Atualiza os ponteiros
    new->ant = c;
    new->prox = c->prox;
    c->prox->ant = new;
    c->prox = new;

    l->tamanho++;

    return 1;
}

int lista_insere_anterior(lista_t *l, celula_t *c, const void *elem)
{
    if(!l || !elem)
        return 0;

    // Caso esse parametro seja invalido, insere o novo elemento na cabeca da lista
    if(!c || lista_vazia(l) == 1){
        insereCabeca(l, elem);
        return 1;
    }

    // Caso o elemento for a cabeca, insere na cabeca
    if(l->cabeca == c){
        insereCabeca(l, elem);
        return 1;
    }

    // Caso contrario, o elemento sera inserido no meio da lista
    celula_t *new = (celula_t *) malloc(sizeof(celula_t));

    if(!new)
        return 0;

    // Atribui o elemento ao novo no
    new->dado = (void *)elem;

    // Atualiza os ponteiros
    new->prox = c;
    new->ant = c->ant;
    c->ant->prox = new;
    c->ant = new;

    l->tamanho++;

    return 1;
}

void insereCabeca(lista_t *l, const void *elem)
{
    if(!l || !elem)
        return;

    // Criamos o novo no
    celula_t *new = (celula_t *) malloc(sizeof(celula_t));

    if(!new)
        return;

    // Salvamos o endereço da antiga cabeca
    celula_t *oldHead = l->cabeca;

    // Caso a lista for vazia, atualizamos o ponteiro da cauda, senao, atualizamos oldHead->ant
    if(lista_vazia(l) != 0){
        l->cauda = new;
    }else{
        oldHead->ant = new;
    }

    // Atualizamos os ponteiros
    l->cabeca = new;
    new->dado = (void *)elem;
    new->prox = oldHead;
    new->ant = NULL;

    l->tamanho++;
}

void insereCauda(lista_t *l, const void *elem)
{
    if(!l || !elem)
        return;

    // Criamos o novo no
    celula_t *new = (celula_t *) malloc(sizeof(celula_t));

    if(!new)
        return;

    // Salvamos o endereço da antiga cauda
    celula_t *oldTail = l->cauda;

    // Caso a lista for vazia
    if(lista_vazia(l) != 0){
        l->cabeca = new;
    }else{
        oldTail->prox = new;
    }

    // Atualizamos os ponteiros
    l->cauda = new;
    new->dado = (void *)elem;
    new->prox = NULL;
    new->ant = oldTail;

    l->tamanho++;
}

int lista_insere_posicao(lista_t *l, const unsigned int posicao, const void *elem)
{
    if(!l || !elem)
        return 0;

    // Verifica se e para inserir na cabeca
    if(posicao == 0){
        insereCabeca(l, elem);
        return 1;
    }

    // Verifica se posicao e maior que o tamanho da lista
    if(posicao > l->tamanho){
        insereCauda(l, elem);
        return 1;
    }

    celula_t *tmp = l->cabeca;

    for(int pos = 0; pos < posicao - 1; pos++)
        tmp = tmp->prox;

    // Como chamo a funcao insere proximo, ela ja atualizará os ponteiros, atribuirá o dado ao no e atualiza tamanho da lista
    if(lista_insere_proximo(l, tmp, elem) == 1){
        return 1;
    }else{
        return 0;
    }
}

int lista_remove(lista_t *l, celula_t *c, void **elem)
{
    if(lista_vazia(l) != 0 || !c || !elem){
        return 0;
    }else{

        // Retorna o conteudo do elemento removido em elem
        *elem = c->dado;

        // Verifica se é pra remover na cabeca ou na cauda
        if(l->cabeca == c){
            removeCabeca(l);
            return 1;
        }
        if(l->cauda == c){
            removeCauda(l);
            return 1;
        }

        // Atualiza os ponteiros
        c->ant->prox = c->prox;
        c->prox->ant = c->ant;

        free(c);
        l->tamanho--;

        return 1;
    }
}

void lista_imprime(lista_t *l)
{
    if(!l || l->imprime == NULL)
        return;

    celula_t *tmp = l->cabeca;

    while(tmp != NULL){
        l->imprime(tmp->dado);
        tmp = tmp->prox;
    }
}

int lista_insere_ordenado(lista_t *l, const void *elem)
{
    if(!l || !elem)
        return 0;

    // Caso o ponteiro nao for valido, a insercao deve ser feita na cauda da lista
    if(l->compara == NULL){
        insereCauda(l, elem);
        return 1;
    }

    celula_t *tmp = l->cabeca;

    // Percorre a lista
    while(tmp != NULL){

        // Se for igual, insere no proximo
        if(l->compara(tmp->dado, elem) == 0){
            lista_insere_proximo(l, tmp, elem);
            return 1;
        }

        // Se for menor, insere no anterior
        if(l->compara(tmp->dado, elem) == 1){
            lista_insere_anterior(l, tmp, elem);
            return 1;
        }

        tmp = tmp->prox;
    }

    // Se nao achar ou se a lista for vazia, insere no final
    insereCauda(l, elem);
    return 1;
}

/* FUNCAO RECURSIVA */
celula_t *lista_busca_recursiva(lista_t *l, const void *elem, celula_t *c)
{
    if(!l || !elem || !c)
        return NULL;

    if(c->dado == elem)
        return c;
    else
        return lista_busca_recursiva(l, elem, c->prox);
}

lista_t *lista_separa(lista_t *l, const void *elem)
{
    if(!l || !elem)
        return NULL;

    // Se a lista for vazia ou tiver so um elemento, nao separa
    if(lista_vazia(l) == 1 || l->tamanho == 1)
        return NULL;

    celula_t *tmp = l->cabeca;
    int tam = 1;

    // Percorre a lista
    while(tmp != NULL){

        // Se encontrou a celula que contem o elemento, separa a lista
        if(tmp->dado == elem){

            // Cria a nova lista
            lista_t *newLista = lista_cria(l->imprime, l->destruir, l->compara);

            // Atualiza os ponteiros
            newLista->cabeca = tmp->prox;
            newLista->cauda = l->cauda;

            l->cauda = tmp;

            tmp->prox = NULL;
            newLista->cabeca->ant = NULL;

            // Atualiza o tamanho das listas
            newLista->tamanho = l->tamanho - tam;
            l->tamanho = tam;

            return newLista;
        }

        tmp = tmp->prox;
        tam++;
    }

    // Caso nao possua o elemento, retorna NULL
    return NULL;
}

lista_t *lista_concatena_e_destroi(lista_t **l1, lista_t **l2)
{
    if(!l1 || !l2)
        return NULL;

    // Retorna NULL se ambas forem vazias (sem destrui-las).
    if(lista_vazia(*l1) == 1 && lista_vazia(*l2) == 1)
        return NULL;

    lista_t *newLista;

    if(lista_vazia(*l1) == 1){
        // Caso l1 for vazia

        newLista = lista_cria((*l2)->imprime, (*l2)->destruir, (*l2)->compara);

        // Atualiza os ponteiros
        newLista->cabeca = (*l2)->cabeca;
        newLista->cauda = (*l2)->cauda;

    }else{
        // Caso l1 nao for vazia

        newLista = lista_cria((*l1)->imprime, (*l1)->destruir, (*l1)->compara);

        newLista->cabeca = (*l1)->cabeca;

        if(lista_vazia(*l2) == 1){
            // Caso l2 for vazia
            newLista->cauda = (*l1)->cauda;
        }else{
            // Caso l2 nao for vazia

            newLista->cauda = (*l2)->cauda;

            // Concatenamos, de fato, as duas listas
            (*l1)->cauda->prox = (*l2)->cabeca;
            (*l2)->cabeca->ant = (*l1)->cauda;
        }
    }

    // Atualizamos o tamanho da lista
    newLista->tamanho = (*l1)->tamanho + (*l2)->tamanho;

    // Por seguranca, setamos os ponteiros da cabeca e cauda das duas listas a serem destruidas para NULL
    (*l1)->cabeca = NULL;
    (*l1)->cauda = NULL;
    (*l2)->cabeca = NULL;
    (*l2)->cauda = NULL;

    // Destroi as listas
    free(*l1);
    free(*l2);

    *l1 = NULL;
    *l2 = NULL;

    return newLista;
}