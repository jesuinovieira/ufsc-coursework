#include "../header/pista_privado.h"

Pista *pistaCria(int velocidade, int tam, int tipo, int limiteSuperior, int limiteInferior)
{
    if(tam < 0)
        return NULL;

    Pista *pista = (Pista *)malloc(sizeof(Pista));
    if(!pista){
        printf("Parametros nulos!\n");
        return NULL;
    }

    /* Cria uma fila representando a fila de carros na Pista */
    pista->f = fila_cria(NULL, (void *)veiculoDestroi, (const void *)veiculoCompara);
    if(!pista->f){
        printf("Erro ao alocar memoria para a pista!\n");
        free(pista);
        return NULL;
    }

    pista->velocidade = velocidade;
    pista->tamanho = tam;
    pista->tamanhoOcupado = 0;
    pista->tipo = tipo;

    pista->limiteSuperior = limiteSuperior;
    pista->limiteInferior = limiteInferior;
    pista->tempoEntrada = 0;

    return pista;
}

void destroiPistas(Pista *PISTAS[], int tamanho)
{
    while(tamanho > 0)
        pistaDestroi(&PISTAS[--tamanho]);
}

void pistaDestroi(Pista **pista)
{
    if(!pista){
        printf("Parametros nulos!\n");
        return;
    }

    if((*pista)->f != NULL)
        fila_destroi(&(*pista)->f);

    free(*pista);
    *pista = NULL;
}

bool verificaDisponibilidade(Pista *pista, int tam)
{
    if(!pista)
            return false;

    if((tam + 3 + pista->tamanhoOcupado) > pista->tamanho)
        return false;
    else
        return true;
}

int pistaTipo(Pista *pista)
{
    if(!pista){
        printf("Parametros nulos!\n");
        return -1;
    }
    return pista->tipo;
}

int moveVeiculo(Pista *pista, int time)
{
    if(!pista){
        printf("Parametros nulos!\n");
        return 0;
    }

    if(fila_vazia(pista->f) != 0)
                    return 0;

    /* Tempo para que um veiculo percorra toda a psita */
    int tmp = (int)pista->tamanho / (pista->velocidade / 3.6);

    /* Verifica o tempo de entrada do prox veiculo */
    Veiculo *v = NULL;
    fila_cabeca(pista->f, (void *)&v);

    if(tmp > time - v->timeEntrada)
        return 0;
    else
        return 1;
}

bool pistaVazia(Pista *pista)
{
    if(!pista){
        printf("Parametros nulos!\n");
        return true;
    }

    if(fila_vazia(pista->f) != 0)
        return false;
    else
        return true;
}

int qtdVeiculos(Pista *pista)
{
    if(!pista || !pista->f){
        printf("Parametros nulos!\n");
        return -1;
    }else
        return fila_tamanho(pista->f);
}

int realizaTroca(Pista *origem, Pista *destino, int hora)
{
    if(!origem || !destino){
        printf("Parametros nulos!\n");
        return -1;
    }

    if(fila_vazia(origem->f))
        return -1;

    Veiculo *carroOut = NULL;
    fila_cabeca(origem->f, (void *)&carroOut);

    /* Caso o veiculo nao couber na Pista eferente, a funcao retorna -1 */
    if(3 + carroOut->tamanho + destino->tamanhoOcupado > destino->tamanho)
        return -1;

    if(fila_desenfileira(origem->f, (void **)&carroOut) != 1){
        printf("Erro ao desenfileirar veiculo!\n");
        return -1;
    }

    origem->tamanhoOcupado -= carroOut->tamanho;
    destino->tamanhoOcupado += carroOut->tamanho;
    carroOut->timeEntrada = hora;

    if(fila_enfileira_ordenado(destino->f, carroOut) != 1){
        printf("Erro ao enfileirar veiculo!\n");
        return -1;
    }

    return 1;
}

int velocidadePista(Pista *pista)
{
    if(!pista){
        printf("Parametros nulos!\n");
        return -1;
    }

    return pista->velocidade / 3.6;
}

int tempoEntrada(Pista *pista)
{
    if(!pista){
        printf("Parametros nulos!\n");
        return -1;
    }
    return pista->tempoEntrada;
}

int horaSaida(Pista *pista, int hora)
{
    if(!pista){
        printf("Parametros nulos!\n");
        return -1;
    }

    if(fila_vazia(pista->f) != 0)
        return -1;

    Veiculo *v = NULL;
    fila_cabeca(pista->f, (void *)&v);

    int horaSaida = pista->tamanho / (pista->velocidade / 3.6) + v->timeEntrada;

    if(horaSaida < hora)
        return hora;
    else
        return horaSaida;
}