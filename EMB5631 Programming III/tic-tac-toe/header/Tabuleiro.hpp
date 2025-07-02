#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP

#include <iostream>

// ______________________________________________________

class Tabuleiro
{
public:
	Tabuleiro();
	~Tabuleiro();

	void setXY(int x, int y, char marcador);
	char getXY(int x, int y) const;

	void imprimeTabuleiro() const;
	void reiniciaTabuleiro();
	void copiaTabuleiro(Tabuleiro* );

	bool verificaFimDeJogo() const;
	char verificaCampeao() const;
private:
	char _tabuleiro[3][3];

	char verificaLinhas() const;
	char verificaColunas() const;
	char verificaDiagonais() const;
	char verificaEmpate() const;
};

#endif