#ifndef pista_privado_h
#define pista_privado_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pista_interface.h"
#include "fila_interface.h"

struct veiculo
{
    int tamanho;        		// Tamanho do veículo
    int timeEntrada;    		// Hora que o veículo entrou na pista
};

struct pista
{
    fila_t *f;      			// Fila de veiculos
    int velocidade;     		// Velocidade da pista
    int tamanho;        		// Tamanho da pista
    int tamanhoOcupado; 	// Tamanho ocupado pelos carros
    int tipo;           		// Tipo da pista: transição (0), fonte (1) e sumidouro (2)

    /* Para pistas fontes */
    int limiteSuperior; 		// Limite superior do intervalo de geração de veículos
    int limiteInferior; 		// Limite inferior do intervalo de geração de veículos
    int tempoEntrada;   		// Hora que vai entrar um veiculo na pista
};

#endif