#ifndef BARCOCRUZADOR_H
#define BARCOCRUZADOR_H

#include "Barco.h"

class BarcoCruzador : public Barco {
public:
    BarcoCruzador(int y, int x)
        : Barco("BarcoCruzador", "rsc/barcoCruzador.txt", y, x) {}

    int getLife() const override {
        return life;
    }
    void sofrerAtaque(int ataque) override {
        life = (life - ataque >= 0)?(life - ataque):0;
    }





private:
    int life = 8;
};

#endif