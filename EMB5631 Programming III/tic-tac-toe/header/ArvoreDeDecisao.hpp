#ifndef ARVOREDEDECISAO_HPP
#define ARVOREDEDECISAO_HPP

#include <iostream>
#include <vector>
#include <exception>
#include "Tabuleiro.hpp"

// ______________________________________________________

class ArvoreDeDecisao
{
private:
	struct No
	{
		std::vector<No> _subArvore;
		Tabuleiro _tabuleiroArv;
		int _jogada;
		int _minmax;
	};

public:
	ArvoreDeDecisao();
	~ArvoreDeDecisao();

	int decideJogadaFacil();
	int decideJogadaIntermediario();
	int decideJogadaDificil();

	void attRodada(int);
	void attRaiz(int, int);
	void setDificuldade(int);
	
	void reiniciaRodada();
	void reiniciaRaiz();

private:
	No* _raiz;
	No* _deletaRaiz;
	int _rodada;
	int _dificuldade;
	int _qtdNos;
	
	int criaSubArvore(No*, int, char);
	int pesquisaJogada(int);
	int verificaVencedor(Tabuleiro*);

	void marcaTabuleiro(Tabuleiro*, char, int);
	void imprimeTabuleiro(Tabuleiro*);
	
	bool verificaJogada(Tabuleiro*, int);
};

#endif