#include "../header/ArvoreDeDecisao.hpp"

ArvoreDeDecisao::ArvoreDeDecisao() : _rodada(0)
{
	_qtdNos = 0;

	try{
		_raiz = new No;
		_deletaRaiz = _raiz;
		_raiz->_jogada = 0;
		_raiz->_minmax = 0;

		for(int i = 0; i < 9; i++){
			_raiz->_subArvore.push_back(No());
			_raiz->_subArvore[i]._minmax = 0;
			_raiz->_subArvore[i]._jogada = i + 1;

			marcaTabuleiro(&_raiz->_subArvore[i]._tabuleiroArv, 'X', i + 1);

			_raiz->_minmax = criaSubArvore(&_raiz->_subArvore[i], 8, 'O');
		}

	}catch(std::exception &e){
		std::cerr << "Excecao: " << e.what() << std::endl;
	}
}

ArvoreDeDecisao::~ArvoreDeDecisao()
{
	delete _deletaRaiz;
}

void ArvoreDeDecisao::setDificuldade(int tmp)
{
	_dificuldade = tmp;
}

int ArvoreDeDecisao::criaSubArvore(No* tmp, int altura, char marcador)
{
	int k = 0;	// Indice para acessar as subArvores
	int R = 0;	// Soma dos minmax das possiveis jogadas a partir do tabuleiro atual
	
	for(int i = 0; i < 9; i++){

		/* Verifica se a posicao esta livre pra jogada. */
		if(verificaJogada(&tmp->_tabuleiroArv, i + 1)){

			_qtdNos++;
			
			tmp->_subArvore.push_back(No());										// Cria a subArvore
			tmp->_subArvore[k]._tabuleiroArv.copiaTabuleiro(&tmp->_tabuleiroArv);	// Copia o tabuleiro anterior
			marcaTabuleiro(&tmp->_subArvore[k]._tabuleiroArv, marcador, i + 1);		// Marca a jogada do tabuleiro atual
			tmp->_subArvore[k]._jogada = i + 1;										// Recebe a jogada (já atualizada)
			tmp->_subArvore[k]._minmax = 0;											// Inicializa o valor de minmax

			if(altura < 6 && tmp->_subArvore[k]._tabuleiroArv.verificaFimDeJogo()){				
				tmp->_subArvore[k]._minmax = verificaVencedor(&tmp->_subArvore[k]._tabuleiroArv) + (altura % 2 == 0 ? 10 : -10) * altura;
				return tmp->_subArvore[k]._minmax;
			}

			/* Realiza a chamada recursiva */	
			if(altura % 2 == 0)
				tmp->_subArvore[k]._minmax = criaSubArvore(&tmp->_subArvore[k], altura - 1, 'X');
			else
				tmp->_subArvore[k]._minmax = criaSubArvore(&tmp->_subArvore[k], altura - 1, 'O');

			R += tmp->_subArvore[k]._minmax;
			k++;
		}
	}

	return R;
}

bool ArvoreDeDecisao::verificaJogada(Tabuleiro* t, int tmp)
{
	if(tmp == 1){
		if(t->getXY(0, 0) == ' ')
			return true;
		return false;
	}
	if(tmp == 2){
		if(t->getXY(0, 1) == ' ')
			return true;
		return false;
	}
	if(tmp == 3){
		if(t->getXY(0, 2) == ' ')
			return true;
		return false;
	}
	if(tmp == 4){
		if(t->getXY(1, 0) == ' ')
			return true;
		return false;
	}
	if(tmp == 5){
		if(t->getXY(1, 1) == ' ')
			return true;
		return false;
	}
	if(tmp == 6){
		if(t->getXY(1, 2) == ' ')
			return true;
		return false;
	}
	if(tmp == 7){
		if(t->getXY(2, 0) == ' ')
			return true;
		return false;
	}
	if(tmp == 8){
		if(t->getXY(2, 1) == ' ')
			return true;
		return false;
	}
	if(tmp == 9){
		if(t->getXY(2, 2) == ' ')
			return true;
		return false;
	}

	return false;
}

/*
		[ 1, 2, 3 ] ---->	[ 0,0	0,1		0,2	]
		[ 4, 5, 6 ] ---->	[ 1,0	1,1		1,2	]
		[ 7, 8, 9 ] ---->	[ 2,0	2,1 	2,2	]
*/
void ArvoreDeDecisao::marcaTabuleiro(Tabuleiro* t, char marcador, int tmp)
{
	if(tmp == 1)
		t->setXY(0, 0, marcador);
	else if(tmp == 2)
		t->setXY(0, 1, marcador);
	else if(tmp == 3)
		t->setXY(0, 2, marcador);
	else if(tmp == 4)
		t->setXY(1, 0, marcador);
	else if(tmp == 5)
		t->setXY(1, 1, marcador);
	else if(tmp == 6)
		t->setXY(1, 2, marcador);
	else if(tmp == 7)
		t->setXY(2, 0, marcador);
	else if(tmp == 8)
		t->setXY(2, 1, marcador);
	else if(tmp == 9)
		t->setXY(2, 2, marcador);
}

void ArvoreDeDecisao::imprimeTabuleiro(Tabuleiro* t)
{
	std::cout << std::endl;
	t->imprimeTabuleiro();
	std::cout << std::endl;
}

int ArvoreDeDecisao::verificaVencedor(Tabuleiro* t)
{
	char tmp = t->verificaCampeao();

	if(tmp == 'O')	return 10;
	if(tmp == 'X')	return -10;
	else 			return 0;
}

