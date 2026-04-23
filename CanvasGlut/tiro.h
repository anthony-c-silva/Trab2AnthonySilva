// Aluno: Anthony Silva

#ifndef TIRO_H
#define TIRO_H

#include "Vector2.h"

enum TipoTiro {
    RETO,
    CURVO_BEZIER
};

class Tiro {
private:
    Vector2 pos;
    Vector2 dir;
    float velocidade;
    bool ativo;
    TipoTiro tipo;

    Vector2 p0;
    Vector2 p1;
    Vector2 p2;
    float t;

public:
    Tiro();
    void dispararReto(Vector2 origem, Vector2 direcao, float vel);
    void dispararCurvo(Vector2 origem, Vector2 pControle, Vector2 destino, float velTempo);
    void atualizar(int limiteAltura);
    void desenhar();
    bool isAtivo();
    void desativar();
    Vector2 getPos();
};

class GerenciadorTiros {
private:
    Tiro tiros[100];
    int maxTiros;

public:
    GerenciadorTiros();
    void atirar(Vector2 origem);
    void atirarParaBaixo(Vector2 origem);
    void atualizar(int limiteAltura);
    void desenhar();
    bool verificarColisao(Vector2 posAlvo, float raioAlvo);
};

#endif