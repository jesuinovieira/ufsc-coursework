#ifndef NAVIO_HPP
#define NAVIO_HPP


//_________________________________________________________________________________________________________________________________

#include <iostream>

//_________________________________________________________________________________________________________________________________


/* Classe base para: Fragata, Balizador, Contratorpedeiro, Cruzador e PortaAvioes */
class Navio
{
public:
	Navio(std::string, int);
	~Navio();

	// Métodos set
	void setTipo(std::string);
	void setLinha(int);
	void setColuna(int);
	void setDirecao(char);

	// Métodos get
	std::string getTipo() const;
	int getTamanho() const;
	int getVida() const;
	int getLinha() const;
	int getColuna() const;
	char getDirecao() const;

	// Outros métodos
	void decrementaVida();

private:
	std::string _tipo;

	int _tamanho;
	int _vida;

	int _x;			// 1 - 15
	int _y;			// A - O (Já convertido para 1 - 15)
	char _direcao;	// H ou V
};



/* Classes derivadas da classe base Navio */


//_________________________________________________________________________________________________________________________________

class Fragata : public Navio
{
public:
	Fragata() : Navio::Navio("Fragata", 2) {}
	~Fragata() {}
	
};
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

class Balizador : public Navio
{
public:
	Balizador() : Navio::Navio("Balizador", 2) {}
	~Balizador() {}
	
};
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

class Contratorpedeiro : public Navio
{
public:
	Contratorpedeiro() : Navio::Navio("Contratorpedeiro", 3) {}
	~Contratorpedeiro() {}
	
};
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

class Cruzador : public Navio
{
public:
	Cruzador() : Navio::Navio("Cruzador", 3) {}
	~Cruzador() {}
	
};
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

class PortaAvioes : public Navio
{
public:
	PortaAvioes() : Navio::Navio("PortaAvioes", 4) {}
	~PortaAvioes() {}
	
};
//_________________________________________________________________________________________________________________________________


#endif