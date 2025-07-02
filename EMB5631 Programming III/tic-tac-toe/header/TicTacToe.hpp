#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "Tabuleiro.hpp"
#include "Jogador.hpp"
#include "ArvoreDeDecisao.hpp"



// ___________________________________________________________________________________________



template<typename T>
class TicTacToe
{
public:
	TicTacToe()
	{
		throw std::logic_error("Nao foi possivel iniciar o jogo!");
	}
	
	~TicTacToe(){}
};


// ___________________________________________________________________________________________



template<>
class TicTacToe<Jogador>
{
public:
	TicTacToe() : _partida(0), _rodada(0), _campeao(' ')
	{
		// Construtor
	}

	~TicTacToe()
	{
		// Destrutor
	}

	void iniciaJogo()
	{
		if(_partida == 0)
			setJogadores();
		setCampeao(' ');

		// Enquanto o jogo nao termina os jogadores realizam suas jogadas
		do{

			_rodada++; std::cout << std::endl;
			_tabuleiro.imprimeTabuleiro(); std::cout << std::endl;
			
			if( _rodada % 2 == 1 )
				realizarJogada( _jogadorUM.getMarcador() );
			else
				realizarJogada( _jogadorDOIS.getMarcador() );

		}while(!_tabuleiro.verificaFimDeJogo());

		setCampeao( _tabuleiro.verificaCampeao() );
		imprimeResultado();
		reiniciaJogo();
	}

	void reiniciaJogo()
	{
		_rodada = 0;
		_tabuleiro.reiniciaTabuleiro();
		jogarNovamente();
	}

	bool verificaJogada(int x, int y) const
	{
		if(x < 0 || y < 0 || x > 2 || y > 2) 		return false;
		if( _tabuleiro.getXY(x, y) != ' ' ) 		return false;

		return true;
	}

	void realizarJogada(char marcador)
	{
		std::cout << "Linha: "; 	std::string x; std::getline(std::cin, x);
		std::cout << "Coluna: "; 	std::string y; std::getline(std::cin, y);

		while(x.length() > 1 || y.length() > 1 || !verificaJogada(x[0] - '0' - 1, y[0] - '0' - 1))
		{
			std::cerr << "Voce nao pode marcar o tabuleiro nessa coordenada." << std::endl << std::endl;

			std::cout << "Linha: "; std::getline(std::cin, x);
			std::cout << "Coluna: "; std::getline(std::cin, y);
		}

		_tabuleiro.setXY(x[0] - '0' - 1, y[0] - '0' - 1, marcador);	
	}

private:
	Tabuleiro _tabuleiro;
	Jogador _jogadorUM;
	Jogador _jogadorDOIS;

	int _partida;
	int _rodada;
	char _campeao;

	void setCampeao(char tmp)
	{
		_campeao = tmp;
	}

	void setJogadores()
	{
		_jogadorUM.setMarcador('X');
		_jogadorDOIS.setMarcador('O');

		std::string tmp;
		std::cout << "Insira o nome do jogador 01: "; std::getline(std::cin, tmp); _jogadorUM.setNome(tmp);
		std::cout << "Insira o nome do jogador 02: "; std::getline(std::cin, tmp); _jogadorDOIS.setNome(tmp);
	}

	void imprimeResultado()
	{
		std::cout << std::endl << std::endl; _tabuleiro.imprimeTabuleiro(); std::cout << std::endl << std::endl;

		if( _campeao == '-' ){
			std::cout << "Deu velha! O jogo empatou." << std::endl;
		}else if( _campeao == 'X' ){
			_jogadorUM.incrementaVitorias();
			std::cout << _jogadorUM.getNome() << " venceu! Parabens." << std::endl;
		}else{
			_jogadorDOIS.incrementaVitorias();
			std::cout << _jogadorDOIS.getNome() << " venceu! Parabens." << std::endl;
		}

		_partida += 1;
		imprimePlacar();
	}

	void imprimePlacar() const
	{
		std::cout << _jogadorUM.getNome() << " " << _jogadorUM.getVitorias();
		std::cout << " x ";
		std::cout << _jogadorDOIS.getVitorias() << " " << _jogadorDOIS.getNome();
		std::cout << std::endl << std::endl;
	}

	void jogarNovamente()
	{
		std::string tmp;
		std::cout << "Jogar novamente? (S/N) ";
		std::getline(std::cin, tmp);
		
		if(tmp == "S" || tmp == "s")
			iniciaJogo();
		else if(tmp == "N" || tmp == "n")
			return;
		else
			jogarNovamente();
	}
};



// ___________________________________________________________________________________________



template<>
class TicTacToe<ArvoreDeDecisao>
{
public:
	TicTacToe(int nivel = 3) :	_partida(0), _dificuldade(nivel), _rodada(0)
	{
		// Construtor
	}

	~TicTacToe()
	{
		// Destrutor
	}

