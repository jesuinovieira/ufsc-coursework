#ifndef buffer_interface_h
#define buffer_interface_h

/* Define o tipo buffer_t */
typedef struct buffer buffer_t;


/* ********************************************** FUNCOES DO BUFFER ********************************************* */

/*
 * Função: executa o comando passando como parâmetro.
 * Pré: o buffer deve ser válido. "fname" é opcional.
 * Pós: o comando é executado, caso seja um comando inválido, uma mensagem de aviso é impressa na tela.
 */
void executaCmd(buffer_t *b, char *fname, char cmd);

/*
 * Função: cria um buffer e seta a linha atual para NULL.
 * Pré: nenhuma.
 * Pós: retorna um ponteiro para um buffer com a linha atual setada para NULL. Se der erro na alocacao, retorna NULL.
 */
buffer_t *bufferCria();

/*
 * Função: destroi o buffer especificado em "b". Nenhuma operacao e permitida apos a funcao, a nao ser que buffer cria
 * seja chamada novamente.
 * Pré: "b" deve ser um buffer valido e criado previamente atraves da funcao buffer cria.
 * Pós: os recursos do buffer foram desalocados com sucesso e o buffer "b" torna-se nulo.
 */
void bufferDestroi(buffer_t **b);


/* ******************************************** FUNCOES DOS COMANDOS ******************************************** */

/*
 * Função: lê um arquivo texto, cujo nome é informado pelo usuário, e armazena no buffer.
 * Qualquer informação existente no buffer será descartada. Ao concluir a leitura, a linha corrente será a primeira linha do arquivo.
 * Pré: o buffer deve ser valido. "fname" é opcional.
 * Pós: o buffer contem o conteudo do arquivo lido. Caso de erro na abertura do arquivo, uma mensagem de aviso e imprimida na tela
 * e nada e feito.
 */
void command_R(buffer_t *b, char *fname);

/*
 * Função: escreve o conteúdo do buffer em um arquivo. O nome do arquivo é fornecido pelo usuário.
 * Não ocorre nenhuma alteração no buffer e na linha corrente. Caso o arquivo não exista, ele será criado.
 * Pré: o buffer deve existir e a linha corrente nao deve ser nula.
 * Pós: o conteudo do buffer e escrito no arquivo. Caso o buffer esteja vazio, uma mensagem de aviso é impressa na tela.
 */
void command_W(buffer_t *b);

/*
 * Função: insere em uma linha especificada pelo usuário, uma nova linha também digitada pelo usuário.
 * Após a inserção, a posição atual do cursor passa a ser a posição da nova linha. Caso ultrapasse o tamanho da linha do buffer,
 * a posição do cursor passa a ser a posição da ultima linha inserida. Caso o usuário queira deixar uma linha em branco,
 * quando for pedido para inserir nova linha, digitar o caractere ' ' (espaço).
 * Pré: o buffer deve existir.
 * Pós: a inserção é feita na linha especificada, caso seja maior que o tamanho do buffer, a inseção ocorre na cauda, caso seja
 * uma posição invalida, é emitido uma mensagem na tela.
 */
void command_I(buffer_t *b);

/*
 * Função: apaga a linha corrente e move para a próxima linha. Se for a linha corrente for a ultima do buffer, seta para a anterior.
 * Pré: o buffer e a linha atual devem ser validos.
 * Pós: retorna 1 se a linha foi removida ou 0 caso contrario.
 */
int command_D(buffer_t *b);

/*
 * Função: encontra a primeira linha, iniciando pela linha corrente, que contêm uma string alvo que foi informada pelo usuário.
 * Pré: o buffer deve existir.
 * Pós: se a lista estiver vazia, é impresso na tela uma mensagem de aviso. Caso contrário, linha atual recebera a linha que contem
 * a string alvo ou permanecera inalterada e uma mensagem de aviso será impressa na tela, caso o buffer nao possua a string desejada.
 */
void command_F(buffer_t *b);

/*
 * Função: imprime a linha atual, a posição da linha atual, a quantidade de caracteres da linha atual
 *  e a quantidade de linhas existente no buffer.
 * Pré: o buffer deve existir.
 * Pós: e impresso na tela a quantidade de caracteres que a linha atual possui e a quantidade de linhas do buffer. Se o buffer
 * estiver vazio, é impresso na tela uma mensagem de aviso.
 */
void command_L(buffer_t *b);

/*
 * Função: troca a string fornecida pelo usuário por um texto de substituição também fornecido pelo usuário.
 * Funciona apenas para a linha corrente. Não altera a quantidade de linhas do buffer.
 * Pré: o buffer deve existir.
 * Pós: a substringAlvo contida na linha atual é substituída pela nova substring.
 */
void command_C(buffer_t *b);

/*
 * Função: finaliza imediatamente o editor.
 * Pré: nenhuma.
 * Pós: o editor é finalizado e uma mensagem é impressa na tela.
 */
void command_Q();

/*
 * Função: imprime uma mensagem de ajuda que explica todos os comandos do editor. O programa tambem aceita o caractere '?' como
 * alternativa ao 'H'.
 * Pré: nenhuma.
 * Pós: imprime na tela a lista de comandos.
 */
void command_H();

/*
 * Função: avança uma linha no buffer.
 * Pré: o buffer deve existir.
 * Pós: linha atual aponta para a proxima linha. Caso esteja na ultima linha do buffer ou o mesmo esta vazio, uma mensagem de aviso
 * é impressa na tela.
 */
void command_N(buffer_t *b);

/*
 * Função: volta uma linha no buffer.
 * Pré: o buffer deve existir.
 * Pós: linha atual aponta para a linha anterior. Caso esteja na primeira linha do buffer ou o mesmo esta vazio, uma mensagem de aviso
 * é impressa na tela.
 */
void command_P(buffer_t *b);

/*
 * Função: vai para a primeira linha no buffer.
 * Pré: o buffer deve existir.
 * Pós: linha atual aponta para a primeira linha do buffer.
 */
void command_B(buffer_t *b);

/*
 * Função: vai para a última linha do buffer.
 * Pré: o buffer deve existir.
 * Pós: linha atual aponta para a ultima linha do buffer.
 */
void command_E(buffer_t *b);

/*
 * Função: vai para uma linha específica no buffer. O usuário fornece o número da linha. Caso o numero fornecido seja
 * maior que o tamanho do buffer, vai para a ultima linha.
 * Pré: o buffer deve existir.
 * Pós: linha atual aponta para a linha especificada pelo usuario. Retorrna 1 se tudo ocorreu como o esperado ou 0 caso
 * ocorreu algum erro ou o usuario digitou alguma posição inválida (menor que 1).
 */
int command_G(buffer_t *b);

/*
 * Função: substitui uma linha digita pelo usuário por uma linha específica do buffer. O usuário fornece o número da linha. Caso o
 * numero fornecido seja maior que o tamanho do buffer, vai para a ultima linha.
 * Pré: o buffer deve existir.
 * Pós: a linha corrente é substituida pela linha digitada pelo usuário. Se a linha for menor que 1 ou maior que a quantidade de linhas
 * do buffer, uma mensagem de aviso é impressa na tela e nada é feito.
 */
void command_S(buffer_t *b);

/*
 * Função: mostra todo o conteúdo do buffer na tela.
 * Pré: o buffer deve existir.
 * Pós: imprime o conteudo do buffer na tela ou uma mensagem de aviso, caso o buffer esteja vazio.
 */
void command_V(buffer_t *b);

#endif