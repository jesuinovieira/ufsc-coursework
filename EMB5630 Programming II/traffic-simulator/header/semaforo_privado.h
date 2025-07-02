#ifndef semaforo_privado_h
#define semaforo_privado_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "semaforo_interface.h"
#include "../header/pista_interface.h"

struct semaforo
{
    Pista *pistaAferente;              // Pista do semáforo
    Pista **pistasEferentes;         // Vetor contendo as pistas de saída
    int *probabilidades;                // Vetor contendo a probabilidade de virar em cada pista
    int estado;                               // Estado do semáforo: (0) fechado ou (1) aberto
    int time;                                   // Tempo que o semáforo permanece aberto
    int sentido;                              // Norte (0), Leste (1), Sul (2), Oeste (3)
};

#endif