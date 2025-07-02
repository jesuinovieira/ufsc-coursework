# Implementação

O programa resume-se em um editor de texto primitivo. Os comandos suportador pelo editor estão descritos detalhadamente em `/header/buffer_interface.h`. 
A estrutura do programa foi baseada na implementação de tipos abstratos de dados (TDA). O programa contém três TDA's:

- **TDA lista:** contém as operações da lista genérica duplamente encadeada. 
- **TDA buffer:** contém as operações do editor e as operações para criar/destruir o buffer.
- **TDA input:** contém algumas operações de interação com o usuário.
	
A descrição detalhada de cada TDA e suas funções se encontra na pasta header `/header`.

# Funcionamento

O editor funciona de maneira simples. A estrutura do buffer é composta por um ponteiro para uma lista aonde cada
nó representa uma linha do buffer. Também possui uma ponteiro para o nó atual, de modo que o usuário consiga se localizar
no texto e realizar as operações de edição no lugar correto. A cada comando a tela será atualizada.
O tamanho de cada linha (TAM) é definido em `/sources/buffer.c` na linha 6. Observe que o numero máximo de 
caracteres não inclui o caractere de final de string `\0`.

# Observações

Atenção, para melhor funcionamento do editor:

- Não digite mais de um comando por vez.
- Quando for pedido para inserir a posição, não insira um caractere que não seja numérico. 
- Para fins de organização, os arquivos para edição devem ser encontrados em uma pasta `/TXT` e os arquivos de saída
(pós edição) em uma pasta `/output`. Assim, tanto no comando `R` como no comando `W`, deve ser inserido o diretório de acordo
com as especificações: `../TXT/nome_do_arquivo_para_edição` ou `../output/nome_do_arquivo_de_saída`.

# Execução

Inicialize o terminal na pasta que contém o Makefile e digite para:

	Compilar o programa:
		$ make

	Executar o programa:
		$ make run

	Remover os arquivos objetos:
		$ make clean

	Remover todos os arquivos:
		$ make remove

	Para executar o programa com o valgrind:

	Após ser gerado o arquivo executável, inicialize o terminal na pasta /bin e digite:
		$ valgrind ./Editor
		
Para fornecer um arquivo como argumento após o executável, considerando que o arquivo esteja no diretório `../TXT`:
	
	Após ser gerado o arquivo executável, inicialize o terminal na pasta /bin e digite:
		$ ./Editor ../TXT/nome_do_arquivo
