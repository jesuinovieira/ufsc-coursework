#include "../header/buffer_privado.h"

/* Implementação das funcoes do TDA buffer */

/* TAM é o numero máximo de caracteres das linhas do buffer, não considerando o '\0' */
#define TAM 80


/* ************************************************** FUNCOES DO BUFFER ************************************************** */

buffer_t *bufferCria()
{
    /* Alocando estrutura do buffer */
    buffer_t *b = (buffer_t *) malloc(sizeof(buffer_t));

    if(!b){
        printf("Erro na alocacao de memoria do buffer!\n");
        return NULL;
    }

    /* Criando a lista de strings. Não será necessário função de comparar os dados da lista */
    b->lista = lista_cria(imprimeLine, destroiLine, NULL);
    b->line = NULL;

    return b;
}

void bufferDestroi(buffer_t **b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
        return;
    }

    /* Destruimos a lista de strings. Obs.: lista_destroi chama (*l)->destroi que libera a memoria dos dados alocados na lista */
    lista_destroi(&((*b)->lista));

    (*b)->lista = NULL;
    (*b)->line = NULL;

    /* Desalocamos a estrutura do buffer e setamos seu ponteiro para NULL */
    free(*b);
    *b = NULL;
}

/* ************************************************ FUNCOES DOS COMANDOS ************************************************ */

/* Executa o comando passado por parâmetro */
void executaCmd(buffer_t *b, char *fname, char cmd)
{
    if(!b){
        printf("Buffer nao inicializado.\n");
        return;
    }

    switch(cmd){

        case 'R':
        command_R(b, fname);
        break;

        case 'W':
        command_W(b);
        break;

        case 'I':
        command_I(b);
        break;

        case 'D':
        command_D(b);
        break;

        case 'F':
        command_F(b);
        break;

        case 'L':
        command_L(b);
        break;

        case 'C':
        command_C(b);
        break;

        case 'Q':
        command_Q();
        break;

        case 'H':
        command_H();
        break;

        case '?':
        command_H();
        break;

        case 'N':
        command_N(b);
        break;

        case 'P':
        command_P(b);
        break;

        case 'B':
        command_B(b);
        break;

        case 'E':
        command_E(b);
        break;

        case 'G':
        command_G(b);
        break;

        case 'S':
        command_S(b);
        break;

        case 'V':
        command_V(b);
        break;

        default:
        printf("Comando invalido! Digite H para visualizar a lista de comandos.\n");
    }
}

/* Le um arquivoTXT e armazena no buffer */
void command_R(buffer_t *b, char *fname)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
        return;
    }

    /* Se a lista não esta vazia, o conteúdo do buffer será deletado */
    if(lista_vazia(b->lista) != 1){

        printf("O conteudo do buffer sera descartado. ");
        char cmd = yesORnot();

        if(cmd == 'N')
            return;

        lista_destroi(&(b->lista));
        b->lista = lista_cria(imprimeLine, destroiLine, NULL);
        b->line = NULL;

        fname = NULL;
    }

    FILE *fo;
    if(!fname){

        printf("Digite o nome do arquivo, (../TXT/nome_do_arquivo): ");
        fname = readString(80);

        if(!fname)
            return;

        fo = OpenTXT(fname, "r");

        free(fname);

        if(!fo)
            return;

    }else{

        fo = OpenTXT(fname, "r");
        if(!fo)
            return;
    }

    char *string = (char *)malloc(sizeof(char) * TAM + 1);

    if(!string){
        CloseTXT(fo);
        printf("Erro na alocacao de memoria!\n");
        return;
    }

    while(!feof(fo)){

        if(fgets(string, TAM + 1, fo) != NULL){

            /* Se a string não é composta somente por um '\n', entra no if */
            if(*string != '\n'){

                if(string[strlen(string) - 1] == '\n')
                    string[strlen(string) - 1] = '\0';
            }

            insereCauda(b->lista, (void *)string);
            string = (char *) malloc(sizeof(char) * TAM + 1);

            if(!string){
                CloseTXT(fo);
                return;
            }
        }
    }

    /* Free no ultimo malloc que recebe EOF */
    free(string);

    /* Setamos a linha atual para o inicio do buffer */
    b->line = lista_cabeca(b->lista);
    CloseTXT(fo);
}

/* Escreve o conteudo do buffer em um arquivo */
void command_W(buffer_t *b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
        return;
    }

    /* Caso a lista estiver vazia, nada e feito */
    if(lista_vazia(b->lista)){
        printf("Buffer vazio!\n");
        return;
    }

    char *fname;
    FILE *fo;

    printf("Digite o nome do arquivo, (../output/nome_do_arquivo): ");
    fname = readString(TAM);

    if(!fname)
        return;

    fo = OpenTXT(fname, "w");
    free(fname);

    if(!fo)
        return;

    celula_t *tmp = lista_cabeca(b->lista);

    while(tmp != NULL){

        /* Caso a string contenha somente um '\n', não imprime com a formatação "%s\n" no arquivo */
        if(strcmp((char *)lista_dado(tmp), "\n") == 0)
            fprintf(fo, "%s", (char *)lista_dado(tmp));
        else
            fprintf(fo, "%s\n", (char *)lista_dado(tmp));

        tmp = lista_proximo(tmp);
    }

    CloseTXT(fo);
}

