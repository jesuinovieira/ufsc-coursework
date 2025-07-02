#ifndef VEICULO_HPP
#define VEICULO_HPP

#include "pista.hpp"

class Pista;

class Veiculo
{
public:
    Veiculo(int = 3);
    Veiculo(const Veiculo& vTmp);
    ~Veiculo();

    int getComprimento() const;
    static unsigned int getQtdVeiculosIn();
    static unsigned int getQtdVeiculosOut();
    static void veiculoOut();
    static void zerar();

private:
    static unsigned int _qtdVeiculosIn;         // Contagem exclusiva de veículos que entraram no simulador
    static unsigned int _qtdVeiculosOut;        // Contagem exclusiva de veículos que sairam do simulador

    int _comprimento;                           // Comprimento do veiculo
};

#endif // VEICULO_HPP
