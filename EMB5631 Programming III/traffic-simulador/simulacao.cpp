#include "simulacao.hpp"
#include <iostream>

int Simulacao::_tempoSimulacao = 0;

Simulacao::Simulacao(int tTmp)
{
    //____________________________________________________________________________________
    /* Pistas fontes */
    _pistasFonte[0] = new PistaAferente(2000, 80, 8, 12, false, true);          // O1Leste
    _pistasFonte[1] = new PistaAferente(500, 60, 23, 37, true, true);           // S1Norte
    _pistasFonte[2] = new PistaAferente(500, 40, 45, 75, true, true);           // S2Norte
    _pistasFonte[3] = new PistaAferente(400, 30, 8, 12, false, false);          // L1Oeste
    _pistasFonte[4] = new PistaAferente(500, 40, 15, 25, true, false);          // N2Sul
    _pistasFonte[5] = new PistaAferente(500, 60, 15, 25, true, false);          // N1Sul

    /* Pistas sumidouros */
    _pistasReceptoras[0] = new PistaEferente(2000, 80, false, false);           // O1Oeste
    _pistasReceptoras[1] = new PistaEferente(500, 60, true, false);             // S1Sul
    _pistasReceptoras[2] = new PistaEferente(500, 40, true, false);             // S2Sul
    _pistasReceptoras[3] = new PistaEferente(400, 30, false, true);             // L1Leste
    _pistasReceptoras[4] = new PistaEferente(500, 40, true, true);              // N2Norte
    _pistasReceptoras[5] = new PistaEferente(500, 60, true, true);              // N1Norte

    /* Pistas centrais */
    _pistasReceptoras[6] = new PistaEferente(300, 60, false, false);            // C1Oeste
    _pistasReceptoras[7] = new PistaEferente(300, 60, false, true);             // C1Leste

    //____________________________________________________________________________________
    /* Setando as pistas de saidas e suas probabilidades */
            // Fontes
    _pistasFonte[0]->setSaidas(_pistasReceptoras[7], 80, _pistasReceptoras[1], 10, _pistasReceptoras[5], 10);
    _pistasFonte[1]->setSaidas(_pistasReceptoras[7], 80, _pistasReceptoras[5], 10, _pistasReceptoras[0], 10);
    _pistasFonte[2]->setSaidas(_pistasReceptoras[3], 40, _pistasReceptoras[2], 30, _pistasReceptoras[6], 30);
    _pistasFonte[3]->setSaidas(_pistasReceptoras[4], 40, _pistasReceptoras[7], 30, _pistasReceptoras[2], 30);
    _pistasFonte[4]->setSaidas(_pistasReceptoras[3], 40, _pistasReceptoras[2], 30, _pistasReceptoras[6], 30);
    _pistasFonte[5]->setSaidas(_pistasReceptoras[7], 80, _pistasReceptoras[1], 10, _pistasReceptoras[0], 10);

            // Sumidouros (recebem nullptr e -1)
    _pistasReceptoras[0]->setSaidas();
    _pistasReceptoras[1]->setSaidas();
    _pistasReceptoras[2]->setSaidas();
    _pistasReceptoras[3]->setSaidas();
    _pistasReceptoras[4]->setSaidas();
    _pistasReceptoras[5]->setSaidas();

            // Centrais
    _pistasReceptoras[6]->setSaidas(_pistasReceptoras[0], 40, _pistasReceptoras[5], 30, _pistasReceptoras[1], 30);
    _pistasReceptoras[7]->setSaidas(_pistasReceptoras[3], 40, _pistasReceptoras[4], 30, _pistasReceptoras[2], 30);

    //____________________________________________________________________________________
    /* Semaforos */
    _semaforos[0] = new Semaforo;     // S_O1Leste
    _semaforos[1] = new Semaforo;     // S_S1Norte
    _semaforos[2] = new Semaforo;     // S_S2Norte
    _semaforos[3] = new Semaforo;     // S_L1Oeste
    _semaforos[4] = new Semaforo;     // S_N2Sul
    _semaforos[5] = new Semaforo;     // S_N1Sul
    _semaforos[6] = new Semaforo;     // S_C1Oeste
    _semaforos[7] = new Semaforo;     // S_C1Leste

    //____________________________________________________________________________________

    /* Tempo de simulação */
    _tempoSimulacao = tTmp;
    _relogio = new Relogio;

    // Criar os primeiros carros do sistema e gera os proximos eventos de entrada
    for(int i = 0; i < 6; i++)
        _relogio->addEvento(_pistasFonte[i]->veiculoEntra(), 2, i, 1);  // tempo, evento, pista, tipoDePista

    /* Inicia com os semaforos que apontam para o norte abertos */
    _semaforoDir = 1;
    _semaforos[1]->trocaEstado(true);
    _semaforos[2]->trocaEstado(true);
}

