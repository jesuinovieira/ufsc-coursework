#include "../header/sistema.h"

void chegadaVeiculo(Pista *PISTAS[], Relogio *r, int *veiculosEntraram, int tam)
{
    if(!PISTAS || !r || !veiculosEntraram){
        printf("Parametros nulos!\n");
        return;
    }

    int hora = horaAtual(r);
    int i = 0;

    /* Percorre apenas as pistas fonte */
    while(i < tam){

        /* Verifica se esta na hora de criar um carro */
        if(tempoEntrada(PISTAS[i]) == hora && pistaTipo(PISTAS[i]) == 1){

            /* tmp recebe o tempo que o veiculo levará para percorrer a pista */
            int tmp = veiculoCria(PISTAS[i], 3, hora);

            /* Verifica se a pista estava cheia */
            if(tmp != -1){
                (*veiculosEntraram)++;
                /* Cria o evento de saida do veiculo */
                eventoCria(r, tmp + hora, 3);
            }

            tmp = gerarVeiculo(PISTAS[i], hora);
            //printf("%d %d\n", tmp, hora);
            /* Cria o evento da proxima chegada de veiculos */
            eventoCria(r, tmp, 1);
        }

        i++;
    }
}

void attSemaforo(Relogio *r, Semaforo *SEMAFOROS[], int tam, int timeSemaforos, int *sentidoAtual)
{
    if(!r || !SEMAFOROS || !sentidoAtual){
        printf("Parametros nulos!\n");
        return;
    }

    if(*sentidoAtual == 3)
        *sentidoAtual = 0;
    else
        *sentidoAtual = *sentidoAtual + 1;

    openSemaforo(SEMAFOROS, tam, *sentidoAtual);

    int timeAtual = horaAtual(r);
    eventoCria(r, timeAtual, 3);
    eventoCria(r, (timeAtual + timeSemaforos), 2);
}

void trocaPista(Relogio *relogio, Pista *PISTAS[], int tamP, Semaforo *SEMAFOROS[], int *veiculosSairam, int tamS)
{
    if(!relogio || !PISTAS || !SEMAFOROS || !veiculosSairam){
        printf("Parametros nulos!\n");
        return;
    }

    int hora = horaAtual(relogio);
    semaforoLibera(SEMAFOROS, tamS, horaAtual(relogio));

    int i = 0, tmp, next = proximoEvento(relogio);

    while(i < tamP){

        /* Para as pintas sumidouros, verifica se há veiculos para sair do sistema */
        if(pistaTipo(PISTAS[i]) == 2){

            while(moveVeiculo(PISTAS[i], hora))
                veiculoSai(PISTAS[i], veiculosSairam);
        }

        /* Se o proximo evento nao é troca de pistas, cria a proxima troca */
        if(next != 3){

            tmp = horaSaida(PISTAS[i], hora);
            if(tmp != -1 && tmp > hora)
                eventoCria(relogio, tmp, 3);
        }

        i++;
    }
}

void resultado(Pista *PISTAS[], int totalTime, int veiculosEntraram, int veiculosSairam)
{
    if(!PISTAS){
        printf("Parametros nulos!\n");
        return;
    }

    printf("==========================================================================\n");
    printf("\t\t\tTempo de simulacao [%dh]\n\n", totalTime/3600);

    printf("Numero total de veiculos que entraram no sistema ------------------- %d\n", veiculosEntraram);
    printf("Numero total de veiculos que sairam do sistema --------------------- %d\n", veiculosSairam);

    printf("Numero de veiculos no sistema -------------------------------------- %d\n\n", veiculosEntraram - veiculosSairam);


    printf("Rua\t\tVeiculos\t\t\t    Rua\t\t  Veiculos\n\n");
    printf("O1Leste ---------- %d\t\t\t\t", qtdVeiculos(PISTAS[10]));
    printf("    O1Oeste ---------- %d\n\n", qtdVeiculos(PISTAS[4]));
    printf("C1Leste ---------- %d\t\t\t\t", qtdVeiculos(PISTAS[13]));
    printf("    C1Oeste ---------- %d\n\n", qtdVeiculos(PISTAS[12]));
    printf("L1Leste ---------- %d\t\t\t\t", qtdVeiculos(PISTAS[5]));
    printf("    L1Oeste ---------- %d\n\n", qtdVeiculos(PISTAS[11]));
    printf("N1Norte ---------- %d\t\t\t\t", qtdVeiculos(PISTAS[0]));
    printf("    N1Sul ------------ %d\n\n", qtdVeiculos(PISTAS[6]));
    printf("S1Norte ---------- %d\t\t\t\t", qtdVeiculos(PISTAS[8]));
    printf("    S1Sul ------------ %d\n\n", qtdVeiculos(PISTAS[2]));
    printf("N2Norte ---------- %d\t\t\t\t", qtdVeiculos(PISTAS[1]));
    printf("    N2Sul ------------ %d\n\n", qtdVeiculos(PISTAS[7]));
    printf("S2Norte ---------- %d\t\t\t\t", qtdVeiculos(PISTAS[9]));
    printf("    S2Sul ------------ %d\n", qtdVeiculos(PISTAS[3]));
    printf("==========================================================================\n");
}