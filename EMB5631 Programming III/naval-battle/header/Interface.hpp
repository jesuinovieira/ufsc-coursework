#ifndef INTERFACE_HPP
#define INTERFACE_HPP

//_________________________________________________________________________________________________________________________________

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <iomanip>
#include <unistd.h>
#include "BatalhaNaval.hpp"
#include "BatalhaNavalException.hpp"
#include "Tabuleiro.hpp"
#include "Jogador.hpp"
#include "IA.hpp"

using namespace std;

//_________________________________________________________________________________________________________________________________


template<class T>
class Interface
{
public:

	Interface()
	{
		throw BatalhaNavalException(1);
	}

	~Interface()
	{
		//
	}
	
};


//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________



template<>
class Interface<IA>
{
public:

//_________________________________________________________________________________________________________________________________

	Interface()
	{
		/* No construtor da classe BatalhaNaval é posicionado os navios dos jogadores. */
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	~Interface()
	{
		//
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	void inicia()
	{
		int x = 0;
		int y = 0;

		char R = '\0';

		const Tabuleiro* A = nullptr;
		const Tabuleiro* B = nullptr;

		int i = 0;

		/*
			A idéia é, toda rodada, pegar os tabuleiros e imprimir:
				'~' -> Lugares que ainda não foram atirados
				' ' -> Lugares que foram atirado e errou
				'X' -> Lugares que foram atirado e acertou
		*/

		try{
			while( !BN.fimDeJogo() )
			{

				BN.getTabuleiros(&A, &B);
				imprimeTabuleiros(A, B);

				/* ************** */
				// BN.estatisticas();
				/* ************** */

				BN.setRodada(++i);

				try{

					if(BN.getRodada() % 2 != 0)		solicitaInput(x, y);
					else
													cout << endl << "Vez do computador..." << endl;
					
					try{
						R = BN.verificaTiro(x, y);

						if(R == 'F')
						{
											std::cout << std::endl << "Tiro invalido!" 			<< std::endl << std::endl;
											BN.setRodada(--i);	
						}		
						
						else if(R == 'A')	std::cout << std::endl << "Navio atingido." 	<< std::endl << std::endl;
						else				std::cout << std::endl << "Agua atingida." 	<< std::endl << std::endl;

					}catch(std::string navio){
						std::cout << std::endl << navio << " destruido!" << std::endl;
					}

					usleep(750000);

				}catch(BatalhaNavalException &e){
					std::cout << std::endl << e.what() << std::endl;
					break;
				}
			}
		}catch(BatalhaNavalException &e){
			std::cout << std::endl << e.what() << std::endl;
		}
		
		BN.getTabuleiros(&A, &B);
		estatisticas(A, B, BN.getCampeao());
	}
//_________________________________________________________________________________________________________________________________


protected:
//_________________________________________________________________________________________________________________________________

	void estatisticas(const Tabuleiro* A, const Tabuleiro* B, Jogador* J)
	{
		char tmp = '\0';

		std::cout << "\tTabuleiro do jogador\t\t";
		std::cout << "\t    Tabuleiro do computador";
		std::cout << std::endl;
		std::cout << "_________________________________________________________________________________";
		std::cout << std::endl;

		std::cout << "\tA B C D E F G H I J K L M N O\t";
		std::cout << "\t    A B C D E F G H I J K L M N O\t";
		std::cout << std::endl << std::endl;

		for(int x = 0; x < 15; x++)
		{
			std::cout << "    " << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "\t";
			
			for(int y = 0; y < 30; y++)
			{
				if(y < 15)
				{
					tmp = A->getXY(x, y);
					if(tmp == '~')
						std::cout << "\033[1;34m" << '~' << "\033[0m" << " ";	// Azul
					else if(tmp == 'X')
						std::cout << "\033[1;31m" << tmp << " " << "\033[0m";	// Vermelho
					else
						std::cout << tmp << " ";								// Space e navios
				}	
				
				else if( y == 15)
				{
					tmp = B->getXY(x, y - 15);
					if(tmp == '~')
						std::cout << "\t\t" << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "\033[1;34m" << "  " << '~' << " " << "\033[0m";
					else if(tmp == 'X')
						std::cout << "\t\t" << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "\033[1;31m" << "  " << tmp << " " << "\033[0m";
					else
						std::cout << "\t\t" << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "  " << tmp << " ";
				}

				else{
					tmp = B->getXY(x, y - 15);
					if(tmp == '~')
						std::cout << "\033[1;34m" << '~' << "\033[0m" << " ";	// Azul
					else if(tmp == 'X')
						std::cout << "\033[1;31m" << tmp << " " << "\033[0m";	// Vermelho
					else
						std::cout << tmp << " ";
				}
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;
		std::cout << "\tFragata\t\t\t-> A" << std::endl;
		std::cout << "\tBalizador\t\t-> B" << std::endl;
		std::cout << "\tContratorpedeiro\t-> C" << std::endl;
		std::cout << "\tCruzador\t\t-> D" << std::endl;
		std::cout << "\tPorta-avioes\t\t-> E" << std::endl;

		if(J == nullptr)
			std::cout << std::endl << "O jogo empatou!" << std::endl;
		else
			std::cout << std::endl << "O " << J->getNome() << " venceu!" << std::endl;
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	void imprimeTabuleiros(const Tabuleiro* A, const Tabuleiro* B)
	{
		char tmp = '\0';

		std::cout << "\tTabuleiro do jogador\t\t";
		std::cout << "\t    Tabuleiro do computador";
		std::cout << std::endl;
		std::cout << "_________________________________________________________________________________";
		std::cout << std::endl;

		std::cout << "\tA B C D E F G H I J K L M N O\t";
		std::cout << "\t    A B C D E F G H I J K L M N O\t";
		std::cout << std::endl << std::endl;

		for(int x = 0; x < 15; x++)
		{
			std::cout << "    " << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "\t";
			
			for(int y = 0; y < 30; y++)
			{
				if(y < 15)
				{
					tmp = A->getXY(x, y);
					if(tmp == 'A' || tmp == 'B' || tmp == 'C' || tmp == 'D' || tmp == 'E' || tmp == '~')
						std::cout << "\033[1;34m" << '~' << "\033[0m" << " ";	// Azul
					else if(tmp == 'X')
						std::cout << "\033[1;31m" << tmp << " " << "\033[0m";	// Vermelho
					else
						std::cout << tmp << " ";								// Space
				}	
				
				else if( y == 15)
				{
					tmp = B->getXY(x, y - 15);
					if(tmp == 'A' || tmp == 'B' || tmp == 'C' || tmp == 'D' || tmp == 'E' || tmp == '~')
						std::cout << "\t\t" << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "\033[1;34m" << "  " << '~' << " " << "\033[0m";
					else if(tmp == 'X')
						std::cout << "\t\t" << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "\033[1;31m" << "  " << tmp << " " << "\033[0m";
					else
						std::cout << "\t\t" << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "  " << tmp << " ";
				}

				else{
					tmp = B->getXY(x, y - 15);
					if(tmp == 'A' || tmp == 'B' || tmp == 'C' || tmp == 'D' || tmp == 'E' || tmp == '~')
						std::cout << "\033[1;34m" << '~' << "\033[0m" << " ";	// Azul
					else if(tmp == 'X')
						std::cout << "\033[1;31m" << tmp << " " << "\033[0m";	// Vermelho
					else
						std::cout << tmp << " ";
				}
			}
			std::cout << std::endl;
		}
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	void solicitaInput(int &x, int &y)
	{
		string R = "\0";

	    while(1){
	        
	        cout << endl << "Insira a coordenada: ";	getline(cin, R);
	        
	    	if(verificaTamanho(R) && verificaX(R, x) && verificaY(R, y))
	    		break;

	    	if(!verificaDesistencia(R))
	    	{
		    	cout << endl;
		    	cout << "  Entrada invalida!" << endl;
		    	cout << "  Sao exemplos de entrada: A1, F13, O9." << endl;
		    	cout << "  Linhas: 1 - 15" << endl;
		    	cout << "  Colunas: A - O" << endl << endl;

		    	cout << "  Para desisitir, digite S ou Sair." << endl << endl;
		    }
	    }
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	void solicitaDirecao(char &d)
	{
		while(1)
		{
			cout << "Insira a direcao da embarcacao [H ou V]: ";	
			cin.get(d); cin.clear(); cin.ignore(256, '\n');

			if(verificaDirecao(toupper(d))){
				d = toupper(d);
				return;
			}else{
				cout << endl;
				cout << "Direcao invalida!" << endl;
				cout << "H - Horizontal" << endl;
				cout << "V - Vertical" << endl << endl;
			}
		}
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	bool verificaDirecao(char d)
	{
		if(d == 'H' || d == 'V')	return true;
									return false;
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	bool verificaX(string R, int &x)
	{
		if(R.size() == 2)
			x = (R[1] - '0') - 1;
		else
			x = 10 * (R[1] - '0') + (R[2] - '0') - 1;
		
		if(x < 0 || x > 14)	return false;
							return true;
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	bool verificaY(string R, int &y)
	{
		R[0] = toupper(R[0]);

		y = (R[0] - 'A');

		if(y < 0 || y > 14)	return false;
							return true;
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	bool verificaTamanho(string R)
	{
	    if(R.size() > 3)	return false;
	    					return true;
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	bool verificaDesistencia(string R)
	{
		char d = '\0';
		if(R.compare("S") == 0 || R.compare("s") == 0 || R.compare("Sair") == 0 || R.compare("sair") == 0){
			cout << "Voce tem certeza que deseja abandonar o jogo? (S/N) ";
			
			while(1)
			{
				cin.get(d); cin.clear(); cin.ignore(256, '\n');
				if(d == 's' || d == 'S')
					throw BatalhaNavalException(2);
				
				if(d == 'n' || d == 'N')
					return true;

				cout << "Entrada invalida! Voce tem certeza que deseja abandonar o jogo? (S/N) ";
			}
		}

		return false;
	}
//_________________________________________________________________________________________________________________________________


private:
	BatalhaNaval<IA> BN;
};



//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________________



template<>
class Interface<Jogador>
{
public:
//_________________________________________________________________________________________________________________________________

	Interface()
	{
		/* No construtor da classe BatalhaNaval é posicionado os navios dos jogadores .*/
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	~Interface()
	{
		//
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	void inicia()
	{
		int x = 0;
		int y = 0;

		char R = '\0';

		const Tabuleiro* A = nullptr;
		const Tabuleiro* B = nullptr;

		int i = 0;

		/*
			A idéia é, toda rodada, pegar os tabuleiros e imprimir:
				'~' -> Lugares que ainda não foram atirados
				' ' -> Lugares que foram atirado e errou
				'X' -> Lugares que foram atirado e acertou
		*/
		
		try{
			while( !BN.fimDeJogo() )
			{
			
				BN.getTabuleiros(&A, &B);
				imprimeTabuleiros(A, B);

				BN.setRodada(++i);

				try{

					solicitaInput(x, y);
					
					try{
						R = BN.verificaTiro(x, y);

						if(R == 'F')
						{
											std::cout << std::endl << "Tiro invalido!" 			<< std::endl << std::endl;
											BN.setRodada(--i);	
						}		
						
						else if(R == 'A')	std::cout << std::endl << "Navio atingido." 	<< std::endl << std::endl;
						else				std::cout << std::endl << "Agua atingida." 	<< std::endl << std::endl;

					}catch(std::string navio){
						std::cout << std::endl << navio << " destruido!" << std::endl << std::endl;
					}

				}catch(BatalhaNavalException &e){
					std::cout << std::endl << e.what() << std::endl << std::endl;
					break;
				}

				usleep(750000);
			}
		}catch(BatalhaNavalException &e){
			std::cout << std::endl << e.what() << std::endl << std::endl;
		}

		BN.getTabuleiros(&A, &B);
		estatisticas(A, B, BN.getCampeao());
	}
//_________________________________________________________________________________________________________________________________


protected:
//_________________________________________________________________________________________________________________________________

	void estatisticas(const Tabuleiro* A, const Tabuleiro* B, Jogador* J)
	{
		char tmp = '\0';

		std::cout << "\tTabuleiro do jogador A\t\t";
		std::cout << "\t    Tabuleiro do jogador B";
		std::cout << std::endl;
		std::cout << "_________________________________________________________________________________";
		std::cout << std::endl;

		std::cout << "\tA B C D E F G H I J K L M N O\t";
		std::cout << "\t    A B C D E F G H I J K L M N O\t";
		std::cout << std::endl << std::endl;

		for(int x = 0; x < 15; x++)
		{
			std::cout << "    " << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "\t";
			
			for(int y = 0; y < 30; y++)
			{
				if(y < 15)
				{
					tmp = A->getXY(x, y);
					if(tmp == '~')
						std::cout << "\033[1;34m" << '~' << "\033[0m" << " ";	// Azul
					else if(tmp == 'X')
						std::cout << "\033[1;31m" << tmp << " " << "\033[0m";	// Vermelho
					else
						std::cout << tmp << " ";								// Space e navios
				}	
				
				else if( y == 15)
				{
					tmp = B->getXY(x, y - 15);
					if(tmp == '~')
						std::cout << "\t\t" << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "\033[1;34m" << "  " << '~' << " " << "\033[0m";
					else if(tmp == 'X')
						std::cout << "\t\t" << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "\033[1;31m" << "  " << tmp << " " << "\033[0m";
					else
						std::cout << "\t\t" << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "  " << tmp << " ";
				}

				else{
					tmp = B->getXY(x, y - 15);
					if(tmp == '~')
						std::cout << "\033[1;34m" << '~' << "\033[0m" << " ";	// Azul
					else if(tmp == 'X')
						std::cout << "\033[1;31m" << tmp << " " << "\033[0m";	// Vermelho
					else
						std::cout << tmp << " ";
				}
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;
		std::cout << "\tFragata\t\t\t-> A" << std::endl;
		std::cout << "\tBalizador\t\t-> B" << std::endl;
		std::cout << "\tContratorpedeiro\t-> C" << std::endl;
		std::cout << "\tCruzador\t\t-> D" << std::endl;
		std::cout << "\tPorta-avioes\t\t-> E" << std::endl;

		if(J == nullptr)
			std::cout << std::endl << "O jogo empatou!" << std::endl;
		else
			std::cout << std::endl << "O " << J->getNome() << " venceu!" << std::endl;
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	void imprimeTabuleiros(const Tabuleiro* A, const Tabuleiro* B)
	{
		char tmp = '\0';

		std::cout << "\tTabuleiro do jogador A\t\t";
		std::cout << "\t    Tabuleiro do jogador B";
		std::cout << std::endl;
		std::cout << "_________________________________________________________________________________";
		std::cout << std::endl;

		std::cout << "\tA B C D E F G H I J K L M N O\t";
		std::cout << "\t    A B C D E F G H I J K L M N O\t";
		std::cout << std::endl << std::endl;

		for(int x = 0; x < 15; x++)
		{
			std::cout << " " << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "\t";
			
			for(int y = 0; y < 30; y++)
			{
				if(y < 15)
				{
					tmp = A->getXY(x, y);
					if(tmp == 'A' || tmp == 'B' || tmp == 'C' || tmp == 'D' || tmp == 'E' || tmp == '~')
						std::cout << "\033[1;34m" << '~' << "\033[0m" << " ";	// Azul
					else if(tmp == 'X')
						std::cout << "\033[1;31m" << tmp << " " << "\033[0m";	// Vermelho
					else
						std::cout << tmp << " ";								// Space
				}	
				
				else if( y == 15)
				{
					tmp = B->getXY(x, y - 15);
					if(tmp == 'A' || tmp == 'B' || tmp == 'C' || tmp == 'D' || tmp == 'E' || tmp == '~')
						std::cout << "\t\t" << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "\033[1;34m" << "  " << '~' << " " << "\033[0m";
					else if(tmp == 'X')
						std::cout << "\t\t" << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "\033[1;31m" << "  " << tmp << " " << "\033[0m";
					else
						std::cout << "\t\t" << std::setfill( '0' ) << std::setw( 2 ) << x + 1 << "  " << tmp << " ";
				}

				else{
					tmp = B->getXY(x, y - 15);
					if(tmp == 'A' || tmp == 'B' || tmp == 'C' || tmp == 'D' || tmp == 'E' || tmp == '~')
						std::cout << "\033[1;34m" << '~' << "\033[0m" << " ";	// Azul
					else if(tmp == 'X')
						std::cout << "\033[1;31m" << tmp << " " << "\033[0m";	// Vermelho
					else
						std::cout << tmp << " ";
				}
			}
			std::cout << std::endl;
		}
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	void solicitaInput(int &x, int &y)
	{
		string R = "\0";

	    while(1){
	        
	        if(BN.getRodada() % 2 == 0){
	        	cout << endl << "Insira a coordenada (Jogador B): ";	
	        	getline(cin, R);
	        }
	        else{
	        	cout << endl << "Insira a coordenada (Jogador A): ";	
	        	getline(cin, R);
	        }
	        
	    	if(verificaTamanho(R) && verificaX(R, x) && verificaY(R, y))
	    		break;

	    	if(!verificaDesistencia(R))
	    	{
		    	cout << endl;
		    	cout << "  Entrada invalida!" << endl;
		    	cout << "  Sao exemplos de entrada: A1, F13, O9." << endl;
		    	cout << "  Linhas: 1 - 15" << endl;
		    	cout << "  Colunas: A - O" << endl << endl;

		    	cout << "  Para desisitir, digite S ou Sair." << endl << endl;
		    }
	    }
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	void solicitaDirecao(char &d)
	{
		while(1)
		{
			cout << "Insira a direcao da embarcacao [H ou V]: ";	
			cin.get(d); cin.clear(); cin.ignore(256, '\n');

			if(verificaDirecao(toupper(d))){
				d = toupper(d);
				return;
			}else{
				cout << endl;
				cout << "Direcao invalida!" << endl;
				cout << "H - Horizontal" << endl;
				cout << "V - Vertical" << endl << endl;
			}
		}
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	bool verificaDirecao(char d)
	{
		if(d == 'H' || d == 'V')	return true;
									return false;
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	bool verificaX(string R, int &x)
	{
		if(R.size() == 2){
			x = (R[1] - '0') - 1;
		}else{
			x = 10 * (R[1] - '0') + (R[2] - '0') - 1;
		}

		if(x < 0 || x > 14)	return false;
							return true;
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	bool verificaY(string R, int &y)
	{
		R[0] = toupper(R[0]);

		y = (R[0] - 'A');

		if(y < 0 || y > 14)	return false;
							return true;
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	bool verificaTamanho(string R)
	{
	    if(R.size() > 3)	return false;
	    					return true;
	}
//_________________________________________________________________________________________________________________________________


//_________________________________________________________________________________________________________________________________

	bool verificaDesistencia(string R)
	{
		char d = '\0';
		if(R.compare("S") == 0 || R.compare("s") == 0 || R.compare("Sair") == 0 || R.compare("sair") == 0){
			cout << "Voce tem certeza que deseja abandonar o jogo? (S/N) ";
			
			while(1)
			{
				cin.get(d); cin.clear(); cin.ignore(256, '\n');
				if(d == 's' || d == 'S')
					throw BatalhaNavalException(2);
				
				if(d == 'n' || d == 'N')
					return true;

				cout << "Entrada invalida! Voce tem certeza que deseja abandonar o jogo? (S/N) ";
			}
		}

		return false;
	}
//_________________________________________________________________________________________________________________________________


private:
	BatalhaNaval<Jogador> BN;
};



#endif