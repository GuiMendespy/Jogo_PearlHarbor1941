#ifndef KEYBOARD_H // Verifica se KEYBOARD_H não foi definido
#define KEYBOARD_H

#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

namespace KEY {
    const char A = 'a';
    const char D = 'd';
    const char S = 's';
    const char W = 'w';
    const char Y = 'y';
    const char X = 'x';
    const char Q = 'q';
    const char ENTER = 10;  // Código ASCII do Enter

    // Definição de setas como valores únicos
    const int UP = 1000;
    const int DOWN = 1001;
    const int LEFT = 1002;
    const int RIGHT = 1003;
}

class KeyBoard {
public:
    static void setInputMode(bool enable = true) {
        struct termios t{};
        tcgetattr(STDIN_FILENO, &t);  // Obtém as configurações do terminal

        if (enable) {
            t.c_lflag &= ~ICANON;  // Desativa o modo canônico
            t.c_lflag &= ~ECHO;    // Desativa a exibição da tecla pressionada
            tcsetattr(STDIN_FILENO, TCSANOW, &t);
        } else {
            t.c_lflag |= ICANON;  // Reativa o modo canônico
            t.c_lflag |= ECHO;    // Reativa a exibição da tecla
            tcsetattr(STDIN_FILENO, TCSANOW, &t);
        }
    }

    static bool readInput(int &input) {
        char ch;
        if (read(STDIN_FILENO, &ch, 1) != 1) return false;

        if (ch == '\x1b') {  // Sequência de escape (setas e outras teclas especiais)
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) != 1) return false;
            if (read(STDIN_FILENO, &seq[1], 1) != 1) return false;

            if (seq[0] == '[') {
                switch (seq[1]) {
                    case 'A': input = KEY::UP; return true;   // Seta para cima
                    case 'B': input = KEY::DOWN; return true; // Seta para baixo
                    case 'C': input = KEY::RIGHT; return true; // Seta para direita
                    case 'D': input = KEY::LEFT; return true;  // Seta para esquerda
                }
            }
            return false;
        }

        input = ch;  // Teclas normais (WASD, Enter, etc.)
        return true;
    }
};

#endif // Fim do include guard