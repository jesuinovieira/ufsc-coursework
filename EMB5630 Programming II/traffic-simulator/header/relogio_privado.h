#ifndef relogio_privado_h
#define relogio_privado_h

#include <stdio.h>
#include <stdlib.h>
#include "relogio_interface.h"
#include "fila_interface.h"

struct evento
{
    int hora;                   // Hora do evento
    int tipo;                    // Tipo do evento: chegadaVeiculo (1), attSemaforo (2) e trocaPista (3)
};

struct relogio
{
    fila_t *f;                    // Fila de eventos
    int hora;                    // Hora atual
    int tempoTotal;        // Tempo de simulação
};

#endif