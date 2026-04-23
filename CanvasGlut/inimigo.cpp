// Aluno: Anthony Silva

#include "inimigo.h"
#include "gl_canvas2d.h"
#include <stdlib.h>
#include <math.h> 

Inimigo::Inimigo() {
    ativo = false;
    raio = 15.0f;
}

void Inimigo::spawn(float startX, float startY, int scoreAtual) {
    pos.set(startX, startY);
    startXOriginal = startX;

    float multiplicadorDificuldade = (scoreAtual / 2500.0f);
    velocidade = 1.0f + (rand() % 2) + multiplicadorDificuldade;

    ativo = true;
}

void Inimigo::atualizar(int limiteBaixo) {
    if (!ativo) return;

    pos.y -= velocidade;
    pos.x = startXOriginal + sinf(pos.y * 0.05f) * 40.0f;

    if (pos.y < limiteBaixo - 50.0f) {
        ativo = false;
    }
}

void Inimigo::desenhar() {
    if (!ativo) return;

    CV::color(1.0f, 0.0f, 0.0f);
    CV::circleFill(pos.x, pos.y, raio, 15);
    CV::color(0.5f, 0.0f, 0.0f);
    CV::circle(pos.x, pos.y, raio, 15);
}

bool Inimigo::isAtivo() { return ativo; }
void Inimigo::desativar() { ativo = false; }
Vector2 Inimigo::getPos() { return pos; }
float Inimigo::getRaio() { return raio; }

GerenciadorInimigos::GerenciadorInimigos() {
    maxInimigos = 50;
    timerSpawn = 0;
    tirosInimigos = new GerenciadorTiros();
}

GerenciadorInimigos::~GerenciadorInimigos() {
    delete tirosInimigos;
}

void GerenciadorInimigos::atualizar(int screenWidth, int screenHeight, int scoreAtual) {
    timerSpawn++;

    int limiteSpawn = 60 - (scoreAtual / 200) * 5;
    if (limiteSpawn < 15) limiteSpawn = 15;

    if (timerSpawn > limiteSpawn) {
        timerSpawn = 0;
        for (int i = 0; i < maxInimigos; i++) {
            if (!inimigos[i].isAtivo()) {
                float startX = (float)(rand() % (screenWidth - 80) + 40);
                float startY = (float)(screenHeight + 50);
                inimigos[i].spawn(startX, startY, scoreAtual);
                break;
            }
        }
    }

    for (int i = 0; i < maxInimigos; i++) {
        if (inimigos[i].isAtivo()) {
            inimigos[i].atualizar(0);

            int chanceTiro = 1 + (scoreAtual / 1000);
            if (rand() % 100 < chanceTiro) {
                Vector2 origem = inimigos[i].getPos();
                origem.y -= inimigos[i].getRaio();
                tirosInimigos->atirarParaBaixo(origem);
            }
        }
    }

    tirosInimigos->atualizar(screenHeight);
}

void GerenciadorInimigos::desenhar() {
    for (int i = 0; i < maxInimigos; i++) {
        inimigos[i].desenhar();
    }
    tirosInimigos->desenhar();
}

Inimigo* GerenciadorInimigos::getInimigos() { return inimigos; }
int GerenciadorInimigos::getMaxInimigos() { return maxInimigos; }
GerenciadorTiros* GerenciadorInimigos::getTirosInimigos() { return tirosInimigos; }