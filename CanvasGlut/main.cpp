// Aluno: Anthony Silva

#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "Vector2.h"
#include "gui.h"
#include "nave.h"
#include "tiro.h"
#include "inimigo.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int screenWidth = 800, screenHeight = 600;
int mouseX, mouseY;

enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

GameState estadoAtual = MENU;

Nave* player = nullptr;
GerenciadorTiros* armamento = nullptr;
GerenciadorInimigos* horda = nullptr;

GuiManager* guiMenu = nullptr;
GuiManager* guiPause = nullptr;
GuiManager* guiGameOver = nullptr;

Botao* btnIniciar = nullptr;
Botao* btnContinuar = nullptr;
Botao* btnSair = nullptr;
Botao* btnReiniciar = nullptr;

float cameraOffsetY = 0.0f;
int score = 0;
bool teclas[300] = { false };

void atualizarMovimento() {
    if (player == nullptr) return;

    if (teclas[201]) player->moverFrente(1.0f, 0, screenHeight / 2);
    if (teclas[203]) player->moverFrente(-1.0f, 0, screenHeight / 2);
    if (teclas[200]) player->moverLado(-1.0f, 0, screenWidth);
    if (teclas[202]) player->moverLado(1.0f, 0, screenWidth);
}

void processarColisoes() {
    if (armamento == nullptr || horda == nullptr || player == nullptr) return;

    Inimigo* inimigos = horda->getInimigos();
    int maxInimigos = horda->getMaxInimigos();
    Vector2 posPlayer = player->getPos();

    for (int i = 0; i < maxInimigos; i++) {
        if (inimigos[i].isAtivo()) {
            if (armamento->verificarColisao(inimigos[i].getPos(), inimigos[i].getRaio())) {
                inimigos[i].desativar();
                score += 100;
            }

            Vector2 diffCorpo = posPlayer - inimigos[i].getPos();
            if (diffCorpo.length() <= (inimigos[i].getRaio() + 15.0f)) {
                estadoAtual = GAME_OVER;
                return;
            }
        }
    }

    if (horda->getTirosInimigos()->verificarColisao(posPlayer, 15.0f)) {
        estadoAtual = GAME_OVER;
    }
}

void render() {
    CV::clear(0.05f, 0.05f, 0.1f);

    if (estadoAtual == MENU) {
        CV::color(1.0f, 1.0f, 1.0f);
        CV::text(screenWidth / 2 - 80, 100, "GALAGA ENGINE C++");
        if (guiMenu != nullptr) guiMenu->renderAll();
    }
    else if (estadoAtual == PLAYING) {
        atualizarMovimento();
        cameraOffsetY -= 1.0f;

        CV::color(1.0f, 1.0f, 1.0f);
        for (int i = 0; i < 50; i++) {
            float starX = (float)((i * 87) % screenWidth);
            float starY = (float)(((i * 123) + (int)cameraOffsetY) % (screenHeight * 10));
            if (starY > 0 && starY < screenHeight) CV::point(starX, starY);
        }

        if (horda != nullptr) horda->atualizar(screenWidth, screenHeight, score);
        if (armamento != nullptr) armamento->atualizar(screenHeight);

        processarColisoes();

        if (horda != nullptr) horda->desenhar();
        if (armamento != nullptr) armamento->desenhar();
        if (player != nullptr) player->desenhar();

        CV::color(1.0f, 1.0f, 1.0f);
        char textoPlacar[50];
        sprintf(textoPlacar, "SCORE: %04d", score);
        CV::text(20, screenHeight - 30, textoPlacar);
    }
    else if (estadoAtual == PAUSED) {
        CV::color(1.0f, 1.0f, 1.0f);
        CV::text(screenWidth / 2 - 30, 100, "PAUSED");
        if (guiPause != nullptr) guiPause->renderAll();
    }
    else if (estadoAtual == GAME_OVER) {
        CV::color(1.0f, 0.0f, 0.0f);
        CV::text(screenWidth / 2 - 40, 100, "GAME OVER");
        CV::color(1.0f, 1.0f, 1.0f);
        char textoPlacar[50];
        sprintf(textoPlacar, "FINAL SCORE: %04d", score);
        CV::text(screenWidth / 2 - 60, 130, textoPlacar);
        if (guiGameOver != nullptr) guiGameOver->renderAll();
    }

    Sleep(16);
}

void keyboard(int key) {
    if (key < 300) teclas[key] = true;
    if (key == 27) exit(0);

    if (key == 'p' || key == 'P') {
        if (estadoAtual == PLAYING) estadoAtual = PAUSED;
        else if (estadoAtual == PAUSED) estadoAtual = PLAYING;
    }

    if (estadoAtual == PLAYING) {
        if (key == 32) {
            if (player != nullptr && armamento != nullptr) {
                armamento->atirar(player->getPos());
            }
        }
    }
}

void keyboardUp(int key) {
    if (key < 300) teclas[key] = false;
}

void resetarJogo() {
    delete player;
    delete armamento;
    delete horda;
    player = new Nave(screenWidth / 2.0f, 100.0f);
    armamento = new GerenciadorTiros();
    horda = new GerenciadorInimigos();
    score = 0;
    cameraOffsetY = 0.0f;
}

void mouse(int button, int state, int wheel, int direction, int x, int y) {
    mouseX = x;
    mouseY = y;

    if (state == 0) {
        if (estadoAtual == MENU) {
            if (guiMenu != nullptr && guiMenu->getBotaoClicado(x, y) == btnIniciar) {
                resetarJogo();
                estadoAtual = PLAYING;
            }
        }
        else if (estadoAtual == PAUSED) {
            if (guiPause != nullptr) {
                Botao* clicado = guiPause->getBotaoClicado(x, y);
                if (clicado == btnContinuar) estadoAtual = PLAYING;
                else if (clicado == btnSair) exit(0);
            }
        }
        else if (estadoAtual == GAME_OVER) {
            if (guiGameOver != nullptr && guiGameOver->getBotaoClicado(x, y) == btnReiniciar) {
                resetarJogo();
                estadoAtual = PLAYING;
            }
        }
    }
}

int main(void) {
    guiMenu = new GuiManager();
    btnIniciar = new Botao(screenWidth / 2.0f - 100.0f, screenHeight / 2.0f, 200.0f, 50.0f, "INICIAR JOGO");
    guiMenu->addBotao(btnIniciar);

    guiPause = new GuiManager();
    btnContinuar = new Botao(screenWidth / 2.0f - 100.0f, screenHeight / 2.0f - 30.0f, 200.0f, 50.0f, "CONTINUAR");
    btnSair = new Botao(screenWidth / 2.0f - 100.0f, screenHeight / 2.0f + 40.0f, 200.0f, 50.0f, "SAIR");
    guiPause->addBotao(btnContinuar);
    guiPause->addBotao(btnSair);

    guiGameOver = new GuiManager();
    btnReiniciar = new Botao(screenWidth / 2.0f - 100.0f, screenHeight / 2.0f, 200.0f, 50.0f, "TENTAR NOVAMENTE");
    guiGameOver->addBotao(btnReiniciar);

    CV::init(&screenWidth, &screenHeight, "Trabalho 2 - Anthony Silva");
    CV::run();

    delete btnIniciar;
    delete btnContinuar;
    delete btnSair;
    delete btnReiniciar;
    delete guiMenu;
    delete guiPause;
    delete guiGameOver;
    delete player;
    delete armamento;
    delete horda;
    return 0;
}