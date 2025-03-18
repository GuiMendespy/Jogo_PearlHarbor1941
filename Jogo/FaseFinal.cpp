#include "FaseFinal.h"

void FaseFinal::init()
{
  	objs.push_back(new ObjetoDeJogo("Explosão",Sprite("rsc/ExplosãoGameOver.txt",COR::MARROM_ESCURA),23,18));
	objs.push_back(new ObjetoDeJogo("Finish",Sprite("rsc/finish.txt",COR::VERMELHA),23,61));
    objs.push_back(new ObjetoDeJogo("Explosão",Sprite("rsc/ExplosãoGameOver.txt",COR::MARROM_ESCURA),23,142));

    objs.push_back(new ObjetoDeJogo("Destroyer",Sprite("rsc/Destroyer2.txt",COR::VERDE),25,5));
    objs.push_back(new ObjetoDeJogo("NavioDeGuerra",Sprite("rsc/NaviodeGuerra2.txt",COR::VERDE),40,30));
    objs.push_back(new ObjetoDeJogo("PortaAvião",Sprite("rsc/PortaAvião2.txt",COR::VERDE),35,140));
    objs.push_back(new ObjetoDeJogo("Patrulheiro",Sprite("rsc/Patrulheiros2.txt",COR::VERDE),25,184));
    objs.push_back(new ObjetoDeJogo("Cruzador",Sprite("rsc/BarcoCruzador2.txt",COR::VERDE),12,51));
    objs.push_back(new ObjetoDeJogo("Submarino",Sprite("rsc/Submarino2.txt",COR::VERDE),12,140));

    objs.push_back(new ObjetoDeJogo("BombaInicio",Sprite("rsc/Inicio.txt",COR::MARROM_ESCURA),2,199));
    objs.push_back(new ObjetoDeJogo("BombaInicio",Sprite("rsc/Inicio.txt",COR::MARROM_ESCURA),25,199));

}

unsigned FaseFinal::run(SpriteBuffer &screen)
{
    std::string ent;

    //padrão
    draw(screen);
    system("clear");
    show(screen);


    for (int i = 0 ; i < 7*4 ; i++)
    {
        //lendo entrada
        getline(std::cin,ent);
        if (ent == "q")
            return Fase::END_GAME;

        //padrão
        update();
        draw(screen);
        system("clear");
        show(screen);
    }

    return Fase::END_GAME; // não necessário
}