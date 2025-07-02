# Implementação

O programa resume-se em uma simulação de tráfego em dois cruzamentos (S1 e S2). Cada 
pista é representada por uma fila e cada semáforo possui um vetor das pistas que fazer 
parte dele (dividindo-as em eferentes e aferentes). O relógio do sistema possui um fila 
de evento, a fila é ordenada por hora de ocorrência dos mesmos. No total, o sistema 
possui 14 vias e 8 semáforos.

A estrutura do programa foi baseada na implementação de tipos abstratos de dados (TDA). 
O programa contém quatro TDA's:

- **TDA fila:** contém as operações de uma fila genérica. 
- **TDA pista:** contém as operações envolvendo as pistas e os veiculo, os quais são 
representados como uma fila na estrutura da pista. (Para melhor organização, o arquivo 
.c foi dividido em duas partes, pista.c e veiculo.c).
- **TDA relogio:** contém as operações envolvendo o relogio e os eventos, os quais são 
representados como uma fila na estrutura da pista. (Para melhor organização, o arquivo 
.c foi dividido em duas partes, relogio.c e evento.c).
- **TDA semaforo:** contém as operações envolvendo os semáforos do sistema. 

A descrição detalhada de cada TDA e suas funções se encontra na pasta header (/header).

# Funcionamento

No início da simulação, o usuário deve inserir o tempo total e o tempo de mudança de 
estado do semáforo. Cada loop do laço while (linha 101, main.c) representa um segundo 
de simulação. 

O programa irá gerar seis eventos iniciais de chegada de veículo para dar inicio ao 
programa, sendo que os proximos serão consequência destes. Cada evento é enfileirado 
ordenadamente na fila de eventos da estrutura do relógio, a ordenação é baseada na sua 
hora de execução.

São eventos: 

- Chegada de um novo veículo
- Mudança de estado dos semáforos
- Troca de pista

A hora de chegada de um novo veículo nas pistas fonte e a pista para qual o veículo vai 
é calculada a partir de probabilidades (slide 13 e 14, Transito.pdf). Cada pista fonte 
possui uma frequência de geração de carros e cada semáforo possui um vetor de 
probabilidades que direciona a pista para qual o carro seguirá.

Assim, para cada segundo é verificado a existência de eventos para aquela hora e, se 
houver, são executados. No final do programa é impresso na tela o resultado da 
simulação.


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

	Após ser gerado o arquivo executável, digite:
		$ valgrind ./bin/Simulador
