#include <iostream>
#include <cstdlib>
#include "../header/TicTacToe.hpp"
#include "../header/ArvoreDeDecisao.hpp"
#include "../header/Jogador.hpp"

// ______________________________________________________

int main(int argc, char **argv)
{
	if(argc > 3){
		std::cout << "Numero de parametros ao programa invalido! Tente novamente." << std::endl;
		return 0;
	}

	/* Por padrão, o tipo de jogo é Usuário vs Máquina no nível difícil */
	int tipo = 2;
	int dificuldade = 3;

	if(argc == 2)
		tipo = atoi(argv[1]);
	else if(argc == 3){
		tipo = atoi(argv[1]);
		dificuldade = atoi(argv[2]);
	}

	/* Verifica se os parametros que foram passados ao programa são válidos */
	if(tipo < 1 || tipo > 2 || dificuldade < 1 || dificuldade > 3){
		std::cout << "Parametros ao programa invalido! Tente novamente." << std::endl;
		return 0;
	}

	try{
		if(tipo == 1){
			TicTacToe<Jogador> jogo;
			jogo.iniciaJogo();
		}else{
			TicTacToe<ArvoreDeDecisao> jogo(dificuldade);
			jogo.iniciaJogo();
		}
	}catch(std::logic_error &e){
		std::cerr << e.what() << std::endl;
	}

	return 0;
}