	void iniciaJogo()
	{
		if(_partida == 0)
			setJogadores();
		setCampeao(' ');

		// Enquanto o jogo nao termina os jogadores realizam suas jogadas
		do{
			_rodada++; std::cout << std::endl;
			_arvore.attRodada(_rodada);
			
			if(_rodada % 2 == 1){
				_tabuleiro.imprimeTabuleiro(); std::cout << std::endl;
				realizarJogada( _jogadorUM.getMarcador() );
			}else
				realizarJogada( _jogadorDOIS.getMarcador() );

		}while(!_tabuleiro.verificaFimDeJogo());

		setCampeao( _tabuleiro.verificaCampeao() );
		imprimeResultado();
		reiniciaJogo();
	}

	void reiniciaJogo()
	{
		_rodada = 0;
		_tabuleiro.reiniciaTabuleiro();

		_arvore.attRodada(_rodada);
		_arvore.reiniciaRaiz();

		jogarNovamente();
	}

	bool verificaJogada(int x, int y) const
	{
		if(x < 0 || y < 0 || x > 2 || y > 2) 		return false;
		if( _tabuleiro.getXY(x, y) != ' ' ) 		return false;

		return true;
	}

	void realizarJogada(char marcador)
	{
		if(_rodada % 2 == 0){

			int tmp;
			if(_dificuldade == 1)		tmp = _arvore.decideJogadaFacil();
			else if(_dificuldade == 2)	tmp = _arvore.decideJogadaIntermediario();
			else						tmp = _arvore.decideJogadaDificil();
			
			if(tmp == 1)
				_tabuleiro.setXY(0, 0, marcador);
			else if(tmp == 2)
				_tabuleiro.setXY(0, 1, marcador);
			else if(tmp == 3)
				_tabuleiro.setXY(0, 2, marcador);
			else if(tmp == 4)
				_tabuleiro.setXY(1, 0, marcador);
			else if(tmp == 5)
				_tabuleiro.setXY(1, 1, marcador);
			else if(tmp == 6)
				_tabuleiro.setXY(1, 2, marcador);
			else if(tmp == 7)
				_tabuleiro.setXY(2, 0, marcador);
			else if(tmp == 8)
				_tabuleiro.setXY(2, 1, marcador);
			else if(tmp == 9)
				_tabuleiro.setXY(2, 2, marcador);
			return;
		}

		std::cout << "Linha: ";
		std::string x; std::getline(std::cin, x);
		
		std::cout << "Coluna: ";
		std::string y; std::getline(std::cin, y);

		while(x.length() > 1 || y.length() > 1 || !verificaJogada(x[0] - '0' - 1, y[0] - '0' - 1))
		{
			std::cerr << "Voce nao pode marcar o tabuleiro nessa coordenada." << std::endl << std::endl;

			std::cout << "Linha: "; std::getline(std::cin, x);
			std::cout << "Coluna: "; std::getline(std::cin, y);
		}

		_tabuleiro.setXY(x[0] - '0' - 1, y[0] - '0' - 1, marcador);
		
		// Se o jogo ainda não acabou, atualizamos a raiz
		if(!_tabuleiro.verificaFimDeJogo())
			_arvore.attRaiz(x[0] - '0', y[0] - '0');
	}

private:
	Tabuleiro _tabuleiro;
	Jogador _jogadorUM;
	Jogador _jogadorDOIS;
	ArvoreDeDecisao _arvore;

	int _partida;
	int _dificuldade;
	int _rodada;
	char _campeao;

	void setCampeao(char tmp)
	{
		_campeao = tmp;
	}

	void setJogadores()
	{
		_jogadorUM.setMarcador('X');
		_jogadorDOIS.setMarcador('O');

		std::string tmp;
		std::cout << "Insira o seu nome: "; std::getline(std::cin, tmp); _jogadorUM.setNome(tmp);

		_jogadorDOIS.setNome("Maquina");
	}

	void imprimeResultado()
	{
		std::cout << std::endl << std::endl; _tabuleiro.imprimeTabuleiro(); std::cout << std::endl << std::endl;

		if( _campeao == '-' ){
			std::cout << "Deu velha! O jogo empatou." << std::endl;
		}else if( _campeao == 'X' ){
			_jogadorUM.incrementaVitorias();
			std::cout << _jogadorUM.getNome() << " venceu! Parabens." << std::endl;
		}else{
			_jogadorDOIS.incrementaVitorias();
			std::cout << _jogadorDOIS.getNome() << " venceu! Tente novamente." << std::endl;
		}

		_partida += 1;
		imprimePlacar();
	}

	void imprimePlacar() const
	{
		std::cout << _jogadorUM.getNome() << " " << _jogadorUM.getVitorias();
		std::cout << " x ";
		std::cout << _jogadorDOIS.getVitorias() << " " << _jogadorDOIS.getNome();
		std::cout << std::endl << std::endl;
	}

	void jogarNovamente()
	{
		std::string tmp;
		std::cout << "Jogar novamente? (S/N) ";
		std::getline(std::cin, tmp);
		
		if(tmp == "S" || tmp == "s")
			iniciaJogo();
		else if(tmp == "N" || tmp == "n")
			return;
		else
			jogarNovamente();
	}
};

#endif