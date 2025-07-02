#include "../header/relogio_privado.h"

int eventoCompara(Evento *e1, Evento *e2)
{
    if(!e1 || !e2)
        return -2;

    if(e1->hora < e2->hora)
        return -1;
    else if(e1->hora > e2->hora)
        return 1;
    else
        return 0;
}

int eventoCria(Relogio *r, int hora, int tipo)
{
    if(!r){
        printf("Parametros nulos!\n");
        return -1;
    }

    if(hora > r->tempoTotal)
        return 0;

    Evento *e = (Evento*)malloc(sizeof(Evento));
    if(!e){
        printf("Erro na alocacao de memoria do evento!\n");
        return -1;
    }

    e->hora = hora;
    e->tipo = tipo;

    if(fila_enfileira_ordenado(r->f,(void*)e) != 1){
        printf("Erro ao enfileirar evento!\n");
        return -1;
    }

    return 1;
}

void eventoDestroi(Evento *evento)
{
    if(!evento){
        printf("Parametros nulos!\n");
        return;
    }
    free(evento);
    evento = NULL;
}

int eventoTipo(Evento *e)
{
    if(!e){
        printf("Parametros nulos!\n");
        return -1;
    }
    return e->tipo;
}

int proximoEvento(Relogio *r)
{
    if(!r){
        printf("Parametros nulos!\n");
        return -1;
    }

    if(fila_vazia(r->f) != 0)
        return -1;

    Evento *e;
    fila_cabeca(r->f, (void *)&e);

    return e->tipo;
}

int eventoDesenfileira(Relogio *r, Evento **e)
{
    if(!r){
        printf("Parametros nulos!\n");
        return -1;
    }

    if(fila_vazia(r->f))
        return 0;

    Evento *tmp = NULL;
    fila_cabeca(r->f, (void*)&tmp);

    if(tmp->hora != r->hora)
        return 0;

    fila_desenfileira(r->f,(void**)e);
    return 1;
}