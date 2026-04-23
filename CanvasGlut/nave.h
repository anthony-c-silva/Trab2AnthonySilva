// Aluno: Anthony Silva

#ifndef NAVE_H
#define NAVE_H

#include "Vector2.h"

class Nave {
private:
    Vector2 pos;
    Vector2 dir;
    float velocidade;
    Vector2 vOriginal[3];

public:
    Nave(float startX, float startY);
    void moverLado(float direcaoX, int limiteEsq, int limiteDir);
    void moverFrente(float direcaoY, int limiteBaixo, int limiteCima);
    void desenhar();
    Vector2 getPos();
};

#endif