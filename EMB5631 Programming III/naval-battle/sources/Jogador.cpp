#include "../header/Jogador.hpp"

//_________________________________________________________________________________________________________________________________

Jogador::Jogador(int tiros) :	 	_vitorias(0),
					 				_tiros(tiros),
									_F(3),			// Fragata		
									_B(3),			// Balizador
									_CO(2),			// Contratorpedeiro
									_CR(2),			// Cruzador
									_P(1)			// PortaAvioes
{
	//
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

Jogador::~Jogador()
{
	//
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

void Jogador::setNome(std::string nome)
{
	_nome = nome;
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

std::string Jogador::getNome() const
{
	return _nome;
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

int Jogador::getVitorias() const
{
	return _vitorias;
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

int Jogador::getTiros() const
{
	return _tiros;
}
//_________________________________________________________________________________________________________________________________

//_________________________________________________________________________________________________________________________________

int Jogador::getVidaNavios() const
{
	int tmp = 0;

	for(int i = 0; i < (int)_F.size(); i++)
		tmp += _F[i].getVida();

	for(int i = 0; i < (int)_B.size(); i++)
		tmp += _B[i].getVida();

	for(int i = 0; i < (int)_CO.size(); i++)
		tmp += _CO[i].getVida();

	for(int i = 0; i < (int)_CR.size(); i++)
		tmp += _CR[i].getVida();

	for(int i = 0; i < (int)_P.size(); i++)
		tmp += _P[i].getVida();

	return tmp;
}

//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

bool Jogador::perdeuJogo() const
{
	// Verifica fragatas
	for(int i = 0; i < (int)_F.size() ; i++)
		if( _F[i].getVida() != 0 )
			return false;

	// Verifica Balizadores
	for(int i = 0; i < (int)_B.size() ; i++)
		if( _B[i].getVida() != 0 )
			return false;

	// Verifica Contratorpedeiros
	for(int i = 0; i < (int)_CO.size() ; i++)
		if( _CO[i].getVida() != 0 )
			return false;

	// Verifica Cruzador
	for(int i = 0; i < (int)_CR.size() ; i++)
		if( _CR[i].getVida() != 0 )
			return false;

	// Verifica PortaAvioes
	for(int i = 0; i < (int)_P.size() ; i++)
		if( _P[i].getVida() != 0 )
			return false;

	return true;
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

const Tabuleiro* Jogador::getTabuleiro() const
{
	return &_tabuleiro;
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

void Jogador::incrementaVitorias()
{
	_vitorias += 1;
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

bool Jogador::verificaJogada(int x, int y, int qtd, char d)
{
	/* 
		(x, y) é o início da verificação se a jogada sera possivel.
		Qtd é a quantidade de casas que será verificada na direção d.
	*/
	if(d == 'H')	return verificaJogadaHorizontal(x, y, qtd);
	else			return verificaJogadaVertical(x, y, qtd);
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

bool Jogador::verificaJogadaHorizontal(int x, int y, int qtd)
{
	if(y + qtd > 14)	return false;

	for(int i = 0; i < qtd; i++)
		if( _tabuleiro.getXY(x, y + i) != '~' )
			return false;

	return true;
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

bool Jogador::verificaJogadaVertical(int x, int y, int qtd)
{
	if(x + qtd > 14)	return false;

	for(int i = 0; i < qtd; i++)
		if( _tabuleiro.getXY(x + i, y) != '~' )
			return false;

	return true;
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

void Jogador::posicionaNavio(int x, int y, int qtd, char d, char marcador)
{
	if(d == 'H')	posicionaNavioHorizontal(x, y, qtd, marcador);
	else			posicionaNavioVertical(x, y, qtd, marcador);
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

void Jogador::posicionaNavioHorizontal(int x, int y, int qtd, char marcador)
{
	for(int i = 0; i < qtd; i++)	_tabuleiro.setXY(x, y + i, marcador);
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

void Jogador::posicionaNavioVertical(int x, int y, int qtd, char marcador)
{
	for(int i = 0; i < qtd; i++)	_tabuleiro.setXY(x + i, y, marcador);
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

void Jogador::setDadosNavio(int x, int y, char d, char tipo, int i)
{
	switch(tipo)
	{
		case 'A':
			setDadosFragata(x, y, d, i);
			break;
		case 'B':
			setDadosBalizador(x, y, d, i);
			break;
		case 'C':
			setDadosContratorpedeiro(x, y, d, i);
			break;
		case 'D':
			setDadosCruzador(x, y, d, i);
			break;
		case 'E':
			setDadosPortaAvioes(x, y, d, i);
			break;
	}
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

void Jogador::setDadosFragata(int x, int y, char d, int i)
{
	_F[i].setTipo("Fragata");
	_F[i].setLinha(x);
	_F[i].setColuna(y);
	_F[i].setDirecao(d);
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

void Jogador::setDadosBalizador(int x, int y, char d, int i)
{
	_B[i].setTipo("Balizador");
	_B[i].setLinha(x);
	_B[i].setColuna(y);
	_B[i].setDirecao(d);
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

void Jogador::setDadosContratorpedeiro(int x, int y, char d, int i)
{
	_CO[i].setTipo("Contratorpedeiro");
	_CO[i].setLinha(x);
	_CO[i].setColuna(y);
	_CO[i].setDirecao(d);
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

void Jogador::setDadosCruzador(int x, int y, char d, int i)
{
	_CR[i].setTipo("Cruzador");
	_CR[i].setLinha(x);
	_CR[i].setColuna(y);
	_CR[i].setDirecao(d);
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

void Jogador::setDadosPortaAvioes(int x, int y, char d, int i)
{
	_P[i].setTipo("Porta-avioes");
	_P[i].setLinha(x);
	_P[i].setColuna(y);
	_P[i].setDirecao(d);
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

void Jogador::posicionaNaviosAleatoriamente()
{
    std::random_device gerador;

    std::uniform_int_distribution<std::size_t> T(1, 5);		// Tipo do navio

    std::uniform_int_distribution<std::size_t> x(0, 14); 	// Coordenada x
	std::uniform_int_distribution<std::size_t> y(0, 14);	// Coordenada y
    std::uniform_int_distribution<std::size_t> d(0, 1);		// dRand: 1 = Vertical, 0 = Horizontal

	int F = 3, B = 3, CO = 2, CR = 2, P = 1;
	int xRand = 0, yRand = 0;
	char dRand = '\0';

	while(F != 0 || B != 0 || CO != 0 || CR != 0 || P != 0)
	{
		xRand = x(gerador);
		yRand = y(gerador);
		dRand = d(gerador) == 0 ? 'H' : 'V';

		switch(T(gerador))
		{
			case 1:
				if(F != 0 && verificaJogada(xRand, yRand, 2, dRand))
				{
					posicionaNavio(xRand, yRand, 2, dRand, 'A');
					setDadosNavio(xRand, yRand, dRand, 'A', 3 - F);
					F -= 1;
				}
				break;

			case 2:
				if(B != 0 && verificaJogada(xRand, yRand, 2, dRand))
				{
					posicionaNavio(xRand, yRand, 2, dRand, 'B');
					setDadosNavio(xRand, yRand, dRand, 'B', 3 - B);
					B -= 1;
				}
				break;

			case 3:
				if(CO != 0 && verificaJogada(xRand, yRand, 3, dRand))
				{
					posicionaNavio(xRand, yRand, 3, dRand, 'C');
					setDadosNavio(xRand, yRand, dRand, 'C', 2 - CO);
					CO -= 1;
				}
				break;

			case 4:
				if(CR != 0 && verificaJogada(xRand, yRand, 3, dRand))
				{
					posicionaNavio(xRand, yRand, 3, dRand, 'D');
					setDadosNavio(xRand, yRand, dRand, 'D', 2 - CR);
					CR -= 1;
				}
				break;

			case 5:
				if(P != 0 && verificaJogada(xRand, yRand, 4, dRand))
				{
					posicionaNavio(xRand, yRand, 4, dRand, 'E');
					setDadosNavio(xRand, yRand, dRand, 'E', 1 - P);
					P -= 1;
				}
				break;

			default:
				break;
		}
	}
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

bool Jogador::tiroInvalido(int x, int y)
{
	/* 'x' -> Lugares aonde foi atirado e acertou um navio 	*/
	/* ' ' -> Lugares aonde foi atirado e acertou a agua 	*/
	if( _tabuleiro.getXY(x, y) == 'X' || _tabuleiro.getXY(x, y) == ' ' )	return true;
																			return false;
}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

char Jogador::atirarXY(int x, int y)
{
	/*
		D -> Destruiu um navio
		A -> Acertou um navio
		E -> Errou
	*/
	
	int xx = 0;		// Inicio do navio
	int yy = 0;		// Inicio do navio
	char dd = '\0';	// Direcao do navio

	_tiros -= 1;

	if( _tabuleiro.getXY(x, y) == '~' ){
		_tabuleiro.setXY(x, y, ' ');
		return 'E';
	}

	/* Verifica se os barcos foram atingidos considerando o intervalo em que foram posicionados no tabuleiro */

	// Verifica fragatas
	for(int i = 0; i < (int)_F.size() ; i++){

		if( _F[i].getVida() != 0 )
		{
			xx = _F[i].getLinha();
			yy = _F[i].getColuna();
			dd = _F[i].getDirecao();

			if(dd == 'H'){
				if(x == xx && ( yy <= y && y < yy + 2))
				{
					_tabuleiro.setXY(x, y, 'X');
					_F[i].decrementaVida();
					if(_F[i].getVida() == 0)		throw _F[i].getTipo();
					else							return 'A';
				}
			}else{
				if(yy == y && (xx <= x && x < xx + 2))
				{
					_tabuleiro.setXY(x, y, 'X');
					_F[i].decrementaVida();
					if(_F[i].getVida() == 0)		throw _F[i].getTipo();
					else							return 'A';
				}	
			}
		}
	}

	// Verifica Balizadores
	for(int i = 0; i < (int)_B.size() ; i++){

		if( _B[i].getVida() != 0 )
		{
			xx = _B[i].getLinha();
			yy = _B[i].getColuna();
			dd = _B[i].getDirecao();

			if(dd == 'H'){
				if(x == xx && ( yy <= y && y < yy + 2))
				{
					_tabuleiro.setXY(x, y, 'X');
					_B[i].decrementaVida();
					if(_B[i].getVida() == 0)		throw _B[i].getTipo();
					else							return 'A';
				}
			}else{
				if(yy == y && (xx <= x && x < xx + 2))
				{
					_tabuleiro.setXY(x, y, 'X');
					_B[i].decrementaVida();
					if(_B[i].getVida() == 0)		throw _B[i].getTipo();
					else							return 'A';
				}	
			}
		}
	}

	// Verifica Contratorpedeiros
	for(int i = 0; i < (int)_CO.size() ; i++){

		if( _CO[i].getVida() != 0 )
		{
			xx = _CO[i].getLinha();
			yy = _CO[i].getColuna();
			dd = _CO[i].getDirecao();

			if(dd == 'H'){
				if(x == xx && ( yy <= y && y < yy + 3))
				{
					_tabuleiro.setXY(x, y, 'X');
					_CO[i].decrementaVida();
					if(_CO[i].getVida() == 0)		throw _CO[i].getTipo();
					else							return 'A';
				}
			}else{
				if(yy == y && (xx <= x && x < xx + 3))
				{
					_tabuleiro.setXY(x, y, 'X');
					_CO[i].decrementaVida();
					if(_CO[i].getVida() == 0)		throw _CO[i].getTipo();
					else							return 'A';
				}	
			}
		}
	}

	// Verifica Cruzador
	for(int i = 0; i < (int)_CR.size() ; i++){

		if( _CR[i].getVida() != 0 )
		{
			xx = _CR[i].getLinha();
			yy = _CR[i].getColuna();
			dd = _CR[i].getDirecao();

			if(dd == 'H'){
				if(x == xx && ( yy <= y && y < yy + 3))
				{
					_tabuleiro.setXY(x, y, 'X');
					_CR[i].decrementaVida();
					if(_CR[i].getVida() == 0)		throw _CR[i].getTipo();
					else							return 'A';
				}
			}else{
				if(yy == y && (xx <= x && x < xx + 3))
				{
					_tabuleiro.setXY(x, y, 'X');
					_CR[i].decrementaVida();
					if(_CR[i].getVida() == 0)		throw _CR[i].getTipo();
					else							return 'A';
				}	
			}
		}
	}

	// Verifica PortaAvioes
	for(int i = 0; i < (int)_P.size() ; i++){

		if( _P[i].getVida() != 0 )
		{
			xx = _P[i].getLinha();
			yy = _P[i].getColuna();
			dd = _P[i].getDirecao();

			if(dd == 'H'){
				if(x == xx && ( yy <= y && y < yy + 4))
				{
					_tabuleiro.setXY(x, y, 'X');
					_P[i].decrementaVida();
					if(_P[i].getVida() == 0)		throw _P[i].getTipo();
					else							return 'A';
				}
			}else{
				if(yy == y && (xx <= x && x < xx + 4))
				{
					_tabuleiro.setXY(x, y, 'X');
					_P[i].decrementaVida();
					if(_P[i].getVida() == 0)		throw _P[i].getTipo();
					else							return 'A';
				}	
			}
		}
	}

	return 'C';		// Bad return
}
//_________________________________________________________________________________________________________________________________