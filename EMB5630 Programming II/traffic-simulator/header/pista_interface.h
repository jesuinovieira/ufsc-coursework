#ifndef pista_interface_h
#define pista_interface_h

#include <stdbool.h>

typedef struct pista Pista;
typedef struct veiculo Veiculo;
typedef struct fila fila_t;

/*
 * Função: cria uma pista.
 * Pre: tam deve ser maior que 0.
 * Pos: retorna um ponteiro para uma pista se houver memória disponível.
 */
Pista *pistaCria(int velocidade, int tam, int tipo, int limiteSuperior, int limiteInferior);

/*
 * Função: recebe um vetor de pista e seu tamanho. Destroi todas as pistas. Nenhuma operacao é permitida apos a funcao,
 * a nao ser que fila cria seja chamada novamente.
 * Pre: o vetor de pistas deve ser valido.
 * Pos: a memória das pistas é desalocada.
 */
void destroiPistas(Pista *PISTAS[], int tamanho);

/*
 * Função: destroi uma pista. Nenhuma operacao é permitida apos a funcao,
 * a nao ser que fila cria seja chamada novamente.
 * Pre: a pistas deve ser valida.
 * Pos: a memória da pista é desalocada.
 */
void pistaDestroi(Pista **pista);

/*
 * Função: retorna o tipo da pista.(Transição (0), fonte (1) e sumidouro (2))
 * Pre: a pista deve ser valida.
 * Pos: o tipo da pista é retornado.
 */
int pistaTipo(Pista *pista);

/*
 * Função: retorna a quantidade de veiculos que atualmente estão na pista.
 * Pre: a pista deve ser valida.
 * Pos: retorna a quantidade de veiculos.
 */
int qtdVeiculos(Pista *pista);

/*
 * Função: retorna a velocidade da pista.
 * Pre: a pista deve ser valida.
 * Pos: a velocidade da pista é retornada.
 */
int velocidadePista(Pista *pista);

/*
 * Função: retorna a hora que vai entrar um novo carro na pista.
 * Pre: a pista deve ser valida.
 * Pos: a hora que vai entrar um novo carro na pista é retornada.
 */
int tempoEntrada(Pista *pista);

/*
 * Função: verifica se a pista possui espaço para a entrada de um carro de tamanho "tam".
 * Pre: a pista deve ser valida.
 * Pos: retorna "true" se possui espaço ou "false", caso contrário.
 */
bool verificaDisponibilidade(Pista *pista, int tam);

/*
 * Função: verifica se a pista esta vazia.
 * Pre: a pista deve ser valida.
 * Pos: retorna "true" se a pista esta vazia ou é nula, caso contrário, retorna "false".
 */
bool pistaVazia(Pista *pista);

/*
 * Função: gera dentro dos limites de frequência da pista, aleatoriamente, um horário para a geração de um novo veículo.
 * Pre: a pista deve ser valida.
 * Pos: a hora de geração de um novo veículo é retornada. Se a pista for nula, retorna -1.
 */
int gerarVeiculo(Pista *pista, int horaAtual);

/*
 * Função: retorna a hora que o primeiro veículo da pista deve sair.
 * Pre: a pista deve ser valida.
 * Pos: se o horario é menor que o parametro "hora", retorna hora. Caso contrario o tempo de saída é retornado.
 */
int horaSaida(Pista *pista, int hora);

/*
 * Função: verifica se o primeiro veículo da pista ja percorreu ela totalmente.
 * Pre: a pista deve ser valida.
 * Pos: retorna 1 se sim, 0 caso contrário.
 */
int moveVeiculo(Pista *pista, int time);

/*
 * Função: desenfileira um veículo de "origem" e enfileira em "destino"
 * Pre: origem e destino devem ser válidos.
 * Pos: retorna 1 em caso de sucesso, e 0 caso contrário.
 */
int realizaTroca(Pista *origem, Pista *destino, int hora);

/*
 * Função: compara o tempo de entrada de v1 com o tempo de entrada de v2.
 * Pre: v1 e v2 devem ser validos.
 * Pos: retorna -2 se v1 ou v2 são nulos.
 * -1, se tempo de entrada de v1 < tempo de entrada de v2
 * 0, se tempo de entrada de v1 = tempo de entrada de v2
 * 1, se tempo de entrada de v1 > tempo de entrada de v2
 */
int veiculoCompara(Veiculo *v1, Veiculo *v2);

/*
 * Função: cria um veiculo e enfileira na pista.
 * Pre: a pista deve ser valida.
 * Pos: retorna a hora previsa para o veículo sair da pista. Em caso de algum erro, -1 é retornado.
 */
int veiculoCria(Pista *pista, int tam, int horaAtual);

/*
 * Função: destroi um veiculo.
 * Pre: o veiculo deve ser valido.
 * Pos: a memoria é liberada.
 */
void veiculoDestroi(Veiculo *veiculo);

/*
 * Função: desenfileira um veiculo da pista.
 * Pre: a pista deve ser valida.
 * Pos: o veiculo é desenfileirado e o tamanho ocupado da pista é diminuido. Retorna -1 se a pista é nula,
 * 0 se a pista esta vazia e 1 em caso de sucesso.
 */
int veiculoDesenfileira(Pista *pista, Veiculo **veiculo);

/*
 * Função: desenfileira e destroi um veiculo da pista.
 * Pre: pista e veiculosSairam devem ser validos.
 * Pos: o veiculo é desenfileirado e veiculosSairam é incrementado.
 */
void veiculoSai(Pista *pista, int *veiculosSairam);

#endif