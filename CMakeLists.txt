cmake_minimum_required(VERSION 3.28.3)
project(Pearl_Harbor_1941)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pearl_Harbor_1941
        Jogo/Main.cpp
        Jogo/Game.h
        Jogo/FaseInicial.h
        ASCII_Engine/Core/ColorHandler.cpp
        ASCII_Engine/Core/ColorHandler.hpp
        ASCII_Engine/Core/Cores_base.cpp
        ASCII_Engine/Core/Cores_base.hpp
        ASCII_Engine/Fase.cpp
        ASCII_Engine/Fase.hpp
        ASCII_Engine/ObjetoDeJogo.cpp
        ASCII_Engine/ObjetoDeJogo.hpp
        ASCII_Engine/Core/RenderBase.hpp
        ASCII_Engine/Sprite.cpp
        ASCII_Engine/Sprite.hpp
        ASCII_Engine/SpriteAnimado.cpp
        ASCII_Engine/SpriteAnimado.hpp
        ASCII_Engine/Core/SpriteBase.hpp
        ASCII_Engine/SpriteBuffer.cpp
        ASCII_Engine/SpriteBuffer.hpp
        ASCII_Engine/TextSprite.cpp
        ASCII_Engine/TextSprite.hpp
        ASCII_Engine/utils/Drawer.cpp
        ASCII_Engine/utils/Drawer.hpp
        ASCII_Engine/input/Keyboard.cpp
        ASCII_Engine/input/Keyboard.hpp
        Jogo/FaseJogo.hpp
        Jogo/FaseInicial.cpp
        Jogo/FaseFinal.cpp
        Jogo/FaseFinal.h
        Jogo/FaseJogo.cpp
        Jogo/PortaAviao.h
        Jogo/NaviodeGuerra.h
        Jogo/BarcoCruzador.h
        Jogo/Submarino.h
        Jogo/BarcoDestroyer.h
        Jogo/BarcoPatrulheiro.h
        Jogo/Barco.h
        Jogo/Jogador.h
)
