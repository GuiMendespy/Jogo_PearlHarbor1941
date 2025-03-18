#include "FaseInicial.h"

void FaseInicial::init()
{
    objs.push_back(new ObjetoDeJogo("textoNomeDoJogo", Sprite("rsc/TextoNomedoJogo.txt",COR::VERMELHA), 10, 30));
    objs.push_back(new ObjetoDeJogo("textoInicial", Sprite("rsc/TextoInicio.txt",COR::AMARELA), 26, 92));
    objs.push_back(new ObjetoDeJogo("textoInf", Sprite("rsc/TextoInformações.txt",COR::AMARELA), 33, 65));

    objs.push_back(new ObjetoDeJogo("Destroyer",Sprite("rsc/Destroyer2.txt",COR::VERDE),4,100));
    objs.push_back(new ObjetoDeJogo("NavioDeGuerra",Sprite("rsc/NaviodeGuerra2.txt",COR::VERDE),2,2));
    objs.push_back(new ObjetoDeJogo("PortaAvião",Sprite("rsc/PortaAvião2.txt",COR::VERDE),2,202));
    objs.push_back(new ObjetoDeJogo("Patrulheiro",Sprite("rsc/Patrulheiros2.txt",COR::VERDE),5,65));
    objs.push_back(new ObjetoDeJogo("Cruzador",Sprite("rsc/BarcoCruzador2.txt",COR::VERDE),2,130));
    objs.push_back(new ObjetoDeJogo("Submarino",Sprite("rsc/Submarino2.txt",COR::VERDE),2,175));

    objs.push_back(new ObjetoDeJogo("BombaInicio",Sprite("rsc/Inicio.txt",COR::MARROM_ESCURA),21,2));
    objs.push_back(new ObjetoDeJogo("BombaInicio",Sprite("rsc/Inicio.txt",COR::MARROM_ESCURA),21,199));


    seta = new ObjetoDeJogo("Seta",Sprite("rsc/seta.txt",COR::VERDE),26,78);
    objs.push_back(seta);

    desc = new ObjetoDeJogo("Desc",Sprite("rsc/descrição.txt"),43,4);
    objs.push_back(desc);
    desc->desativarObj();

    seta2 = new ObjetoDeJogo("Seta2",Sprite("rsc/seta.txt",COR::VERDE),33,50);
    objs.push_back(seta2);
    seta2->desativarObj();
}

unsigned FaseInicial::run(SpriteBuffer& screen)
{
    int state = MENU_INICIAR; // Começa com a seta em "Iniciar"
    int ent = 0;

    // Renderiza o estado inicial da fase
    draw(screen);
    system("clear");
    show(screen);

    while (true)
    {
        KeyBoard::setInputMode(true); // Habilita modo de leitura de tecla sem buffer

        if (KeyBoard::readInput(ent)) {
            if (ent == KEY::Q)
                return Fase::END_GAME;

            switch (state)
            {
                case MENU_INICIAR:
                    if (ent == KEY::S || ent == KEY::DOWN) { // Pressionar "s" move a seta para baixo
                        seta->desativarObj();
                        seta2->ativarObj();
                        state = MENU_INFO;
                    }
                    else if (ent == KEY::Y || ent == KEY::ENTER) { // Pressionar "y" inicia o jogo
                        return Fase::LEVEL_COMPLETE; // Vai para a primeira fase
                    }
                    break;

                case MENU_INFO:
                    if (ent == KEY::W || ent == KEY::UP) { // Pressionar "w" move a seta para cima
                        seta2->desativarObj();
                        seta->ativarObj();
                        state = MENU_INICIAR;
                    }
                    else if (ent == KEY::Y || ent == KEY::ENTER) { // Pressionar "y" exibe a descrição
                        desc->ativarObj();
                        state = DESCRICAO;
                    }
                    break;

                case DESCRICAO:
                    if (ent == KEY::X ) { // Pressionar "x" fecha a descrição
                        desc->desativarObj();
                        state = MENU_INFO; // Volta para o estado de menu
                    }
                    break;
            }
        }

        // Atualiza e desenha a fase após cada iteração
        update();
        draw(screen);
        system("clear"); // Ou use outra forma de atualização de tela, sem limpar o terminal
        show(screen);
        KeyBoard::setInputMode(false);
    }

    return Fase::END_GAME; // Retorno padrão caso algo dê errado
}

