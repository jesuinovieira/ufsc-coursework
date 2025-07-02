#include "semaforo.hpp"

Semaforo::Semaforo(int tempo) : _tempo(tempo)
{
    _estado = false;
}

void Semaforo::trocaEstado(bool eTmp)
{
    _estado = eTmp;
}

bool Semaforo::getEstado() const
{
    return _estado;
}
