#include "FaseJogo.hpp"
#include <iostream>
#include <random>
#include <vector>
#include "BarcoCruzador.h"
#include "BarcoDestroyer.h"
#include "BarcoPatrulheiro.h"
#include "NaviodeGuerra.h"
#include "PortaAviao.h"
#include "Submarino.h"

// Estrutura para representar uma área ocupada


bool verificaSobreposicao(int y, int x, int altura, int largura, const std::vector<AreaOcupada>& ocupadas) {
    for (const auto& area : ocupadas) {
        if (!(y + altura <= area.y_inicio || y >= area.y_fim ||
              x + largura <= area.x_inicio || x >= area.x_fim)) {
            return true;
        }
    }
    return false;
}

bool posicaoMultiploDe4(int y, int x) {
    return (y == 3 || y == 7|| y == 11 || y == 15 || y == 19 || y == 23 || y == 27 || y == 31 || y == 35 || y == 39 || y == 43 || y == 47) && (x == 99 || x == 104 || x == 109 || x == 114 || x ==119 || x == 124 || x == 129 || x == 134 || x == 139 || x == 144 || x == 149 || x == 154 || x == 159 || x == 164 || x == 169 || x == 174 || x == 179 || x ==184 || x == 189 || x == 194 || x == 199 || x == 204 || x == 209 || x == 214 || x == 219 || x == 224);
}

