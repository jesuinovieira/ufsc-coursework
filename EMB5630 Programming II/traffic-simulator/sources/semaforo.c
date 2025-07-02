#include "../header/semaforo_privado.h"

Semaforo *semaforoCria(Pista *chegada, Pista **saidas, int *vetorProbabilidade, int time, int sentido)
{
    if(!chegada || !saidas || time < 0){
        printf("Parametros nulos!\n");
        return NULL;
    }

    Semaforo *s = (Semaforo *)malloc(sizeof(Semaforo));
    if(!s){
        printf("Erro ao alocar memoria do semaforo!\n");
        return NULL;
    }

    s->pistaAferente = chegada;
    s->pistasEferentes = saidas;
    s->probabilidades = vetorProbabilidade;
    s->estado = 0;
    s->time = time;
    s->sentido = sentido;

    return s;
}

void semaforoDestroi(Semaforo **s)
{
    if(!s){
        printf("Parametros nulos!\n");
        return;
    }

    /* Destruimos a estrutura e setamos seu ponteiro para NULL */
    free(*s);
    *s = NULL;
}

void destroiSemaforos(Semaforo *SEMAFOROS[], int tamanho)
{
    while(tamanho > 0)
        semaforoDestroi(&SEMAFOROS[--tamanho]);
}

void openSemaforo(Semaforo *SEMAFOROS[], int tamanhoVetor, int sentido)
{
    if(!SEMAFOROS){
        printf("Parametros nulos!\n");
        return;
    }

    int tmp = 0;
    while(tmp < tamanhoVetor){

        if(SEMAFOROS[tmp]->sentido == sentido)
            SEMAFOROS[tmp]->estado = 1;
        else
            SEMAFOROS[tmp]->estado = 0;

        tmp++;
    }
}

bool sinalAberto(Semaforo *s)
{
    if(!s){
        printf("Parametros nulos!\n");
        return false;
    }

    return (s->estado);
}

void semaforoLibera(Semaforo *SEMAFOROS[], int tam, int hora)
{
    if(!SEMAFOROS){
        printf("Parametros nulos!\n");
        return;
    }

    int i = 0, j, qtdOut, aux, tmp;

    while(i < tam){

        /* Executa o fluxo de carros em cruzamentos abertos */
        if(sinalAberto(SEMAFOROS[i])){

            // Quantidade de carros que iram sair: velocidade da pista / 3. Sendo 3 + tamCarro o tamanho que cada carro ocupa na pista
            qtdOut = (int) velocidadePista(SEMAFOROS[i]->pistaAferente) / (3 + 3);

            while(moveVeiculo(SEMAFOROS[i]->pistaAferente, hora) == 1 && qtdOut > 0){

                /* Calculo em qual pista o carro vai entrar */
                aux = rand() % 101; tmp = 0;

                for(j = 0; j < 3; j++){
                    tmp += SEMAFOROS[i]->probabilidades[j];
                    if(aux <= tmp)
                        break;
                }

                if(realizaTroca(SEMAFOROS[i]->pistaAferente, SEMAFOROS[i]->pistasEferentes[j], hora) == -1)
                    break;

                qtdOut--;
            }
        }

        i++;
    }
}