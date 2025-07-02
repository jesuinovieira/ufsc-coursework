#ifndef input_interface_h
#define input_interface_h

/*
 * Função: questiona o usuário se ele quer continuar alguma operação ou não. Deve ser respondido com 'Y' ou 'N'.
 * Pré: nenhuma.
 * Pós: retorna 'Y' se sim e 'N' se não.
 */
char yesORnot();

/*
 * Função: le um caractere inserido pelo usuario e retorna em letra maiuscula.
 * Caso o usuario digite mais de uma string, somente o ultimo caractere sera retornado (caractere antes do '\n').
 * Pré: nenhuma.
 * Pós: retorna o comando inserido pelo usuario em letra maiuscula.
 */
char readChar();

/*
 * Função: le uma string inserida pelo usuário.
 * Pré: nElementos deve ser maior que 0.
 * Pós: retorna um ponteiro para a string lida.
 */
char *readString(int nElementos);

/*
 * Função: limpa o buffer de entrada e o de saida.
 * Pré: nenhuma.
 * Pós: o buffer de entrada e o de saida (stdin e sdout) recebem NULL.
 */
void clearBuffer();

#endif