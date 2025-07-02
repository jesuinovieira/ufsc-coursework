#ifndef IA_HPP
#define IA_HPP

//_________________________________________________________________________________________________________________________________

#include <iostream>
#include <list>
#include "Jogador.hpp"
#include "Coordenadas.hpp"

//_________________________________________________________________________________________________________________________________


class IA : public Jogador
{
public:
	IA();
	~IA();

	/* Funções IA */
	void getTiros(int*, int*, bool);
	void insereTiro(int, int);

	bool getInteligencia() const;
	bool lTirosVazia() const;

	void esvaziarlTiros();

private:
	std::list<Coordenadas> _lTiros;
	bool _inteligencia;	// True se sim, false se não
	
	void tiroAleatorio(int*, int*, bool);
	bool tiroRepetido(int, int);
	bool confereParidade(int, int);
};

//_________________________________________________________________________________________________________________________________


#endif