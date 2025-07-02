#ifndef relogio_interface_h
#define relogio_interface_h

#include <stdbool.h>

typedef struct fila fila_t;
typedef struct relogio Relogio;
typedef struct evento Evento;

/*
 * Função: cria e inicializa um relogio. totalTime é o tempo total de execução.
 * Pre: totalTime deve ser maior que 0;
 * Pos: retorna um ponteiro para o relogio se houver memória disponível.
 */
Relogio *relogioCria(int totalTime);

/*
 * Função: destroi um relogio.
 * Pre: o relogio deve ser valido.
 * Pos: a memória de relogio é desalocada.
 */
void relogioDestroi(Relogio **relogio);

/*
 * Função: incrementa a hora do relogio (1 segundo).
 * Pre: o relogio deve ser valido.
 * Pos: r->hora é incrementado.
 */
void skipTime(Relogio *r);

/*
 * Função: retorna a hora atual do relogio.
 * Pre: o relogio deve ser valido.
 * Pos: a hora atual é retornada.
 */
int horaAtual(Relogio *relogio);

/*
 * Função: verifica se hora atual é menor ou igual que o tempo total da execucao.
 * Pre: o relogio deve ser valido.
 * Pos: retorna "true" se sim, "false" caso contrario.
 */
bool simulador(Relogio *r);

/*
 * Função: compara dois eventos.
 * Pre: e1 e e2 devem ser validos.
 * Pos: retorna -2 se e1 ou e2 são nulos.
 * -1, se tempo de entrada de e1 < tempo de entrada de e2
 * 0, se tempo de entrada de e1 = tempo de entrada de e2
 * 1, se tempo de entrada de e1 > tempo de entrada de e2
 */
int eventoCompara(Evento *e1, Evento *e2);

/*
 * Função: cria um evento.
 * Pre: relogio deve ser valido.
 * Pos: retorna 1 se o evento foi criado e enfileirado corretamente, retorna 0 de hora é maior que o tempo
 * total de execução. Caso contrário, retorna -1.
 */
int eventoCria(Relogio *relogio, int hora, int tipo);

/*
 * Função: destroi um evento.
 * Pre: evento deve ser valido.
 * Pos: a memória apontada por evento é desalocada.
 */
void eventoDestroi(Evento *evento);

/*
 * Função: retorna o tipo do evento.
 * Pre: "e" deve ser valido.
 * Pos: o tipo do evento é retornado.
 */
int eventoTipo(Evento *e);

/*
 * Função: retorna o tipo do proximo evento.
 * Pre: relogio deve ser valido.
 * Pos: retorna o tipo do evento ou -1 se relogio é invalido ou se a fila de eventos é vazia.
 */
int proximoEvento(Relogio *relogio);

/*
 * Função: desenfileira um evento se esta no seu horario de execução.
 * Pre: evento deve ser valido.
 * Pos: o evento é retornado por referência em "evento". A função retorna 1 em caso de sucesso,
 * -1 se relogio é invalido ou 0 se a fila de eventos é vazia ou se não é a hora de execução do evento.
 */
int eventoDesenfileira(Relogio *relogio, Evento **evento);

#endif