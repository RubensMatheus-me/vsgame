# Projeto Game - Baseado em Vampire Survival

Este é um jogo simples feito com **C++** e **SDL2**, inspirado no estilo do jogo **Vampire Survival**. Abaixo estão as instruções para rodar o projeto tanto no **Linux** quanto no **Windows**.

## Requisitos
- **my-lib** -> https://github.com/ehmcruz/my-lib
- **SDL2**
- **SDL2_image**
- **g++** (ou outro compilador C++)

---

## Instalação no Linux

1. **Instale as dependências**:
   ```bash
   sudo apt-get install libsdl2-dev libsdl2-image-dev g++ make
2. **Clone o repositório**:
   ```bash
   git clone https://github.com/RubensMatheus-me/vsgame
3. **Compile o projeto e rode o jogo**:  
   **No terminal linux(wsl) execute os comandos**:
    ```bash
     make
     /game
## Instalação no Windows

1. **Instale o MinGW e as bibliotecas SDL2 e SDL2_image.**
2. **Clone o repositório**:
   ```bash
   git clone https://github.com/RubensMatheus-me/vsgame
3. **Compile o projeto com MinGW e rode o jogo:**  
   **No terminal, execute o comando abaixo (se necessario substitua os caminhos corretos das bibliotecas SDL2 e SDL2_image)**:
   ```bash
   g++ -std=c++23 -Wall -Iinclude -I../my-lib/include -I/path/to/SDL2/include -I/path/to/SDL2_image/include src/*.cpp -o game -L/path/to/SDL2/lib -L/path/to/SDL2_image/lib -lSDL2 -lSDL2_image
   /game
