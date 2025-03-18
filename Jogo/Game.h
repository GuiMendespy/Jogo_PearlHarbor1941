#include "FaseJogo.hpp"
#include "FaseInicial.h"
#include "FaseFinal.h"
#include "../ASCII_Engine/Sprite.hpp"
#include "../ASCII_Engine/SpriteAnimado.hpp"

class Game {
public:
	static void run() {
		SpriteBuffer buffer(234, 58);

		FaseInicial marcacao("FaseInicial", Sprite("rsc/Marcação.txt"));
		FaseJogo marcacao2("FaseInicial", Sprite("rsc/Marcação2.txt"));
        FaseFinal fim("FaseFinal", Sprite("rsc/Marcação.txt"));

		//FaseJogo base("Base Naval", Sprite("rsc/BaseNavalHavaiana.txt"));
		//FaseFinal marcacao2("FaseInicial", Sprite("rsc/Marcação.txt"));


		marcacao.init();
		int resul = marcacao.run(buffer);
		if (resul == Fase::LEVEL_COMPLETE) {
			buffer.clear();
			system("clear");
			marcacao2.init();
			marcacao2.run(buffer);
		}

		int ret1 =marcacao2.run(buffer);
		if ( ret1 != Fase::GAME_OVER && ret1 != Fase::END_GAME){

			buffer.clear();
			fim.init();
			fim.run(buffer);

		}else{
			std::cout << "GAME OVER" << std::endl;

		std::cout << "Saindo..." << std::endl;
		}
    }
};