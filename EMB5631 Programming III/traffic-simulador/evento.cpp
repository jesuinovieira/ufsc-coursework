#include "evento.hpp"

Evento::Evento(int tempo, int evento, int pista, int tipoDePista)
{
    _tempo = tempo;
    _tipoEvento = evento;
    _pista = pista;
    _tipoDePista = tipoDePista;
}

Evento::Evento(const Evento &evento)
{
    this->_tempo = evento._tempo;
    this->_tipoEvento = evento._tipoEvento;
    this->_pista = evento._pista;
    this->_tipoDePista = evento._tipoDePista;
}

bool Evento::operator < (const Evento& dTmp) const
{
    return this->_tempo > dTmp._tempo;
}

int Evento::getTipoEvento() const
{
    return _tipoEvento;
}

int Evento::getTempo() const
{
    return _tempo;
}

int Evento::getPistaEvento() const
{
    return _pista;
}

int Evento::getTipoDePista() const
{
    return _tipoDePista;
}