Simulacao::~Simulacao()
{
    for(PistaAferente* tmp : _pistasFonte)
    {
        delete tmp;
        tmp = nullptr;
    }

    for(PistaEferente* tmp : _pistasReceptoras)
    {
        delete tmp;
        tmp = nullptr;
    }

    delete _relogio;
    _relogio = nullptr;
}

void Simulacao::attSemaforos()
{
    int i = 0;

    if(_semaforoDir == 1)
    {
        for(Semaforo* tmp : _semaforos)
        {
            if(i == 3 || i == 6)    tmp->trocaEstado(true);
            else                    tmp->trocaEstado(false);
            i++;
        }
    }

    else if(_semaforoDir == 2)
    {
        for(Semaforo* tmp : _semaforos)
        {
            if(i == 4 || i == 5)    tmp->trocaEstado(true);
            else                    tmp->trocaEstado(false);
            i++;
        }
    }

    else if(_semaforoDir == 3)
    {
        for(Semaforo* tmp : _semaforos)
        {
            if(i == 0 || i == 7)    tmp->trocaEstado(true);
            else                    tmp->trocaEstado(false);
            i++;
        }
    }

    else
    {
        for(Semaforo* tmp: _semaforos)
        {
            if(i == 1 || i == 2)    tmp->trocaEstado(true);
            else                    tmp->trocaEstado(false);
            i++;
        }
    }

    if(_semaforoDir == 4)   _semaforoDir = 1;
    else                    _semaforoDir++;
}

void Simulacao::attTimer()
{
    ++(*_relogio);
}

int Simulacao::getTempoAtual() const
{
    return _relogio->getTempo();
}

int Simulacao::getTempoSimulacao() const
{
    return _tempoSimulacao;
}

void Simulacao::execEventos()
{
    while(_relogio->horaDeEvento())
    {
        Evento tmp = _relogio->getEvento();
        switch(tmp.getTipoEvento())
        {
            /* Caso nao de para executar o evento agora, reenfileira novamente para a hora atual */
            case 1:
                if(!this->trocaPista(&tmp))
                    _relogio->addEvento(_relogio->getTempo() + 100, 1, tmp.getPistaEvento(), tmp.getTipoDePista());
                break;

            case 2:
                if(!this->veiculoSistema(tmp.getPistaEvento()))
                    _relogio->addEvento(_relogio->getTempo() + 100, 2, tmp.getPistaEvento(), 1);
                break;

            default:
                break;
        }
    }
}

bool Simulacao::trocaPista(Evento* eTmp)
{
    if((eTmp->getTipoDePista()) == 1)
    {
        // Semaforo fechado: os indices dos semaforos coincidem com os das pistas fontes
        if(!_semaforos[eTmp->getPistaEvento()]->getEstado())
            return false;
        if(!_pistasFonte[ eTmp->getPistaEvento() ]->pistaDisponivel())
            return false;
        if(!_pistasFonte[ eTmp->getPistaEvento() ]->veiculoSai())
            return false;

        return true;
    }

    else
    {
        // Semaforo fechado: os indices dos semaforos coincidem com os das pistas fontes
        if(!_semaforos[eTmp->getPistaEvento()]->getEstado())
            return false;
        if(!_pistasReceptoras[ eTmp->getPistaEvento() ]->pistaDisponivel())
            return false;
        if(!_pistasReceptoras[ eTmp->getPistaEvento() ]->veiculoSai())
            return false;

        return true;
    }
}

bool Simulacao::veiculoSistema(int i)
{
    if(!_pistasFonte[i]->pistaDisponivel())
        return false;

    _relogio->addEvento( _pistasFonte[i]->veiculoEntra() + _relogio->getTempo(), 2, i, 1);
    return true;
}

