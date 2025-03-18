#ifndef NAVIODEGUERRA_H
#define NAVIODEGUERRA_H

#include "Barco.h"

class NaviodeGuerra : public Barco {
public:
    NaviodeGuerra(int y, int x)
        : Barco("NaviodeGuerra", "rsc/NaviodeGuerra.txt", y, x) {}

    int getLife() const override {
        return life;
    }
    void sofrerAtaque(int ataque) override {
        life = (life - ataque >= 0)?(life - ataque):0;
    }

private:
    int life = 14;
};

#endif