/* Nesse comando a linha nao e removida, diferente do command_S */
void command_I(buffer_t *b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
        return;
    }

    int pos;

    printf("Digite a posicao da linha desejada (0 < pos): ");
    scanf("%d", &pos);

    if(pos <= 0){
        printf("Posicao invalida!\n");
        return;
    }

    char *newLine;

    printf("Digite a nova linha: ");

    do{

        newLine = readString(TAM);
        if(!newLine)
            return;

        /* Caso a string da linha anterior seja do tamanho da linha do buffer mas nao há mais caracteres para ser inserido, sai da loop */
        if(strlen(newLine) == 0){
            free(newLine);
            break;
        }

        lista_insere_posicao(b->lista, pos - 1, (void *)newLine);
        pos++;

    }while(strlen(newLine) == TAM);

    pos--;

    if(pos > lista_tamanho(b->lista)){
        command_E(b);
        return;
    }

    b->line = lista_cabeca(b->lista);
    while(pos > 1 && lista_proximo(b->line) != NULL){
        b->line = lista_proximo(b->line);
        pos--;
    }
}

/* Apaga a linha corrente e move para a proxima linha */
int command_D(buffer_t *b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
        return 0;
    }

    if(lista_vazia(b->lista)){
        printf("Buffer vazio!\n");
        return 0;
    }

    char cmd;

    printf("A linha atual sera removida.\n\
Linha atual: %s\n\n", (char *)lista_dado(b->line));

    cmd = yesORnot();

    if(cmd == 'N')
        return 0;

    celula_t *oldLine = b->line;

    if(lista_eh_cauda(b->lista, b->line))
        b->line = lista_anterior(b->line);
    else
        b->line = lista_proximo(b->line);

    void *tmp;
    lista_remove(b->lista, oldLine, &tmp);

    /* Liberamos a memória do dado da linha removida */
    free(tmp);

    return 1;
}

/* Procura uma substring no buffer */
void command_F(buffer_t *b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
        return;
    }

    if(lista_vazia(b->lista)){
        printf("Buffer vazio!\n");
        return;
    }

    char *str;
    printf("Digite a string alvo: ");

    str = readString(TAM);

    if(!str)
        return;

    celula_t *tmp = b->line;

    /* Percorre a partir da linha atual até o fim do buffer */
    while(tmp != NULL){

        if(strstr((char *)lista_dado(tmp), str) != NULL){
            b->line = tmp;
            printf("Linha: %s\n", (char *)lista_dado(b->line));
            free(str);
            return;
        }

        tmp = lista_proximo(tmp);
    }

    /* Caso nao achou, percorre a partir da primeira linha até a linha anterior da atual */
    tmp = lista_cabeca(b->lista);

    while(tmp != NULL && tmp != b->line){

        if(strstr((char *)lista_dado(tmp), str) != NULL){
            b->line = tmp;
            printf("Linha: %s\n", (char *)lista_dado(b->line));
            free(str);
            return;
        }

        tmp = lista_proximo(tmp);
    }

    /* Caso nao localize a substring, emite uma mensagem de aviso para o usuario */
    printf("Substring nao encontrada!\n");
    free(str);
}

/* Informações do buffer */
void command_L(buffer_t *b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
        return;
    }

    if(lista_vazia(b->lista) != 0 || !b->line){
        printf("Buffer vazio!\n");
        return;
    }

    printf("Linha atual: %s\n\
Posicao da linha atual: %d\n\
Quantidade de caracteres da linha atual: %d\n\n\
Quantidade de linhas do buffer: %d\n\n", (char *)lista_dado(b->line), positionLine(b),
(unsigned int)strlen((char *)lista_dado(b->line)), lista_tamanho(b->lista));

}

/* Troca de substrings: funciona apenas para a linha atual */
void command_C(buffer_t *b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
        return;
    }

    if(lista_vazia(b->lista)){
        printf("Buffer vazio!\n");
        return;
    }

    char cmd;

    printf("Linha atual: %s\n\n", (char *)lista_dado(b->line));
    printf("O processo resultara numa possivel alteracao da linha. ");

    cmd = yesORnot();

    if(cmd == 'N')
        return;

    char *substringAlvo, *newSubstring;

    printf("Digite a substring alvo: ");
    substringAlvo = readString(TAM);

    if(!substringAlvo)
        return;

    if(strstr((char *)lista_dado(b->line), substringAlvo) == NULL){
        printf("Substring alvo não encontrada!\n");
        free(substringAlvo);
        return;
    }

    printf("Digite o texto de substituicao: ");
    newSubstring = readString(TAM);

    if(!newSubstring){
        free(substringAlvo);
        return;
    }

    strReplace((char *)lista_dado(b->line), substringAlvo, newSubstring, TAM + 1);

    free(substringAlvo);
    free(newSubstring);

}

