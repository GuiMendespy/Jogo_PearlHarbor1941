#ifndef BARCODESTROYER_H
#define BARCODESTROYER_H

#include "Barco.h"

class BarcoDestroyer : public Barco {
public:
    BarcoDestroyer(int y, int x)
        : Barco("Destroyer", "rsc/Destroyer.txt", y, x) {}
    int getLife() const override {
        return life;
    }
    void sofrerAtaque(int ataque) override {
        life = (life - ataque >= 0)?(life - ataque):0;
    }

private:
    int life =2;
};

#endif