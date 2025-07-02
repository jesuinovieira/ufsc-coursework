#include "../header/input_privado.h"

/* Implementação das funcoes do TDA input */

char yesORnot()
{

    printf("Deseja continuar? (Y or N) ");
    char cmd = readChar();

    while(cmd != 'Y' && cmd != 'N'){
        printf("Comando invalido! Digite Y para sim ou N para nao: ");
        cmd = readChar();
    }

    return cmd;
}

char readChar()
{
    char cmd;

    cmd = getchar();

    while(cmd == '\n')
        cmd = getchar();

    /* Remove o '\n' do usuário apos ele digitar um comando */
    getchar();

    return cmdToupper(cmd);
}

char *readString(int nElementos)
{
    if(nElementos < 1)
        return NULL;

    char *string = (char *)malloc(sizeof(char) * nElementos + 1);

    if(!string){
        printf("Erro na alocacao de memoria.\n");
        return NULL;
    }

    unsigned int contador = 0;
    char caractereLido;

    clearBuffer();
    while(contador < nElementos){

        caractereLido = getchar();
        if(caractereLido == '\n')
            break;

        string[contador++] = caractereLido;
    }

    string[contador] = '\0';

    clearBuffer();
    return string;
}


void clearBuffer()
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
}