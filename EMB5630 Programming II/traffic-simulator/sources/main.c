#include "../header/sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    printf("\e[H\e[2J");
    int i = 0, tmp = 0, totalTime = 0, tempoSemaforos = 0, sentidoAtual = 0, veiculosEntraram = 0, veiculosSairam = 0;
    srand(time(NULL));

    printf("==========================================================================\n");
    printf("\t\t\tSIMULADOR DE TRAFEGO\n");
    printf("==========================================================================\n");

    printf("Digite o tempo total de simulacao [horas]: "); scanf("%d", &totalTime);
    printf("Digite o tempo dos semaforos [segundos]: "); scanf("%d", &tempoSemaforos);

    if(totalTime <= 0){
        printf("Tempo de execucao invalido!\n");
        return 0;
    }

    if(tempoSemaforos <= 0){
        printf("Tempo de mudanca de estados do semaforo invalido!\n");
        return 0;
    }

    printf("\nExecutando a simulacao:\n");
    /* Passa o tempo para segundos */
    totalTime = totalTime * 3600;

    /* Vetor de pistas */
    Pista *PISTAS[14];

    /* Criando as pistas sumidouros */
    PISTAS[0] = pistaCria(60,500,2,0,0);        // N1Norte
    PISTAS[1] = pistaCria(40,500,2,0,0);        // N2Norte
    PISTAS[2] = pistaCria(60,500,2,0,0);        // S1Sul
    PISTAS[3] = pistaCria(40,500,2,0,0);        // S2Sul
    PISTAS[4] = pistaCria(80,2000,2,0,0);      // O1Oeste
    PISTAS[5] = pistaCria(30,400,2,0,0);        // L1Leste

    /* Criando as pistas fontes */
    PISTAS[6] = pistaCria(60,500,1,25,15);    // N1Sul
    PISTAS[7] = pistaCria(40,500,1,25,15);    // N2Sul
    PISTAS[8] = pistaCria(60,500,1,37,23);    // S1Norte
    PISTAS[9] = pistaCria(40,500,1,75,45);    // S2Norte
    PISTAS[10] = pistaCria(80, 2000,1,12,8); // O1Leste
    PISTAS[11] = pistaCria(30,400,1,12,8);    // L1Oeste

    /* Criando as pistas centrais */
    PISTAS[12] = pistaCria(60,300,0,0,0);      // C1Oeste
    PISTAS[13] = pistaCria(60,300,0,0,0);      // C1Leste

    /* Vetor de semaforos */
    Semaforo *SEMAFOROS[8];

                                                    /* Cruzamento S1 */
    /* O1Leste */
    Pista *S_O1Leste[3] = {PISTAS[13], PISTAS[0], PISTAS[2]}; int P_O1Leste[3] = {80, 10, 10};
    SEMAFOROS[0] = semaforoCria(PISTAS[10], S_O1Leste, P_O1Leste, tempoSemaforos,1);

    /* N1Sul */
    Pista *S_N1Sul[3] = {PISTAS[2], PISTAS[13], PISTAS[4]}; int P_N1Sul[3] = {10, 80, 10};
    SEMAFOROS[1] = semaforoCria(PISTAS[6], S_N1Sul, P_N1Sul, tempoSemaforos,2);

    /* S1Norte */
    Pista *S_S1Norte[3] = {PISTAS[1], PISTAS[4], PISTAS[13]}; int P_S1Norte[3] = {10, 10, 80};
    SEMAFOROS[2] = semaforoCria(PISTAS[8], S_S1Norte, P_S1Norte, tempoSemaforos,0);

    /* C1Oeste */
    Pista *S_C1Oeste[3] = {PISTAS[4], PISTAS[2], PISTAS[1]}; int P_C1Oeste[3] = {40, 30, 30};
    SEMAFOROS[3] = semaforoCria(PISTAS[12], S_C1Oeste, P_C1Oeste, tempoSemaforos,3);

                                                    /* Cruzamento S2 */
    /* C1Leste */
    Pista *S_C1Leste[3] = {PISTAS[5], PISTAS[1], PISTAS[3]}; int P_C1Leste[3] = {40, 30, 30};
    SEMAFOROS[4] = semaforoCria(PISTAS[13], S_C1Leste, P_C1Leste, tempoSemaforos,1);

    /* N2Sul */
    Pista *S_N2Sul[3] = {PISTAS[3], PISTAS[5], PISTAS[12]}; int P_N2Sul[3] = {30, 40, 30};
    SEMAFOROS[5] = semaforoCria(PISTAS[7], S_N2Sul, P_N2Sul, tempoSemaforos,2);

    /* S2Norte */
    Pista *S_S2Norte[3] = {PISTAS[1], PISTAS[5], PISTAS[12]}; int P_S2Norte[3] = {30, 40, 30};
    SEMAFOROS[6] = semaforoCria(PISTAS[9], S_S2Norte, P_S2Norte, tempoSemaforos,0);

    /* L1Oeste */
    Pista *S_L1Oeste[3] = {PISTAS[12], PISTAS[3], PISTAS[1]}; int P_L1Oeste[3] = {30, 30, 40};
    SEMAFOROS[7] = semaforoCria(PISTAS[11], S_L1Oeste, P_L1Oeste, tempoSemaforos,3);


    /* Cria o relogio da simulacao */
    Relogio *relogio = relogioCria(totalTime);

    /* Cria os eventos iniciais do programa */
    for(i = 0; i < 6; i++){
            tmp = gerarVeiculo(PISTAS[i], 0);
            eventoCria(relogio, tmp, 1);
    }

    /* Abre os semaforos sentido norte (0) e cria o proximo evento para atualizar os semáforos */
    sentidoAtual = 0;
    openSemaforo(SEMAFOROS, 8, sentidoAtual);
    eventoCria(relogio, tempoSemaforos, 2);


    /* Inicio da simulacao */
    Evento *evento = NULL;
    while(simulador(relogio)){

        evento = NULL;
        while(eventoDesenfileira(relogio, &evento)){

            switch(eventoTipo(evento)){
                case 1:
                    chegadaVeiculo(PISTAS, relogio, &veiculosEntraram, 14);
                    eventoDestroi(evento);
                    break;
                case 2:
                    attSemaforo(relogio, SEMAFOROS, 8, tempoSemaforos, &sentidoAtual);
                    eventoDestroi(evento); // veiculosSairam
                    break;
                case 3:
                    trocaPista(relogio, PISTAS, 14, SEMAFOROS, &veiculosSairam, 8);
                    eventoDestroi(evento);
                    break;
                default:
                    eventoDestroi(evento);
                    break;
            }
        }

        /* Cada loop representa 1 segundo de simulacao */
        skipTime(relogio);
    }

    /* Resultado da simulacao */
    resultado(PISTAS, totalTime, veiculosEntraram, veiculosSairam);

    /* Destroi todas as pistas */
    destroiPistas(PISTAS, 14);
    /* Destroi todos os semáforos */
    destroiSemaforos(SEMAFOROS, 8);
    /* Destroi o relogio */
    relogioDestroi(&relogio);

    return 0;
}