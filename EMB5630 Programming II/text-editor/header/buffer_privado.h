#ifndef buffer_privado_h
#define buffer_privado_h

/* Bibliotecas */
#include "buffer_interface.h"
#include "lista_interface.h"
#include "input_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Estrutura do buffer */
struct buffer{
    lista_t *lista;                 // Lista de strings
    celula_t *line;               // Linha atual
};

/* ************************************************* FUNÇÕES PRIVADAS ************************************************* */

/*
 * Função: abre o arquivo que contem o nome passado por parametro.
 * Pré: o arquivo deve existir e o modo deve ser valido.
 * Pós: retorna um ponteiro para o arquivo. Se der erro, retorna NULL.
 */
FILE *OpenTXT(const char *filename, const char *modo)
{
    FILE *fo;

    fo = fopen(filename, modo);

    if(!fo){
        printf("Erro ao abrir o arquivo!\n");
        return NULL;
    }

    return fo;
}

/*
 * Função: abre o arquivo que contem o nome passado por parametro.
 * Pré: o arquivo deve existir e o modo deve ser valido.
 * Pós: retorna um ponteiro para o arquivo. Se der erro, retorna NULL.
 */
int CloseTXT(FILE *arq)
{
    /* Retorna 0 se o arquivo foi fechado com sucesso */
    if(!arq)
        return 1;
    else
        return fclose(arq);
}

/*
 * Função: sabe como imprimir os dados da lista.
 * Pré: elem deve ser válido.
 * Pós: o dado da lista é impresso na tela.
 */
void imprimeLine(const void *elem)
{
    if(elem != NULL){

        if(strcmp((char *)elem, "\n") == 0)
            printf("%s", (char*)elem);
        else
            printf("%s\n", (char*)elem);
    }
}

/*
 * Função: sabe como destruir os dados da lista.
 * Pré: elem deve ser válido.
 * Pós: o dado da lista é destruído.
 */
void destroiLine(void *elem)
{
    if(elem != NULL)
        free(elem);
}

/*
 * Função: retorna a posição da linha atual do buffer.
 * Pré: o buffer deve ser valido e a lista não deve estar vazia.
 * Pós: a posição da linha atual do buffer é retornada.
 */
int positionLine(buffer_t *b)
{
    if(!b || lista_vazia(b->lista) != 0)
        return 0;

    int posAtual = 1;
    celula_t *tmp = lista_cabeca(b->lista);

    while(tmp != NULL){

        if(tmp == b->line)
            return posAtual;

        tmp = lista_proximo(tmp);
        posAtual++;
    }

    return 0;
}

/*
 * Função: substitui uma substring alvo por uma nova substring na string principal.
 * Pré: as três strings devem ser validas e o numero de elementos maior que zero.
 * Pós: substitui a substringAlvo em str por newSubstring.
 */
void strReplace(char *str, char *substringAlvo, char *newSubstring, int nElementos)
{
    if(!str || !substringAlvo || !newSubstring){
        printf("String invalida!\n");
        return;
    }

    if((int)strlen(str) + (int)strlen(newSubstring) - (int)strlen(substringAlvo) >= nElementos){
        printf("Quantidade maxima de caracteres da linha ultrapassada!\n");
        return;
    }

    char *tmp = (char *)malloc(sizeof(char) * nElementos + 1);
    char *strAux;
    int i = 0, strTam = 0;

    /* Da pra incluir o \0 no final da strings depois de lida */
    memset(tmp, '\0', nElementos + 1);

    while((strAux = strstr(&str[i], substringAlvo)) != NULL){

        /* Tamanho da string até a primeira ocorrencia da substringAlvo */
        strTam = strlen(str) - strlen(strAux);

        /* Copia na string temporaria até a substringAlvo */
        memcpy(tmp, str, strTam + 1);

        /* Copia na string temporaria, a partir do caso anterior, a newSubstring */
        memcpy(tmp + strlen(str) - strlen(strAux), newSubstring, strlen(newSubstring) + 1);

        /* Copia na string temporaria, a partir do caso anterior, o resto da string*/
        memcpy(tmp + strlen(str) - strlen(strAux) + strlen(newSubstring), strAux + strlen(substringAlvo), strlen(strAux) - strlen(substringAlvo) + 1);

        /* Copia na string do buffer a string temporaria*/
        memcpy(str, tmp, strlen(tmp) + 1);


        i = strTam + strlen(newSubstring);

        if(i > (int)sizeof(str))
            break;
    }

    free(tmp);
}

#endif