/* Quit */
void command_Q()
{
    printf("EXIT.\n");
}

/* Help */
void command_H()
{
    printf("Comandos:\n\n\
R\tLe um arquivo texto e armazena no buffer.\n\
W\tEscreve o conteudo do buffer em um arquivo.\n\
I\tInsere em uma linha especificada pelo usuario, uma nova linha tambem especificada pelo usuario.\n\
D\tApaga a linha atual.\n\
F\tEncontra a primeira linha que contem uma string alvo.\n\
L\tMostra a quantidade de caracteres na linha atual e o numero de linhas do buffer.\n\
C\tTroca uma string fornecida por um texto tambem fornecido. Funciona apenas para a linha corrente.\n\
Q\tFinaliza o editor.\n\
H\tImprime na tela os comandos do editor.\n\
N\tAvanca para a proxima linha.\n\
P\tVolta para a linha anterior.\n\
B\tVai para a primeira linha do buffer.\n\
E\tVai para a ultima linha do buffer.\n\
G\tVai para uma linha do buffer, que deve ser especificada pelo usuario.\n\
S\tSubstitui uma linha digitada pelo usuario pela linha corrente.\n\
V\tImprime o conteudo do buffer.\n\n");

}

/* Proxima linha */
void command_N(buffer_t *b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
    }else if(lista_vazia(b->lista) != 0 || !b->line){
        printf("Buffer vazio!\n");
    }else{

        if(lista_proximo(b->line) == NULL){
            printf("Voce esta na ultima linha do buffer!\n");
            return;
        }

        b->line = lista_proximo(b->line);
    }
}

/* Linha anterior */
void command_P(buffer_t *b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
    }else if(lista_vazia(b->lista) != 0 || !b->line){
        printf("Buffer vazio!\n");
    }else{

        if(lista_anterior(b->line) == NULL){
            printf("Voce esta na primeira linha do buffer!\n");
            return;
        }

        b->line = lista_anterior(b->line);
    }
}

/* Primeira linha */
void command_B(buffer_t *b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
    }else if(lista_vazia(b->lista)){
        printf("Buffer vazio!\n");
    }else{

        if(b->line == lista_cabeca(b->lista)){
            printf("Voce ja esta na primeira linha do buffer!\n");
            return;
        }
        b->line = lista_cabeca(b->lista);
    }
}

/* Ultima linha */
void command_E(buffer_t *b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
    }else if(lista_vazia(b->lista)){
        printf("Buffer vazio!\n");
    }else{

        if(b->line == lista_cauda(b->lista)){
            printf("Voce ja esta na ultima linha do buffer!\n");
            return;
        }
        b->line = lista_cauda(b->lista);
    }
}

/* Vai para linha especificada */
int command_G(buffer_t *b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
        return 0;
    }

    if(lista_vazia(b->lista)){
        printf("Buffer vazio!\n");
        return 0;
    }

    int pos ;

    printf("Digite a posicao da linha desejada (0 < pos): ");
    scanf("%d", &pos);

    if(pos <= 0){
        printf("Posicao invalida!\n");
        return 0;
    }

    b->line = lista_cabeca(b->lista);

    /* Obs.: a linha 1 é a primeira linha do buffer */
    while(pos > 1 && lista_proximo(b->line) != NULL){
        b->line = lista_proximo(b->line);
        pos--;
    }

    return 1;
}

/* Substituir */
void command_S(buffer_t *b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
        return;
    }

    if(lista_vazia(b->lista) != 0 || !b->line){
        printf("Buffer vazio!\n");
        return;
    }

    if(!command_G(b))
        return;

    if(command_D(b) != 1)
        return;

    printf("Digite a nova linha: ");
    char *newLine = readString(TAM);

    /* Caso o usuário digitou uma strings maior que TAM, se livra dos inputs inválidos */
    while(strlen(newLine) == TAM){
        if(getchar() == '\n')
            break;
    }

    if(!newLine)
        return;

    if(lista_eh_cauda(b->lista, b->line)){

        insereCauda(b->lista, (void *)newLine);
        command_E(b);
        return;
    }

    lista_insere_anterior(b->lista, b->line, (void *)newLine);
    command_P(b);
}

/* Imprimir buffer */
void command_V(buffer_t *b)
{
    if(!b){
        printf("Buffer nao inicializado!\n");
        return;
    }

    if(lista_vazia(b->lista) != 0){
        printf("Buffer vazio!\n");
        return;
    }

    lista_imprime(b->lista);
}