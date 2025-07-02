#ifndef RELOGIO_HPP
#define RELOGIO_HPP

#include <queue>
#include <stdexcept>
#include "evento.hpp"

class Evento;

class Relogio
{
public:
    Relogio();
    Relogio(const Relogio&);    // Copy constructor
    ~Relogio();

    Relogio& operator++();      // prefix
    Evento getEvento();

    int getTempo() const;
    bool horaDeEvento() const;
    void addEvento(int, int, int, int);

private:
    int _tempo;                                 // Tempo ficticio da simulacao
    std::priority_queue<Evento> _filaEventos;   // Fila de eventos
};

#endif // RELOGIO_HPP
