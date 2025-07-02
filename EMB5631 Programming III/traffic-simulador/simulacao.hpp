#ifndef SIMULACAO_HPP
#define SIMULACAO_HPP

#include "relogio.hpp"
#include "pista.hpp"
#include "semaforo.hpp"
#include "evento.hpp"
#include "veiculo.hpp"

class Pista;
class PistaAferente;
class PistaEferente;
class Semaforo;
class Relogio;
class Evento;
class Veiculo;

class Simulacao
{
public:
    Simulacao(int = 86400);
    ~Simulacao();

    struct DadosVeiculo
    {
        int x;
        int y;
        bool direcao;
        bool sentido;
    };

    typedef struct DadosVeiculo DadosVeiculo;

    void attSemaforos();
    void attTimer();
    void execEventos();
    void movimentaVeiculos();
    int getTempoAtual() const;
    int getTempoSimulacao() const;
    int getSemaforoDir() const;
    int getQtdVeiculosIn() const;
    int getQtdVeiculosOut() const;

    std::vector<DadosVeiculo> getListaPosVeiculos();

private:
    static int _tempoSimulacao;
    int _semaforoDir;

    Relogio* _relogio;

    PistaAferente* _pistasFonte[6];
    PistaEferente* _pistasReceptoras[8];

    Semaforo* _semaforos[8];

    std::vector<DadosVeiculo> carros;

    bool trocaPista(Evento*);
    bool veiculoSistema(int);
};

#endif // SIMULACAO_HPP
