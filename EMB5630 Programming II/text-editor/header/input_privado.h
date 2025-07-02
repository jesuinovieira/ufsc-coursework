#ifndef input_privado_h
#define input_privado_h

/* Bibliotecas */
#include "input_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* ************************************************* FUNÇÕES PRIVADAS ************************************************* */

/* Retorna o caractere em letra maiuscula */
int cmdToupper(int cmd)
{
    return toupper(cmd);
}

#endif