#include "pista.hpp"

Pista::Pista(int tamanho, int velocidade, bool direcao, bool sentido)
{
    _velocidade = velocidade;
    _tamanho = tamanho;
    _tamanhoOcupado = 0;
    _qtdVeiculos = 0;
    _direcao = direcao;
    _sentido = sentido;
}

Pista::~Pista()
{
    while(!_listaVeiculos.empty())
    {
        Veiculo* car;
        car = _listaVeiculos.first();
        delete car;
        Veiculo::veiculoOut();
        _listaVeiculos.pop_front();
    }
}

int Pista::getQtdVeiculos() const
{
    return _qtdVeiculos;
}

bool Pista::pistaCheia() const
{
    return _tamanho == _tamanhoOcupado;
}

bool Pista::getDirecao() const
{
    return _direcao;
}

bool Pista::getSentido() const
{
    return _sentido;
}

bool Pista::pistaDisponivel() const
{
    if(_listaVeiculos.empty())
        return true;
    if(this->pistaCheia())
        return false;
    if(this->_listaPosVeiculos[ _listaPosVeiculos.size() - 1 ] < 10) // (< x) depende do tamanho do carro!
        return false;
    return true;
}

void Pista::veiculoEntra()
{
    Veiculo* tmp = new Veiculo;
    _tamanhoOcupado = _tamanhoOcupado + 2 + tmp->getComprimento() + 1;

    _listaVeiculos.append(tmp);
    _listaPosVeiculos.push_back(0);         // Como altero esse valor depois?

    _qtdVeiculos += 1;
}

bool Pista::movimentaVeiculos()
{
    bool R = false;

    for(int i = 0; i < (int)_listaPosVeiculos.size(); i++)
    {
        // Primeiro carro da fila
        if(i == 0){
            if(_listaPosVeiculos[i] >= this->_tamanho){ // Chegou no semaforo
                _listaPosVeiculos[i] = this->_tamanho;
                R = true;
            }
            else
                  _listaPosVeiculos[i] += (int)this->_velocidade/3.6;
        }

        // Outros
        else{
            if(_listaPosVeiculos[i - 1] - _listaPosVeiculos[i] >= 10) // (>= x) depende do tamanho do carro!
                  _listaPosVeiculos[i] += (int)this->_velocidade/3.6;
        }
    }

    return R;
}

std::deque<int> Pista::getListaPosVeiculos() const
{
    return _listaPosVeiculos;
}

void Pista::setSaidas(PistaEferente* P1, int p1, PistaEferente* P2, int p2, PistaEferente* P3, int p3)
{
    _saidas[0] = P1; _probSaidas[0] = p1;
    _saidas[1] = P2; _probSaidas[1] = p2;
    _saidas[2] = P3; _probSaidas[2] = p3;
}

// Para saidas pistas sumidouro
void Pista::setSaidas()
{
    _saidas[0] = nullptr; _probSaidas[0] = -1;
    _saidas[1] = nullptr; _probSaidas[1] = -1;
    _saidas[2] = nullptr; _probSaidas[2] = -1;
}

bool Pista::veiculoSai()
{
    if(_listaVeiculos.empty())
        return true;

    Veiculo* car;
    // Veiculo saindo do sistema
    if(_saidas[0] == nullptr)
    {
        car = _listaVeiculos.first();
        delete car;
        _listaVeiculos.pop_front();
        _listaPosVeiculos.pop_front();

        _qtdVeiculos -=1;

        Veiculo::veiculoOut();
        return true;
    }

    // Veiculo trocando de pista
    std::random_device gerador;
    std::uniform_int_distribution<int> time(1, 100);

    int i = time(gerador);
    int j = 0;
    int tmp = 0;

    for(j = 0; j < 3; j++){
        tmp += _probSaidas[j];
        if(i <= tmp)
            break;
    }

    if(_saidas[j]->pistaCheia())
        return false;

    _saidas[j]->veiculoEntra();

    car = _listaVeiculos.first();
    this->_tamanhoOcupado -= (1 + car->getComprimento() + 2);
    delete car;
    _listaVeiculos.pop_front();
    _listaPosVeiculos.pop_front();

    _qtdVeiculos -=1;

    return true;
}

//_________________________________________________


PistaEferente::PistaEferente(int tamanho, int velocidade, bool direcao, bool sentido) :
Pista::Pista(tamanho, velocidade, direcao, sentido)
{

}


//_________________________________________________


PistaAferente::PistaAferente(int tamanho, int velocidade, int limInferior, int limSuperior, bool direcao, bool sentido) :
Pista::Pista(tamanho, velocidade, direcao, sentido)
{
    _limiteInferior = limInferior;
    _limiteSuperior = limSuperior;
}

int PistaAferente::veiculoEntra()
{
    std::random_device gerador;
    std::uniform_int_distribution<int> time(_limiteInferior, _limiteSuperior);

    Veiculo* tmp = new Veiculo;

    _tamanhoOcupado = _tamanhoOcupado + 2 + tmp->getComprimento() + 1;

    _qtdVeiculos += 1;
    _listaVeiculos.append(tmp);
    _listaPosVeiculos.push_back(0);

    return  time(gerador);
}
