#ifndef SUBMARINO_H
#define SUBMARINO_H

#include "Barco.h"

class Submarino : public Barco {
public:
    Submarino(int y, int x)
        : Barco("Submarino", "rsc/Submarino.txt", y, x) {}

    int getLife() const override {
        return life;
    }
    void sofrerAtaque(int ataque) override {
        life = (life - ataque >= 0)?(life - ataque):0;
    }

private:
    int life = 4;
};

#endif