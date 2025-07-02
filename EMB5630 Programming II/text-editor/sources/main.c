/*
 * -------------------------------------------------------------------------------------------
 *  Editor de Texto com Lista Encadeada
 *
 *  Jesuino Vieira Filho (16203244)
 *
 *  Universidade Federal de Santa Catarina (Campus Joinville) - 2017/1
 *  Programação II
 * -------------------------------------------------------------------------------------------
 */

/*
 * Função principal que dara início ao editor.
 * Pré: nenhuma.
 * Pós: lê o arquivo (fornecido, facultativamente, como argumento ao programa) que contêm as linhas,
 * realiza as operações de edição e escreve a nova versão em um arquivo.
 */

/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../header/buffer_interface.h"
#include "../header/input_interface.h"

/* Funcao principal */
int main(int argc, char *argv[])
{

    /* Testa se o numero de argumentos e valido */
    if(argc > 2){
        printf("\e[H\e[2J");
        printf("Numero de argumentos invalido. (Quantidade maxima: 2)\n");
        return 0;
    }

    char cmd, *fname;
    buffer_t *b = bufferCria();
    if(!b) return 0;

    /* Verifica se foi passado o nome do arquivo, caso contrario, fname recebe NULL */
    if(argc == 1)
        fname = NULL;
    else
        fname = argv[argc - 1];

    printf("\e[H\e[2J");
    printf("*** Editor de texto inicializado com sucesso! ***\n");
    printf("--------------------------------------------------\n\n");
    printf("Digite H para ver os possiveis comando.\n");

    do{

        printf("\nComando: ");
        cmd = readChar();

        printf("\e[H\e[2J");
        executaCmd(b, fname, cmd);
        clearBuffer();

    }while(cmd != 'Q');

    bufferDestroi(&b);
    return 0;
}