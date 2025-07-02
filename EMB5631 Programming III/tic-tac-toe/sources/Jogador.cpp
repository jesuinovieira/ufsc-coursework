#include "../header/Jogador.hpp"

Jogador::Jogador() : _vitorias(0)
{
	// Construtor padrao
}

Jogador::Jogador(char tmp) : _marcador(tmp)
{
	//
}

Jogador::~Jogador()
{

}

void Jogador::setNome(std::string nome)
{
	_nome = nome;
}

void Jogador::setMarcador(char tmp)
{
	_marcador = tmp;
}

std::string Jogador::getNome() const
{
	return _nome;
}

char Jogador::getMarcador() const
{
	return _marcador;
}

int Jogador::getVitorias() const
{
	return _vitorias;
}

void Jogador::incrementaVitorias()
{
	_vitorias += 1;
}