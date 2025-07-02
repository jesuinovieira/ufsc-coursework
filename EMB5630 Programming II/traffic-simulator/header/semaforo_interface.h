#ifndef semaforo_interface_h
#define semaforo_interface_h

#include <stdbool.h>

typedef struct pista Pista;
typedef struct semaforo Semaforo;

/*
 * Função: cria um semaforo e inicializa.
 * Pre: chegada e saidas devem ser validos, time deve ser maior que 0.
 * Pos: retorna um ponteiro para o semáforo criado se houver memória disponível.
 */
Semaforo *semaforoCria(Pista *chegada, Pista **saidas, int *vetorProbabilidade, int time, int sentido);

/*
 * Função: destroi um semaforo.
 * Pre: "s" deve ser valido.
 * Pos: a memória é desalocada.
 */
void semaforoDestroi(Semaforo **s);

/*
 * Função: destroi um vetor de semaforos. O tamanho do vetor é passado como argumento da função.
 * Pre: SEMAFOROS deve ser valido.
 * Pos: a memória de todos semaforos é desalocada.
 */
void destroiSemaforos(Semaforo *SEMAFOROS[], int tamanho);

/*
 * Função: abre os semaforos com o sentido passado como argumento da função.
 * Pre: SEMAFOROS deve ser valido.
 * Pos: os semaforos com o sentido passado como argumento são abertos e os outros são fechados.
 */
void openSemaforo(Semaforo *SEMAFOROS[], int tamanhoVetor, int sentido);

/*
 * Função: libera os carros que estão nas pistas com o semáforo aberto e a troca de pistas é realizada.
 * Pre: SEMAFOROS deve ser valido.
 * Pos: os carros são liberados e as trocas de pista são efetuadas. No caso da pista destino estiver cheia,
 * o carro bloqueia a pista e ocorre um engarrafamento.
 */
void semaforoLibera(Semaforo *SEMAFOROS[], int tam, int hora);

/*
 * Função: verifica se o sinal esta aberto (1).
 * Pre: "s" deve ser valido.
 * Pos: retorna "true" se sim, "false" caso contrário.
 */
bool sinalAberto(Semaforo *s);

#endif