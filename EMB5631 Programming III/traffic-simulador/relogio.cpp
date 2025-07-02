#include "relogio.hpp"
#include <iostream>

Relogio::Relogio()
{
    _tempo = 0;
}

Relogio::Relogio(const Relogio& rTmp)
{
    this->_tempo = rTmp._tempo;
    this->_filaEventos = rTmp._filaEventos;
}

Relogio::~Relogio()
{

}

Relogio& Relogio::operator++()     // prefix
{
    this->_tempo += 1;
    return *this;
}

int Relogio::getTempo() const
{
    return this->_tempo;
}

bool Relogio::horaDeEvento() const
{
    if(_filaEventos.empty())
        return false;

    Evento tmp = _filaEventos.top();

    if(tmp.getTempo() <= this->_tempo)  // Executa eventos atuais e eventos que já eram pra ter acontecidos
        return true;

    return false;
}

Evento Relogio::getEvento()
{
    if(_filaEventos.empty())
        throw std::logic_error("A fila de eventos esta vazia.");

    Evento tmp = _filaEventos.top();
    _filaEventos.pop();

    return tmp;
}

void Relogio::addEvento(int tempo, int tipoEvento, int indicePista, int tipoPista)
{
    _filaEventos.emplace(tempo, tipoEvento, indicePista, tipoPista);
}
