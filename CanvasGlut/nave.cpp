// Aluno: Anthony Silva

#include "nave.h"
#include "gl_canvas2d.h"
#include <math.h>

Nave::Nave(float startX, float startY) {
    pos.set(startX, startY);
    dir.set(0.0f, 1.0f);
    velocidade = 5.0f;

    vOriginal[0].set(0.0f, 20.0f);
    vOriginal[1].set(-15.0f, -15.0f);
    vOriginal[2].set(15.0f, -15.0f);
}

void Nave::moverLado(float direcaoX, int limiteEsq, int limiteDir) {
    pos.x += direcaoX * velocidade;

    if (pos.x < limiteEsq + 15.0f) pos.x = limiteEsq + 15.0f;
    if (pos.x > limiteDir - 15.0f) pos.x = limiteDir - 15.0f;
}

void Nave::moverFrente(float direcaoY, int limiteBaixo, int limiteCima) {
    pos.y += direcaoY * velocidade;

    if (pos.y < limiteBaixo + 15.0f) pos.y = limiteBaixo + 15.0f;
    if (pos.y > limiteCima - 15.0f) pos.y = limiteCima - 15.0f;
}

void Nave::desenhar() {
    float vx[3], vy[3];

    float angulo = atan2f(dir.y, dir.x) - PI_2 / 4.0f;
    float cosseno = cosf(angulo);
    float seno = sinf(angulo);

    for (int i = 0; i < 3; i++) {
        float rx = vOriginal[i].x * cosseno - vOriginal[i].y * seno;
        float ry = vOriginal[i].x * seno + vOriginal[i].y * cosseno;

        vx[i] = rx + pos.x;
        vy[i] = ry + pos.y;
    }

    CV::color(0.0f, 0.0f, 1.0f);
    CV::polygon(vx, vy, 3);
    CV::color(0.0f, 0.5f, 1.0f);
    CV::triangleFill(vx, vy);
}

Vector2 Nave::getPos() {
    return pos;
}