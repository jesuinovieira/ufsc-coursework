#include "../header/pista_privado.h"

int veiculoCria(Pista *pista, int tam, int horaAtual)
{
    if(!pista){
        printf("Parametros nulos!\n");
        return -1;
    }

    /* Verifica se a pista esta cheia */
    if(!verificaDisponibilidade(pista, tam))
        return -1;

    Veiculo *v = (Veiculo *) malloc(sizeof(Veiculo));
    if(!v){
        printf("Erro ao alocar memoria do veiculo!\n");
        return -1;
    }

    v->tamanho = tam + 3;
    v->timeEntrada = horaAtual;

    if(!fila_enfileira_ordenado(pista->f, v)){
        printf("Erro ao enfileirar veiculo!\n");
        free(v);
        return -1;
    }

    int tempoSaida = (int) pista->tamanho/ (pista->velocidade / 3.6);

    return tempoSaida;
}

int veiculoCompara(Veiculo *v1, Veiculo *v2)
{
    if(!v1 || !v2)
        return -2;

    if(v1->timeEntrada < v2->timeEntrada)
        return -1;
    else if(v1->timeEntrada > v2->timeEntrada)
        return 1;
    else
        return 0;
}

void veiculoDestroi(Veiculo *veiculo)
{
    if(!veiculo){
        printf("Parametros nulos!\n");
        return;
    }

    free(veiculo);
    veiculo = NULL;
}

int gerarVeiculo(Pista *pista, int horaAtual)
{
    if(!pista){
        printf("Parametros nulos!\n");
        return -1;
    }

    srand(time(NULL));

    float tmp = (float) rand();
    tmp = tmp / RAND_MAX;
    tmp = tmp * (pista->limiteSuperior - pista->limiteInferior);

    pista->tempoEntrada = (int)tmp + pista->limiteInferior + horaAtual;

    return (pista->tempoEntrada);
}

int veiculoDesenfileira(Pista *pista, Veiculo **v)
{
    if(!pista){
        printf("Parametros nulos!\n");
        return -1;
    }

    /* Verifica se a Pista esta vazia */
    if(fila_vazia(pista->f))
        return 0;

    if(fila_desenfileira(pista->f, (void **)v) != 1){
        printf("Erro ao desenfileirar o evento!\n");
        return -1;
    }
    pista->tamanhoOcupado -= (*v)->tamanho;

    return 1;
}

void veiculoSai(Pista *pista, int *veiculosSairam)
{
    if(!pista || !veiculosSairam)
        return;

    Veiculo *v = NULL;
    veiculoDesenfileira(pista, &v);
    veiculoDestroi(v);
    (*veiculosSairam)++;
}