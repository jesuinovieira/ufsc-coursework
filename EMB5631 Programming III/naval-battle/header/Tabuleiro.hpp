#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP


//_________________________________________________________________________________________________________________________________

#include <iostream>

//_________________________________________________________________________________________________________________________________


class Tabuleiro
{
public:
	Tabuleiro(char = '~');
	~Tabuleiro();

	// Métodos set
	void setXY(int, int, char marcador);

	// Métodos get
	char getXY(int, int) const;

	// Outros métodos
	void reiniciaTabuleiro(char = '~');

private:	
	char _tabuleiro[15][15];
};


#endif