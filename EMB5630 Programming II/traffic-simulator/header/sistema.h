#ifndef sistema_h
#define sistema_h

#include <stdio.h>
#include <stdlib.h>
#include "pista_interface.h"
#include "semaforo_interface.h"
#include "relogio_interface.h"

typedef struct pista Pista;
typedef struct semaforo Semaforo;
typedef struct relogio Relogio;
typedef struct evento Evento;


/*
 * Função: para as pistas que estão programadas para receber veículos no horário atual, estes são enfileirados
 * e veiculosEntraram é incrementado. Também gera seus respectivos eventos de saidas, que se da quando o
 * veículo percorre toda a pista. Novos eventos de também são criados.
 * Pre: PISTAS, r e veiculosEntraram devem ser validos.
 * Pos: ocorre a entrada de novos veículos e eventos de chegada e troca de pista são enfileirados.
 */
void chegadaVeiculo(Pista *PISTAS[], Relogio *r, int *veiculosEntraram, int tam);

/*
 * Função: atualiza os semaforos. O ciclo de rotação dos semáforos é: norte > leste > sul > oeste. Também cria
 * o próximo evento de atualização dos semáforos.
 * Pre: r, SEMAFOROS e sentidoAtual devem ser validos.
 * Pos: os semáforos são atualizados e a proxima atualização é enfileirada.
 */
void attSemaforo(Relogio *r, Semaforo *SEMAFOROS[], int tam, int timeSemaforos, int *sentidoAtual);

/*
 * Função: realiza a troca de pistas e também quando um veículo sai do sistema. Caso a pista destino esteja
 * cheia, a pista origem e o fluxo de carros são bloqueadas. A função também gera novos evenos de troca de pista.
 * Pre: r, PISTAS, SEMAFOROS e veiculosSairam devem ser validos.
 * Pos: a troca é realizada e os novos eventos de troca de pista são enfileirados.
 */
void trocaPista(Relogio *r, Pista *PISTAS[], int tamP, Semaforo *SEMAFOROS[], int *veiculosSairam, int tamS);

/*
 * Função: imprime na tela o resultado da simulação.
 * Pre: PISTAS deve ser valido.
 * Pos: o resultado é impresso na tela.
 */
void resultado(Pista *PISTAS[], int totalTime, int veiculosEntraram, int veiculosSairam);

#endif