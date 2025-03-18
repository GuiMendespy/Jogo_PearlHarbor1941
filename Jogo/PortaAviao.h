#ifndef PORTAAVIAO_H
#define PORTAAVIAO_H

#include "Barco.h"

class PortaAviao : public Barco {
public:
    PortaAviao(int y, int x)
        : Barco("PortaAvião", "rsc/PortaAvião.txt", y, x) {}

    int getLife() const override {
        return life;
    }
    void sofrerAtaque(int ataque) override {
        life = (life - ataque >= 0)?(life - ataque):0;
    }

private:
    int life = 24;
};

#endif