int ArvoreDeDecisao::decideJogadaFacil()
{
	// Esta gerando alguns tabuleiros errados!
	if(_raiz->_tabuleiroArv.verificaFimDeJogo()){
		_raiz->_tabuleiroArv.imprimeTabuleiro();
	}

	int tmp = 0;			// Recebe o valor do minmax da subArvore[i]
	int piorJogada = 0;		// Recebe a posicao da pior jogada
	int indice = 0;			// Recebe o indice da subArvore que tem a pior jogada

	for(int i = 0; i < (int)_raiz->_subArvore.size(); i++)
	{
		if(i == 0 || (tmp > _raiz->_subArvore[i]._minmax && _raiz->_subArvore[i]._minmax > -900)){ 
			indice = i;
			tmp = _raiz->_subArvore[i]._minmax;
			piorJogada = _raiz->_subArvore[i]._jogada;
		}
	}

	if(!_raiz->_subArvore[indice]._tabuleiroArv.verificaFimDeJogo())
		_raiz = &_raiz->_subArvore[indice];

	return piorJogada;
}

int ArvoreDeDecisao::decideJogadaIntermediario()
{
	int tmp = 0;					// Recebe o valor do minmax da subArvore[i]
	int jogadaIntermediaria = 0;	// Recebe a posicao da jogada intermediaria
	int indice = 0;					// Recebe o indice da subArvore que tem a jogada intermediaria

	for(int i = 0; i < (int)_raiz->_subArvore.size(); i++)
	{
		if(i == 0 || (tmp < _raiz->_subArvore[i]._minmax)){ 
			indice = i;
			tmp = _raiz->_subArvore[i]._minmax;
			jogadaIntermediaria = _raiz->_subArvore[i]._jogada;
		}
	}

	if(!_raiz->_subArvore[indice]._tabuleiroArv.verificaFimDeJogo())
		_raiz = &_raiz->_subArvore[indice];

	return jogadaIntermediaria;
}

int ArvoreDeDecisao::decideJogadaDificil()
{
	if(_rodada == 2 && _raiz->_tabuleiroArv.getXY(1, 1) == ' '){
		attRaiz(2, 2);
		return 5;
	}

	int tmp = 0;				// Recebe o valor do minmax da subArvore[i]
	int melhorJogada = 0;		// Recebe a posicao da jogada intermediaria
	int indice = 0;				// Recebe o indice da subArvore que tem a jogada intermediaria

	for(int i = 0; i < (int)_raiz->_subArvore.size(); i++)
	{
		/* Se tem a possibilidade de ganhar nessa rodada, já retorna */
		if(verificaVencedor(&_raiz->_subArvore[i]._tabuleiroArv) == 10){
			indice = pesquisaJogada(_raiz->_subArvore[i]._jogada);
			melhorJogada = _raiz->_subArvore[i]._jogada;
			return melhorJogada;
		}else if(i == 0 || (tmp < _raiz->_subArvore[i]._minmax)){ 
			indice = i;
			tmp = _raiz->_subArvore[i]._minmax;
			melhorJogada = _raiz->_subArvore[i]._jogada;
		}
	}

	// Verificacao extra para o nivel dificil, consiste em bloquear a chance do adversário ganhar na proxima rodada
	for(int i = 0; i < (int)_raiz->_subArvore.size(); i++)
		for(int j = 0; j < (int)_raiz->_subArvore[i]._subArvore.size(); j++)
			if(verificaVencedor(&_raiz->_subArvore[i]._subArvore[j]._tabuleiroArv) == -10){
				indice = pesquisaJogada(_raiz->_subArvore[i]._subArvore[j]._jogada);
				melhorJogada = _raiz->_subArvore[i]._subArvore[j]._jogada;
			}

	if(!_raiz->_subArvore[indice]._tabuleiroArv.verificaFimDeJogo())
		_raiz = &_raiz->_subArvore[indice];

	return melhorJogada;
}

void ArvoreDeDecisao::attRodada(int rodada)
{
	_rodada = rodada;
}

void ArvoreDeDecisao::reiniciaRodada()
{
	_rodada = 0;
}

void ArvoreDeDecisao::attRaiz(int x, int y)
{
	if(x == 1){
		if(y == 1)
			_raiz = &_raiz->_subArvore[pesquisaJogada(1)];
		else if(y == 2)
			_raiz = &_raiz->_subArvore[pesquisaJogada(2)];
		else if(y == 3)
			_raiz = &_raiz->_subArvore[pesquisaJogada(3)];
	}

	else if(x == 2){
		if(y == 1)
			_raiz = &_raiz->_subArvore[pesquisaJogada(4)];
		else if(y == 2)
			_raiz = &_raiz->_subArvore[pesquisaJogada(5)];
		else if(y == 3)
			_raiz = &_raiz->_subArvore[pesquisaJogada(6)];
	}
	
	else if(x == 3){
		if(y == 1)
			_raiz = &_raiz->_subArvore[pesquisaJogada(7)];
		else if(y == 2)
			_raiz = &_raiz->_subArvore[pesquisaJogada(8)];
		else if(y == 3)
			_raiz = &_raiz->_subArvore[pesquisaJogada(9)];
	}
}

void ArvoreDeDecisao::reiniciaRaiz()
{
	_raiz = _deletaRaiz;
}

/* Retorna o indice da subArvore que possui a jogada tmp */
int ArvoreDeDecisao::pesquisaJogada(int tmp)
{
	for(int i = 0; i < (int)_raiz->_subArvore.size(); i++)
		if(tmp == _raiz->_subArvore[i]._jogada)
			return i;
	
	return 0;
}