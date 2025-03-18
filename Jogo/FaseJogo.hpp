#ifndef FASEJOGO_HPP
#define FASEJOGO_HPP

#include "../ASCII_Engine/Fase.hpp"
#include "../ASCII_Engine/ObjetoDeJogo.hpp"
#include <string>
#include <list>
#include <array>
#include <vector>
#include "Barco.h"
#include "Jogador.h"
#include "KeyBoard.h"


struct AreaOcupada {
    int y_inicio, y_fim;
    int x_inicio, x_fim;
};

class FaseJogo : public Fase {
public:
    FaseJogo(std::string name, const Sprite &bkg): Fase(name,bkg) {}
    FaseJogo(std::string name, const SpriteAnimado &bkg): Fase(name,bkg) {}
    //virtual ~FaseJogo();

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    int verificaColisaoBomba(int y, int x, const std::vector<AreaOcupada>& areasOcupadas);
    bool posicaoJaBombardeada(int y, int x);
    bool todosBarcosDestruidos();




private:
    ObjetoDeJogo *sel, *bomba;

    std::vector<Barco*> emb;
    std::vector<AreaOcupada> areasOcupadas;
    Jogador* hero = new Jogador(9.0);
    TextSprite *life, *lifeBC, *lifeBD, *lifeBP, *lifeNG, *lifePA, *lifeSU;
    std::vector<std::pair<int, int>> posicoesBomba;
};

#endif // FASEJOGO_HPP