void FaseJogo::init() {
    objs.push_back(new ObjetoDeJogo("BaseNaval", Sprite("rsc/BaseNavalHavaiana.txt"), 1, 3));
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<std::pair<std::string, std::pair<int, int>>> barcos = {
        {"BarcoCruzador", {16, 8}},
        {"Destroyer", {8, 4}},
        {"NaviodeGuerra", {32, 8}},
        {"Patrulheiros", {4, 4}},
        {"PortaAvião", {28, 16}},
        {"Submarino", {8, 8}},
    };

    for (const auto& barco : barcos) {
        int largura = barco.second.first;
        int altura = barco.second.second;
        std::uniform_int_distribution<int> distrib_y(3, 50 - altura);
        std::uniform_int_distribution<int> distrib_x(99, 227 - largura);
        int y, x;
        do {
            y = distrib_y(gen);
            x = distrib_x(gen);
        } while (verificaSobreposicao(y, x, altura, largura, areasOcupadas) || !posicaoMultiploDe4(y, x));

        if (barco.first == "BarcoCruzador") {
            auto* barcoNovo = new BarcoCruzador(y, x);
            emb.push_back(barcoNovo);
            objs.push_back(barcoNovo);  // Adiciona à lista de objetos para renderização
        } else if (barco.first == "Destroyer") {
            auto* barcoNovo = new BarcoDestroyer(y, x);
            emb.push_back(barcoNovo);
            objs.push_back(barcoNovo);
        } else if (barco.first == "NaviodeGuerra") {
            auto* barcoNovo = new NaviodeGuerra(y, x);
            emb.push_back(barcoNovo);
            objs.push_back(barcoNovo);
        } else if (barco.first == "Patrulheiros") {
            auto* barcoNovo = new BarcoPatrulheiro(y, x);
            emb.push_back(barcoNovo);
            objs.push_back(barcoNovo);
        } else if (barco.first == "PortaAvião") {
            auto* barcoNovo = new PortaAviao(y, x);
            emb.push_back(barcoNovo);
            objs.push_back(barcoNovo);
        } else if (barco.first == "Submarino") {
            auto* barcoNovo = new Submarino(y, x);
            emb.push_back(barcoNovo);
            objs.push_back(barcoNovo);
        }

        areasOcupadas.push_back({y, y + altura, x, x + largura});
        std::cout << "Área ocupada adicionada: (" << y << ", " << y + altura << ") x (" << x << ", " << x + largura << ")\n";
        }

    // Adiciona Tanque e Morteiro em posições fixas para não interferir nos barcos
    objs.push_back(new ObjetoDeJogo("Tanque", SpriteAnimado("rsc/Tanque.txt", 2,COR::VERMELHA), 3, 5));
    objs.push_back(new ObjetoDeJogo("Tanque", SpriteAnimado("rsc/Tanque.txt", 2,COR::VERMELHA), 40, 5));
    objs.push_back(new ObjetoDeJogo("Morteiro", SpriteAnimado("rsc/Morteiro.txt", 2,COR::VERMELHA), 10, 5));
    objs.push_back(new ObjetoDeJogo("Morteiro", SpriteAnimado("rsc/Morteiro.txt", 2,COR::VERMELHA), 24, 5));

    objs.push_back(new ObjetoDeJogo("Bomba", SpriteAnimado("rsc/BombadeGuerra.txt", 2,COR::MARROM_ESCURA), 18, 59));
    objs.push_back(new ObjetoDeJogo("Bomba", SpriteAnimado("rsc/BombadeGuerra.txt", 2,COR::MARROM_ESCURA), 23, 59));
    objs.push_back(new ObjetoDeJogo("Bomba", SpriteAnimado("rsc/BombadeGuerra.txt", 2,COR::MARROM_ESCURA), 28, 59));

    sel = new ObjetoDeJogo("Seletor", SpriteAnimado("rsc/seletor.txt", 1,COR::AMARELA), 2, 98);
    objs.push_back(sel);

    bomba = new ObjetoDeJogo("Bomba", SpriteAnimado("rsc/BombadeGuerra.txt", 2,COR::VERDE), 23, 59);
    objs.push_back(bomba);
    bomba->desativarObj();

    objs.push_back(new ObjetoDeJogo("Life",TextSprite("##########",COR::VERDE),53,29));
    SpriteBase *tmp = const_cast<SpriteBase*> (objs.back()->getSprite());
    life = dynamic_cast<TextSprite*> (tmp);

    objs.push_back(new ObjetoDeJogo("LifeBC",TextSprite("########",COR::VERDE),54,29));
    SpriteBase *tmpBC = const_cast<SpriteBase*> (objs.back()->getSprite());
    lifeBC = dynamic_cast<TextSprite*> (tmpBC);

    objs.push_back(new ObjetoDeJogo("LifeBD",TextSprite("##",COR::VERDE),55,29));
    SpriteBase *tmpBD = const_cast<SpriteBase*> (objs.back()->getSprite());
    lifeBD = dynamic_cast<TextSprite*> (tmpBD);

    objs.push_back(new ObjetoDeJogo("LifeBP",TextSprite("#",COR::VERDE),56,29));
    SpriteBase *tmpBP = const_cast<SpriteBase*> (objs.back()->getSprite());
    lifeBP = dynamic_cast<TextSprite*> (tmpBP);

    objs.push_back(new ObjetoDeJogo("LifeNG",TextSprite("##############",COR::VERDE),53,78));
    SpriteBase *tmpNG = const_cast<SpriteBase*> (objs.back()->getSprite());
    lifeNG = dynamic_cast<TextSprite*> (tmpNG);

    objs.push_back(new ObjetoDeJogo("LifePA",TextSprite("############################",COR::VERDE),54,79));
    SpriteBase *tmpPA = const_cast<SpriteBase*> (objs.back()->getSprite());
    lifePA = dynamic_cast<TextSprite*> (tmpPA);

    objs.push_back(new ObjetoDeJogo("LifeSU",TextSprite("####",COR::VERDE),55,78));
    SpriteBase *tmpSU = const_cast<SpriteBase*> (objs.back()->getSprite());
    lifeSU = dynamic_cast<TextSprite*> (tmpSU);
}
int FaseJogo::verificaColisaoBomba(int y_bomba, int x_bomba, const std::vector<AreaOcupada>& areasOcupadas) {
    for (int i = 0; i < areasOcupadas.size(); i++) {
        std::cout << "Verificando colisão em (" << y_bomba << ", " << x_bomba << ") com área ("
                  << areasOcupadas[i].y_inicio << ", " << areasOcupadas[i].y_fim << ") x ("
                  << areasOcupadas[i].x_inicio << ", " << areasOcupadas[i].x_fim << ")\n";

        if (y_bomba >= areasOcupadas[i].y_inicio && y_bomba < areasOcupadas[i].y_fim &&
            x_bomba >= areasOcupadas[i].x_inicio && x_bomba < areasOcupadas[i].x_fim) {
            std::cout << "Colisão detectada com área " << i << "!\n";

            return i;  // Retorna o índice do barco atingido
            }
    }

    std::cout << "Nenhuma colisão detectada.\n";
    return -1;  // Nenhuma colisão encontrada
}

bool FaseJogo::posicaoJaBombardeada(int y, int x) {
    for (const auto& pos : posicoesBomba) {
        if (pos.first == y && pos.second == x) {
            return true;  // Posição já foi bombardeada
        }
    }
    return false;
}
bool FaseJogo::todosBarcosDestruidos() {
    for (int barco = 0; barco<emb.size();barco++) {
            if (emb[barco]->getLife() !=0 ) {
                return false;
            }
    }// Retorna true se todos os barcos foram removidos
    return true;
}


