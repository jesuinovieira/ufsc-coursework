//_________________________________________________________________________________________________________________________________

#include <iostream>
#include <cstring>
#include "../header/Interface.hpp"
#include "../header/BatalhaNavalException.hpp"

using namespace std;

//_________________________________________________________________________________________________________________________________


int main(int argc, char **argv)
{
	if(argc > 3){
		cerr << "Argumentos invalidos!" 										<< endl << endl;
		cerr << "Para escolher o tipo de jogo:" 								<< endl;
		cerr << "Jogador contra Jogador:			$$ make ARGS=""JxJ"" run" 	<< endl;
		cerr << "Jogador contra Ambiente [Facil]:	$$ make ARGS=""JxA F"" run" << endl;
		cerr << "Jogador contra Ambiente [Dificil]:	$$ make ARGS=""JxA D"" run" << endl << endl;	
		
		return -1;
	}


/* _________________________________ Jogador contra ambiente _________________________________ */
	if(argc == 1 || (argc == 3 && strcmp(argv[1], "JxA") == 0))
	{
		if(argc == 1 || strcmp(argv[2], "D") == 0)	// Difícil
		{
			try{
				Interface<IA> game;
				game.inicia();
			}catch(BatalhaNavalException &e){
				cerr << e.what() << endl;
			}

			return 0;
		}

		else if(strcmp(argv[2], "F") == 0)			// Fácil
		{
			try{
				Interface<IA> game;
				game.inicia();
			}catch(BatalhaNavalException &e){
				cerr << e.what() << endl;
			}

			return 0;	
		}
	}

/* _________________________________ Jogador contra jogador _________________________________ */
	else if(argc == 2 && strcmp(argv[1], "JxJ") == 0)
	{
		try{
			Interface<Jogador> game;
			game.inicia();
		}catch(BatalhaNavalException &e){
			cerr << e.what() << endl;
		}

		return 0;
	}

/* _________________________________ Bad args _________________________________ */

	cerr << "Argumentos invalidos!" 										<< endl << endl;
	cerr << "Para escolher o tipo de jogo:" 								<< endl;
	cerr << "Jogador contra Jogador:			$$ make ARGS=""JxJ"" run" 	<< endl;
	cerr << "Jogador contra Ambiente [Facil]:	$$ make ARGS=""JxA F"" run" << endl;
	cerr << "Jogador contra Ambiente [Dificil]:	$$ make ARGS=""JxA D"" run" << endl << endl;	
	
	return -1;
}
//_________________________________________________________________________________________________________________________________