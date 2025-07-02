#include "../header/Tabuleiro.hpp"

Tabuleiro::Tabuleiro()
{
	for(int x = 0; x < 3; x++)
		for(int y = 0; y < 3; y++)
			_tabuleiro[x][y] = ' ';
}

Tabuleiro::~Tabuleiro()
{
	//
}

void Tabuleiro::imprimeTabuleiro() const
{
	std::cout << "       " << "1" << "   " << "2" << "   " << "3" << std::endl;

	for(int x = 0; x < 3; x++){
		
		std::cout << "    " << x + 1 << "  ";
		for(int y = 0; y < 3; y++){
			if(y != 2)
				std::cout << _tabuleiro[x][y] << " | ";
			else
				std::cout << _tabuleiro[x][y] << std::endl;
		}

		if(x != 2)	std::cout << "      " << "---|---|---" << std::endl;
	}
}

/* Retorna o conteúdo na coordenada (x, y) do tabuleiro */
char Tabuleiro::getXY(int x, int y) const
{
	return _tabuleiro[x][y];
}

/* Marca uma celula do tabuleiro com o marcador recebido por parâmetro */
void Tabuleiro::setXY(int x, int y, char marcador)
{
	_tabuleiro[x][y] = marcador;
}

void Tabuleiro::copiaTabuleiro(Tabuleiro* t)
{
	/* Fazer um construtor cópia */
	for(int x = 0; x < 3; x++)
		for(int y = 0; y < 3; y++)
			this->setXY(x, y, t->getXY(x, y));
}

void Tabuleiro::reiniciaTabuleiro()
{
	for(int x = 0; x < 3; x++)
		for(int y = 0; y < 3; y++)
			setXY(x, y, ' ');
}

bool Tabuleiro::verificaFimDeJogo() const
{
	if(verificaCampeao() == ' ') 
		return false;
	return true;
}

char Tabuleiro::verificaCampeao() const
{
	char F1 = verificaColunas();
	char F2 = verificaLinhas();
	char F3 = verificaDiagonais();
	char F4 = verificaEmpate();

	if(F1 == ' ' && F1 == F2 && F2 == F3 && F3 == F4)
		return ' ';
	if(F1 != ' ')
		return F1;
	if(F2 != ' ')
		return F2;
	if(F3 != ' ')
		return F3;
	else
		return F4;
}

char Tabuleiro::verificaLinhas() const
{
	for(int x = 0; x < 3; x++)
		if(getXY(x, 0) != ' ')
			if(getXY(x, 0) == getXY(x, 1) && getXY(x, 1) == getXY(x, 2))		
				return getXY(x, 0);
	return ' ';
}

char Tabuleiro::verificaColunas() const
{
	for(int y = 0; y < 3; y++)
		if(getXY(0, y) != ' ')
			if(getXY(0, y) == getXY(1, y) && getXY(1, y) == getXY(2, y))
				return getXY(0, y);
	return ' ';
}

char Tabuleiro::verificaDiagonais() const
{
	if(getXY(1, 1) == ' ')	return ' ';
	if(getXY(0, 0) == getXY(1, 1) && getXY(1, 1) == getXY(2, 2))	return getXY(0, 0);
	if(getXY(0, 2) == getXY(1, 1) && getXY(1, 1) == getXY(2, 0))	return getXY(1, 1);
	return ' ';
}

char Tabuleiro::verificaEmpate() const
{
	for(int x = 0; x < 3; x++)
		for(int y = 0; y < 3; y++)
			if(getXY(x, y) == ' ')
				return ' ';
	return '-';
}