unsigned FaseJogo::run(SpriteBuffer &screen)
{
    draw(screen);
    system("clear");
    show(screen);
    std::string ent;

    while (true) {
      	// Atualiza e imprime o estado dos barcos
        std::cout << "\nEstado atual dos barcos:\n";
        for (const auto& barco : emb) {
            std::cout << barco->getName() << " - Vida: " << barco->getLife() << "\n";
        }
        if (todosBarcosDestruidos()) {
    		std::cout << "Parabéns! Você destruiu todos os barcos! Fim de jogo." << std::endl;
   			return Fase::LEVEL_COMPLETE;  // Defina um estado de vitória e saia do jogo

        }
		KeyBoard::setInputMode(true); // Habilita modo de leitura de tecla sem buffer
        int input;

        if (KeyBoard::readInput(input)) {
            if (((input == KEY::W) || (input == KEY::UP)) && sel->getPosL() > 2)
                sel->moveUp(4);
            else if (((input == KEY::S)||(input == KEY::DOWN)) && sel->getPosL() < 45)
                sel->moveDown(4);
            else if (((input == KEY::A) || (input == KEY::LEFT)) && sel->getPosC() > 98)
                sel->moveLeft(5);
            else if (((input == KEY::D) || (input == KEY::RIGHT)) && sel->getPosC() < 220)
                sel->moveRight(5);
            else if (((input == KEY::Y) || (input == KEY::ENTER))) {
          	int y_bomba = sel->getPosL();
    		int x_bomba = sel->getPosC();

    		// Verifica se a posição já foi bombardeada
    		if (posicaoJaBombardeada(y_bomba, x_bomba)) {
        	std::cout << "Você já lançou uma bomba nessa posição! Escolha outro local.\n";
        	continue;  // Pula a execução para a próxima entrada do jogador
    		}

   			 // Se ainda não foi bombardeada, adiciona ao vetor
    		posicoesBomba.push_back({y_bomba, x_bomba});
            bomba->ativarObj();  // Ativa a bomba

        	// Loop para mover a bomba até a posição do seletor
        	while (bomba->getPosL() != sel->getPosL() || bomba->getPosC() != sel->getPosC()) {
            	if (bomba->getPosL() < sel->getPosL()) {
               		 bomba->moveDown(1);
            	} else if (bomba->getPosL() > sel->getPosL()) {
                	bomba->moveUp(1);
            	}

            	if (bomba->getPosC() < sel->getPosC()) {
             	   bomba->moveRight(1);
           	 	}else if (bomba->getPosC() > sel->getPosC()) {
              	  bomba->moveLeft(1);
            	}
        	}
        	bomba->desativarObj();
        	objs.push_back(new ObjetoDeJogo("Destroços", Sprite("rsc/Destroços.txt",COR::VERMELHA), sel->getPosL(), sel->getPosC()));

        	// Verifica colisão com os barcos no array global
        	double danoBomba = 10.0;  // Defina o dano da bomba

        	bool bombaAtingiuBarco = false;  // Flag para verificar se a bomba atingiu algum barco

        	int num = verificaColisaoBomba(sel->getPosL()+1, sel->getPosC()+1, areasOcupadas);

        	if (num != -1) {
            	std::cout << "Bomba atingiu um barco!" << std::endl;
            	std::cout<<num<<std::endl;

            	// Atualiza a barra de vida correspondente
            	if (emb[num]->getName() == "BarcoCruzador") {
                	emb[num]->sofrerAtaque(1);
                	lifeBC->setText(std::string(emb[num]->getLife(), '#'));
                	std::cout<<"Você colidiu "<<emb[num]->getName()<<"sua vida resta: "<<emb[num]->getLife()<<std::endl;
                	if (emb[num]->getLife() == 0) {
                    	std::cout<<"Voce destruiu um banco todo!"<<std::endl;
                    	//emb[num]->desativarObj();
                        if (todosBarcosDestruidos()) {
    						std::cout << "Todos os barcos foram destruídos! O jogo acabou!" << std::endl;
    						return Fase::LEVEL_COMPLETE;  // Ou outro código de retorno que encerre o jogo corretamente
						}


                	}
            	} else if (emb[num]->getName() == "Destroyer") {
                	emb[num]->sofrerAtaque(1);
                	lifeBD->setText(std::string(emb[num]->getLife() , '#'));
                	std::cout<<"Você colidiu "<<emb[num]->getName()<<"sua vida resta: "<<emb[num]->getLife()<<std::endl;
                	if (emb[num]->getLife() == 0) {
                    	std::cout<<"Voce destruiu um banco todo!"<<std::endl;
						//emb[num]->desativarObj();
                         if (todosBarcosDestruidos()) {
    						std::cout << "Todos os barcos foram destruídos! O jogo acabou!" << std::endl;
    						return Fase::LEVEL_COMPLETE;  // Ou outro código de retorno que encerre o jogo corretamente
						}

                	}
            	} else if (emb[num]->getName() == "NaviodeGuerra") {
                	emb[num]->sofrerAtaque(1);
                	lifeNG->setText(std::string(emb[num]->getLife(), '#'));
                	std::cout<<"Você colidiu "<<emb[num]->getName()<<"sua vida resta: "<<emb[num]->getLife()<<std::endl;
                	if (emb[num]->getLife() == 0) {
                    	std::cout<<"Voce destruiu um banco todo!"<<std::endl;
						//emb[num]->desativarObj();
                        if (todosBarcosDestruidos()) {
    						std::cout << "Todos os barcos foram destruídos! O jogo acabou!" << std::endl;
    						return Fase::LEVEL_COMPLETE;  // Ou outro código de retorno que encerre o jogo corretamente
						}

                	}
            	} else if (emb[num]->getName() == "Patrulheiros") {
                	emb[num]->sofrerAtaque(1);
                	lifeBP->setText(std::string(emb[num]->getLife(), '#'));
                	std::cout<<"Você colidiu "<<emb[num]->getName()<<"sua vida resta: "<<emb[num]->getLife()<<std::endl;
                	if (emb[num]->getLife() == 0) {
                    	std::cout<<"Voce destruiu um banco todo!"<<std::endl;
						//emb[num]->desativarObj();
                        if (todosBarcosDestruidos()) {
    						std::cout << "Todos os barcos foram destruídos! O jogo acabou!" << std::endl;
    						return Fase::LEVEL_COMPLETE;  // Ou outro código de retorno que encerre o jogo corretamente
						}

                	}
            	} else if (emb[num]->getName() == "PortaAvião") {
                	emb[num]->sofrerAtaque(1);
                	lifePA->setText(std::string(emb[num]->getLife() , '#'));
                	std::cout<<"Você colidiu "<<emb[num]->getName()<<"sua vida resta: "<<emb[num]->getLife()<<std::endl;
                	if (emb[num]->getLife() == 0) {
                    	std::cout<<"Voce destruiu um banco todo!"<<std::endl;
						//emb[num]->desativarObj();
				        if (todosBarcosDestruidos()) {
    						std::cout << "Todos os barcos foram destruídos! O jogo acabou!" << std::endl;
    						return Fase::LEVEL_COMPLETE;  // Ou outro código de retorno que encerre o jogo corretamente
						}

                	}
            	} else if (emb[num]->getName() == "Submarino") {
                	emb[num]->sofrerAtaque(1);
                	lifeSU->setText(std::string(emb[num]->getLife(), '#'));
                	std::cout<<"Você colidiu "<<emb[num]->getName()<<"sua vida resta: "<<emb[num]->getLife()<<std::endl;
                	if (emb[num]->getLife() == 0) {
                    	std::cout<<"Voce destruiu um banco todo!"<<std::endl;
						//emb[num]->desativarObj();
                        if (todosBarcosDestruidos()) {
    						std::cout << "Todos os barcos foram destruídos! O jogo acabou!" << std::endl;
    						return Fase::LEVEL_COMPLETE;  // Ou outro código de retorno que encerre o jogo corretamente
						}

                	}
            	}
        	}else{
            	// Se a bomba não atingiu nenhum barco, reduz a vida do jogador
            	hero->sofrerAtaque(1);
           		// life->setText(std::string(hero->getLife(), '#'));
            	std::cout << "Bomba não atingiu nenhum barco. Dano ao jogador!" << std::endl;

            	if (hero->isAlive() <=0) {
                	std::cout << "Game Over!" << std::endl;
                	return Fase::GAME_OVER;
            	} else {
            		life->setText(std::string(hero->getLife(), '#'));
                	std::cout << "O jogo continua. Vida restante: " << hero->getLife() << std::endl;
            	}
        	if (todosBarcosDestruidos()) {
    			std::cout << "Parabéns! Você destruiu todos os barcos! Fim de jogo." << std::endl;
   				return Fase::LEVEL_COMPLETE;  // Defina um estado de vitória e saia do jogo

                }
        }
        }
        }
        update();
        draw(screen);
        system("clear");
        show(screen);
        KeyBoard::setInputMode(false);
    }
}