# Execução

Inicialize o terminal na pasta que contém o Makefile e digite para:

	Compilar o programa:
		$ make

	Executar o programa com tipo de jogo e dificuldade padrão (Jogador contra Ambiente com nível de dificuldade difícil):
		$ make run

	Para escolher o tipo de jogo:
		Jogador contra Jogador:				$ make ARGS="JxJ" run;
		Jogador contra Ambiente [Facil]:	$ make ARGS="JxA F" run;
		Jogador contra Ambiente [Dificil]:	$ make ARGS="JxA D" run;
	
	Remover os arquivos objetos:
		$ make clean

	Remover todos os arquivos:
		$ make remove

# Comandos

O(s) usuário(s) entraram com as jogadas até que o jogo termine ou que algum deles 
desista. Sao exemplos de entrada: A1, F13, O9. Caso deseja abandonar a partirda, digite 
`S` ou `Sair` como entrada da jogada.

# Atenção
	
Os comandor para executar o jogo são vulneráveis, portante, utilize corretamente para a 
melhor execução do programa. Por exemplo, os comandos a seguir são diferentes:

    $ make ARGS="JXJ" run; 
    $ make ARGS="JxJ" run;

Para saber informações mais detalhadas e toda o desenvolvimento do programa, consulte o 
arquivo `docs/relatorio.pdf`.
