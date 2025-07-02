#include "veiculo.hpp"

unsigned int Veiculo::_qtdVeiculosIn = 0;
unsigned int Veiculo::_qtdVeiculosOut = 0;

Veiculo::Veiculo(int comprimento)
{
    _comprimento = comprimento;
    _qtdVeiculosIn++;
}

Veiculo::~Veiculo()
{

}

void Veiculo::veiculoOut()
{
    _qtdVeiculosOut++;
}

void Veiculo::zerar()
{
    _qtdVeiculosOut = 0;
    _qtdVeiculosIn = 0;
}

Veiculo::Veiculo(const Veiculo& vTmp)
{
    this->_comprimento = vTmp.getComprimento();
}

int Veiculo::getComprimento() const
{
    return _comprimento;
}

unsigned int Veiculo::getQtdVeiculosIn()
{
    return _qtdVeiculosIn;
}

unsigned int Veiculo::getQtdVeiculosOut()
{
    return _qtdVeiculosOut;
}
