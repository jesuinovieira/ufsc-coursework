#ifndef EVENTO_HPP
#define EVENTO_HPP

class Evento
{
public:
    explicit Evento(int, int, int, int);
    Evento(const Evento &evento);

    bool operator < (const Evento&) const;  // Sobrecarga do operador <

    int getTempo() const;
    int getTipoEvento() const;
    int getPistaEvento() const;
    int getTipoDePista() const;

private:
    int _tempo;                 // Tempo que o evento acontecerá
    int _tipoEvento;            // Tipo do evento: 1(Veiculo chega no sistema) e 2(Veiculo trocara de pista)
    int _pista;                 // Pista que o evento ocorrerá
    int _tipoDePista;           // Tipo da pista que acontecera o evento: 1(Fonte), 2(Central) e 3(Sumidouro)
};

#endif // EVENTO_HPP
