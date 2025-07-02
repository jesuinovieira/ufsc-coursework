# Execução

Inicialize o terminal na pasta que contém o Makefile e digite para:

	Compilar o programa:
		$ make

	Executar o programa com tipo de jogo e dificuldade padrão:
		$ make run

	Para escolher o tipo de jogo:
		Jogar contra um amigo:		$ make ARGS="1" run
		Facil:				$ make ARGS="2 1" run
		Intermediario:			$ make ARGS="2 2" run
		Dificil:			$ make ARGS="2 3" run
	
	Remover os arquivos objetos:
		$ make clean

	Remover todos os arquivos:
		$ make remove

# Comandos

Para selecionar a posição que deseja marcar insira, primeiramente a linha e depois a 
coluna. Exemplo:

	Linha: 2
	Coluna: 2 
