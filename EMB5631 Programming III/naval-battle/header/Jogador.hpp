#ifndef JOGADOR_HPP
#define JOGADOR_HPP


//_________________________________________________________________________________________________________________________________

#include <iostream>
#include <random>
#include <vector>
#include "Navio.hpp"
#include "Tabuleiro.hpp"

//_________________________________________________________________________________________________________________________________


class Jogador
{
public:
	Jogador(int = 70);	// Por padrão, o jogador possui 70 tiros para destruir a frota do oponente.
	~Jogador();

	// Métodos set
	void setNome(std::string nome);
	void setDadosNavio(int, int, char, char, int);	

	// Métodos get
	std::string getNome() const;
	int getVitorias() const;
	int getTiros() const;
	const Tabuleiro* getTabuleiro() const;

	// Outros métodos
	bool verificaJogada(int, int, int, char);
	void posicionaNavio(int, int, int, char, char);
	void incrementaVitorias();

	void posicionaNaviosAleatoriamente();
	bool tiroInvalido(int, int);
	char atirarXY(int, int);

	bool perdeuJogo() const;

	int getVidaNavios() const;

protected:
	std::string _nome;
	Tabuleiro _tabuleiro;
	int _vitorias;
	int _tiros;	// Qtd de tiros

	std::vector<Fragata> _F;
	std::vector<Balizador> _B;
	std::vector<Contratorpedeiro> _CO;
	std::vector<Cruzador> _CR;
	std::vector<PortaAvioes> _P;

	bool verificaJogadaHorizontal(int, int, int);
	bool verificaJogadaVertical(int, int, int);
	void posicionaNavioHorizontal(int, int, int, char);
	void posicionaNavioVertical(int, int, int, char);

	void setDadosFragata(int, int, char, int);
	void setDadosBalizador(int, int, char, int);
	void setDadosContratorpedeiro(int, int, char, int);
	void setDadosCruzador(int, int, char, int);
	void setDadosPortaAvioes(int, int, char, int);
};

#endif