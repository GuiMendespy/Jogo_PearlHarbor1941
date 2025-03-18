#ifndef BARCOPATRULHEIRO_H
#define BARCOPATRULHEIRO_H

#include "Barco.h"

class BarcoPatrulheiro : public Barco {
public:
    BarcoPatrulheiro(int y, int x)
        : Barco("Patrulheiros", "rsc/Patrulheiros.txt", y, x) {}

    int getLife() const override {
        return life;
    }
    void sofrerAtaque(int ataque) override {
        life = (life - ataque >= 0)?(life - ataque):0;
    }
    // Método para verificar se o jogador está vivo

private:
    int life = 1;
};

#endif