void Simulacao::movimentaVeiculos()
{
    /*
        Este também criar um evento trocaPista (pra hora atual, se primeiro carro da fila percorreu a pista
    */
    for(int i = 0; i < 6; i++)
    {
        if(_pistasFonte[i]->movimentaVeiculos())
            _relogio->addEvento( _relogio->getTempo(), 1, i, 1);    // tempo, evento, pista, tipoDePista
    }

    for(int i = 0; i < 8; i++)
    {
        if(_pistasReceptoras[i]->movimentaVeiculos())
            _relogio->addEvento( _relogio->getTempo(), 1, i, 2);    // tempo, evento, pista, tipoDePista
    }
}

std::vector<Simulacao::DadosVeiculo> Simulacao::getListaPosVeiculos()
{
    carros.clear();
    std::deque<int> tmp;

    // Pistas Fontes
    tmp = _pistasFonte[0]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({(int)((tmp[i] - 10) * 0.1925), 348, _pistasFonte[0]->getDirecao(), _pistasFonte[0]->getSentido()});

    tmp = _pistasFonte[1]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({483, 600 - (int)(0.44 * tmp[i]), _pistasFonte[1]->getDirecao(), _pistasFonte[1]->getSentido()});

    tmp = _pistasFonte[2]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({1190, 600 - (int)(0.44 * tmp[i]), _pistasFonte[2]->getDirecao(), _pistasFonte[2]->getSentido()});

    tmp = _pistasFonte[3]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({1570 - (int)(0.85 * tmp[i]), 283, _pistasFonte[3]->getDirecao(), _pistasFonte[3]->getSentido()});

    tmp = _pistasFonte[4]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({1133, (int)(0.504 * tmp[i]), _pistasFonte[4]->getDirecao(), _pistasFonte[4]->getSentido()});

    tmp = _pistasFonte[5]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({427, (int)(0.504 * tmp[i]), _pistasFonte[5]->getDirecao(), _pistasFonte[5]->getSentido()});

    // Pista Receptoras
    tmp = _pistasReceptoras[0]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({385 - (int)(tmp[i] * 0.1925), 282, _pistasReceptoras[0]->getDirecao(), _pistasReceptoras[0]->getSentido()});

    tmp = _pistasReceptoras[1]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({424, 380 + (int)(0.44 * tmp[i]), _pistasReceptoras[1]->getDirecao(), _pistasReceptoras[1]->getSentido()});

    tmp = _pistasReceptoras[2]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({1133, 380 + (int)(0.44 * tmp[i]), _pistasReceptoras[2]->getDirecao(), _pistasReceptoras[2]->getSentido()});

    tmp = _pistasReceptoras[3]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({1228 + (int)(0.85 * tmp[i]), 348, _pistasReceptoras[3]->getDirecao(), _pistasReceptoras[3]->getSentido()});

    tmp = _pistasReceptoras[4]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({1190, 252 - (int)(0.504 * tmp[i]), _pistasReceptoras[4]->getDirecao(), _pistasReceptoras[4]->getSentido()});

    tmp = _pistasReceptoras[5]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({487, 252 - (int)(0.504 * tmp[i]), _pistasReceptoras[5]->getDirecao(), _pistasReceptoras[5]->getSentido()});

    tmp = _pistasReceptoras[6]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({1090 - (int)(1.9 * tmp[i]), 280, _pistasReceptoras[6]->getDirecao(), _pistasReceptoras[6]->getSentido()});

    tmp = _pistasReceptoras[7]->getListaPosVeiculos();
    for(int i = 0; i < (int)tmp.size(); i++)
        carros.push_back({520 + (int)(1.9 * tmp[i]), 347, _pistasReceptoras[7]->getDirecao(), _pistasReceptoras[7]->getSentido()});

    return carros;
}

int Simulacao::getSemaforoDir() const
{
    return _semaforoDir;
}

int Simulacao::getQtdVeiculosIn() const
{
    return Veiculo::getQtdVeiculosIn();
}

int Simulacao::getQtdVeiculosOut() const
{
    return Veiculo::getQtdVeiculosOut();
}
