#ifndef BARCO_H
#define BARCO_H

#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Barco : public ObjetoDeJogo {
public:
    Barco(const std::string& nome, const std::string& spritePath, int y, int x)
        : ObjetoDeJogo(nome, SpriteAnimado(spritePath, 2,COR::AZUL), y, x) {}

    virtual ~Barco() = default;
    virtual int getLife() const = 0;
    virtual void sofrerAtaque(int ataque) = 0;

};

#endif