#include "../header/relogio_privado.h"

Relogio *relogioCria(int totalTime)
{
    if(totalTime <= 0)
        return NULL;

    Relogio *r = (Relogio *)malloc(sizeof(Relogio));
    if(!r){
        printf("Erro ao alocar memoria do relogio!\n");
        return NULL;
    }

    /* Criando a fila de eventos do sistema */
    r->f = fila_cria(NULL, (void *)eventoDestroi, (const void *)eventoCompara);
    if(!r->f){
        printf("Erro ao criar a fila de eventos!\n");
        free(r);
        return NULL;
    }

    r->hora = 0;
    r->tempoTotal = totalTime;

    return r;
}

void relogioDestroi(Relogio **r)
{
    if(!r){
        printf("Parametros nulos!\n");
        return;
    }

    /* Destruimos a fila de eventos e a estrutura do relogio */
    if((*r)->f != NULL)
        fila_destroi(&(*r)->f);

    free(*r);
    *r = NULL;
}

void skipTime(Relogio *r)
{
    if(!r){
        printf("Parametros nulos!\n");
        return;
    }

    r->hora++;
}

int horaAtual(Relogio *r)
{
    if(!r){
        printf("Parametros nulos!\n");
        return -1;
    }

    return r->hora;
}

bool simulador(Relogio *r)
{
    if(!r){
        printf("Parametros nulos!\n");
        return false;
    }
    return (r->hora <= r->tempoTotal);
}