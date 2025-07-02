#ifndef PISTA_HPP
#define PISTA_HPP

#include <QLinkedList>
#include <random>
#include <deque>

#include "veiculo.hpp"
#include "semaforo.hpp"

class Veiculo;
class Semaforo;
class PistaEferente;

class Pista
{
public:
    Pista(int, int, bool, bool);
    ~Pista();

    std::deque<int> getListaPosVeiculos() const;
    bool pistaCheia() const;
    bool pistaDisponivel() const;
    bool getDirecao() const;
    bool getSentido() const;
    int getQtdVeiculos() const;

    bool movimentaVeiculos();
    bool veiculoSai();
    void veiculoEntra();
    void setSaidas(PistaEferente*, int, PistaEferente*, int, PistaEferente*, int);
    void setSaidas();

protected:
    int _tamanho;             // Tamanho da pista
    int _tamanhoOcupado;      // Tamanho da pista que está ocupado
    int _velocidade;          // Velocidade da pista
    int _qtdVeiculos;         // Quantidade de veiculos na pista

    bool _direcao;      // True (Vertical)     e False (Horizontal)
    bool _sentido;      // True (Para direita ou para cima)  e False (Para esquerda ou para baixo)

    QLinkedList<Veiculo*> _listaVeiculos;
    std::deque<int> _listaPosVeiculos;

    PistaEferente* _saidas[3];  // Responsabilidade do usuario deletar
    int _probSaidas[3];
};


//_________________________________________________


class PistaEferente : public Pista
{
public:
    PistaEferente(int, int, bool, bool);
    virtual ~PistaEferente()
    {

    }
};


//_________________________________________________


class PistaAferente : public Pista
{
public:
    PistaAferente(int, int, int, int, bool, bool);

    virtual ~PistaAferente()
    {

    }

    int veiculoEntra();

private:
    int _limiteInferior;    // Limite superior do intervalo de geração de veículos
    int _limiteSuperior;    // Limite inferior do intervalo de geração de veículos
};

#endif // PISTA_HPP
