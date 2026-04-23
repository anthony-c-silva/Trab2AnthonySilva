// Aluno: Anthony Silva

#ifndef INIMIGO_H
#define INIMIGO_H

#include "Vector2.h"
#include "tiro.h" 

class Inimigo {
private:
    Vector2 pos;
    float startXOriginal;
    float velocidade;
    bool ativo;
    float raio;

public:
    Inimigo();
    void spawn(float startX, float startY, int scoreAtual);
    void atualizar(int limiteBaixo);
    void desenhar();
    bool isAtivo();
    void desativar();
    Vector2 getPos();
    float getRaio();
};

class GerenciadorInimigos {
private:
    Inimigo inimigos[50];
    int maxInimigos;
    int timerSpawn;
    GerenciadorTiros* tirosInimigos;

public:
    GerenciadorInimigos();
    ~GerenciadorInimigos();
    void atualizar(int screenWidth, int screenHeight, int scoreAtual);
    void desenhar();

    Inimigo* getInimigos();
    int getMaxInimigos();
    GerenciadorTiros* getTirosInimigos();
};

#endif