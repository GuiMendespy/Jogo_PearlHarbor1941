#include "../ASCII_Engine/Fase.hpp"
#include "KeyBoard.h"

class FaseInicial: public Fase
{
public:
    FaseInicial(std::string name, const Sprite &bkg) : Fase(name,bkg) {}
    FaseInicial(std::string name, const SpriteAnimado &bkg) : Fase(name,bkg) {}
    virtual ~FaseInicial() {}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);
private:
    ObjetoDeJogo *seta,*desc,*seta2;

    enum {MENU_INICIAR, MENU_INFO, DESCRICAO};

};