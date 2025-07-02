#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <iostream>

// ______________________________________________________

class Jogador
{
public:
	Jogador();
	Jogador(char tmp);
	~Jogador();

	void setNome(std::string nome);
	void setMarcador(char tmp);

	std::string getNome() const;
	char getMarcador() const;
	int getVitorias() const;
	
	void incrementaVitorias();

private:
	std::string _nome;
	char _marcador;	
	int _vitorias;
};

#endif