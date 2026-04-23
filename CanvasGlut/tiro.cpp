// Aluno: Anthony Silva

#include "tiro.h"
#include "gl_canvas2d.h"

Tiro::Tiro() {
    ativo = false;
}

void Tiro::dispararReto(Vector2 origem, Vector2 direcao, float vel) {
    pos = origem;
    dir = direcao;
    dir.normalize();
    velocidade = vel;
    tipo = RETO;
    ativo = true;
}

void Tiro::dispararCurvo(Vector2 origem, Vector2 pControle, Vector2 destino, float velTempo) {
    p0 = origem;
    p1 = pControle;
    p2 = destino;
    t = 0.0f;
    velocidade = velTempo;
    tipo = CURVO_BEZIER;
    ativo = true;
}

void Tiro::atualizar(int limiteAltura) {
    if (!ativo) return;

    if (tipo == RETO) {
        pos.x += dir.x * velocidade;
        pos.y += dir.y * velocidade;

        if (pos.y > limiteAltura + 50.0f || pos.x < -100.0f || pos.x > 2000.0f || pos.y < -50.0f) {
            ativo = false;
        }
    }
    else if (tipo == CURVO_BEZIER) {
        t += velocidade;
        if (t > 1.0f) {
            ativo = false;
            return;
        }

        float u = 1.0f - t;
        float tt = t * t;
        float uu = u * u;

        pos.x = uu * p0.x + 2.0f * u * t * p1.x + tt * p2.x;
        pos.y = uu * p0.y + 2.0f * u * t * p1.y + tt * p2.y;
    }
}

void Tiro::desenhar() {
    if (!ativo) return;

    if (tipo == RETO) {
        CV::color(1.0f, 1.0f, 0.0f);
        CV::circleFill(pos.x, pos.y, 4.0f, 10);
    }
    else {
        CV::color(1.0f, 0.0f, 1.0f);
        CV::circleFill(pos.x, pos.y, 5.0f, 10);
    }
}

bool Tiro::isAtivo() {
    return ativo;
}

void Tiro::desativar() {
    ativo = false;
}

Vector2 Tiro::getPos() {
    return pos;
}

GerenciadorTiros::GerenciadorTiros() {
    maxTiros = 100;
}

void GerenciadorTiros::atirar(Vector2 origem) {
    for (int i = 0; i < maxTiros; i++) {
        if (!tiros[i].isAtivo()) {
            Vector2 dir(0.0f, 1.0f);
            tiros[i].dispararReto(origem, dir, 12.0f);
            break;
        }
    }

    for (int i = 0; i < maxTiros; i++) {
        if (!tiros[i].isAtivo()) {
            Vector2 pControle(origem.x - 300.0f, origem.y + 200.0f);
            Vector2 pDestino(origem.x - 50.0f, origem.y + 800.0f);
            tiros[i].dispararCurvo(origem, pControle, pDestino, 0.015f);
            break;
        }
    }

    for (int i = 0; i < maxTiros; i++) {
        if (!tiros[i].isAtivo()) {
            Vector2 pControle(origem.x + 300.0f, origem.y + 200.0f);
            Vector2 pDestino(origem.x + 50.0f, origem.y + 800.0f);
            tiros[i].dispararCurvo(origem, pControle, pDestino, 0.015f);
            break;
        }
    }
}

void GerenciadorTiros::atirarParaBaixo(Vector2 origem) {
    for (int i = 0; i < maxTiros; i++) {
        if (!tiros[i].isAtivo()) {
            Vector2 dir(0.0f, -1.0f);
            tiros[i].dispararReto(origem, dir, 7.0f);
            break;
        }
    }
}

void GerenciadorTiros::atualizar(int limiteAltura) {
    for (int i = 0; i < maxTiros; i++) {
        tiros[i].atualizar(limiteAltura);
    }
}

void GerenciadorTiros::desenhar() {
    for (int i = 0; i < maxTiros; i++) {
        tiros[i].desenhar();
    }
}

bool GerenciadorTiros::verificarColisao(Vector2 posAlvo, float raioAlvo) {
    for (int i = 0; i < maxTiros; i++) {
        if (tiros[i].isAtivo()) {
            Vector2 diff = tiros[i].getPos() - posAlvo;
            if (diff.length() <= (raioAlvo + 5.0f)) {
                tiros[i].desativar();
                return true;
            }
        }
    }
    return false;
}