#include <iostream>
#include <string>

class Jogador {
private:
    double vida;  // Vida do jogador

public:
    // Construtor para inicializar a vida do jogador
    Jogador(double vidaInicial) : vida(vidaInicial) {}

    // Método para sofrer dano
    void sofrerAtaque(double dano) {
        vida = (vida - dano >= 0)?(vida - dano):0;
    }

    // Método para verificar se o jogador está vivo
    bool isAlive() const {
        return vida > 0;
    }

    // Método para retornar a vida do jogador
    double getLife() const {
        return vida;
    }
};