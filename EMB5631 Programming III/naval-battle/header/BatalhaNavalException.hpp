#ifndef BATALHANAVALEXCEPTION_HPP
#define BATALHANAVALEXCEPTION_HPP

//_________________________________________________________________________________________________________________________________

#include <iostream>
#include <exception>

//_________________________________________________________________________________________________________________________________

/* Classe abstrata. */
class BatalhaNavalException : public std::exception
{
public:
	BatalhaNavalException(int erro) : codigo(erro)
	{
		//
	}

	virtual const char* what() const throw();

private:
	int codigo;
};

//_________________________________________________________________________________________________________________________________


const char* BatalhaNavalException::what() const throw()
{
	switch(codigo){
		case 1:
			return "Excecao: tipo de jogo indefinido! Tente novamente.";
		case 2:
			return "Um jogador abandonou o jogo!";
		case 3:
			return "Seus tiros acabaram!";
		default:
			return "Excecao desconhecida.";
	}
}

#endif