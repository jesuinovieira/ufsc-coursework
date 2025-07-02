# Implementação

O programa resume-se em uma simulação de tráfego em dois cruzamentos. Cada pista é representada por uma fila e cada semáforo possui um vetor das pistas que fazer parte dele (dividindo-as em eferentes e aferentes). O relógio do sistema possui um fila de evento, a fila é ordenada por hora de ocorrência dos mesmos. No total, o sistema possui 14 vias e 8 semáforos.

# Funcionamento

No início, o programa irá gerar seis eventos iniciais de chegada de veículo para dar inicio a simulação, sendo que os proximos serão consequência destes. Cada evento é enfileirado ordenadamente na fila de eventos da classe do relógio, a ordenação é baseada na sua hora de execução.
Os próximos eventos serão gerados automaticamente em cada chegada de veículo no sistema e também com a chegada de veículos no semáforo.
 
São eventos: 

1. Chegada de um novo veículo no sistema
2. Troca de pista

A hora de chegada de um novo veículo nas pistas fonte e a pista para qual o veículo vai é calculada a partir de uma distribuição randômica de probabilidades (para mais informações, consultar o relatório). Cada pista fonte possui uma faixa de frequência para a geração de carros e cada um vetor de probabilidades associa a pista para qual o veículo que a percorrer seguirá.

Assim, para cada segundo é verificado a existência de eventos para esse instante, se houver, são executados. Na decorrência do programa é possível visualizar a quantidade de carros que entraram e saíram da simulação.

# Execução

Abra o terminal na pasta que contém o arquivo (.pro) da simulação, os comandos são:

	Gerar o makefile do programa:
		$ qmake

	Compilar o programa:
		$ make

	Executar o programa:
		$ ./SimuladorTransito

	Remover os arquivos objetos:
		$ make clean

Em seguida, para dar início a simulação, clique no botão iniciar (o primeiro na parte superior esquerda da interface). Você também tem a liberdade para pausar e reiniciar a simulação. Ainda, pode acelerar ou diminuir a velocidade em que o tempo se passa, a qual possui um defeito devido ao overhead causado pela criação e destruição das imagens dos carros. Infelizmente, devido a isso, esse recurso ficou pouco eficiente, a intenção era para uma velocidade 100 vezes mais rápida comparada a inicial, fosse possível realizar a simulação das 24horas virtuais em aproximadamente 90~100 segundos do tempo real. 
