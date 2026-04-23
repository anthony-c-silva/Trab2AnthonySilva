// Aluno: Anthony Silva

#include "gui.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

Botao::Botao(float _x, float _y, float _larg, float _alt, const char* _label) {
    x = _x;
    y = _y;
    largura = _larg;
    altura = _alt;
    strcpy(label, _label);
}

void Botao::render() {
    CV::color(0.7f, 0.7f, 0.7f);
    CV::rectFill(x, y, x + largura, y + altura);
    CV::color(0.0f, 0.0f, 0.0f);
    CV::rect(x, y, x + largura, y + altura);

    int tamanhoTextoPixel = strlen(label) * 8;
    float centroX = x + (largura / 2.0f) - (tamanhoTextoPixel / 2.0f);
    float centroY = y + (altura / 2.0f) + 5.0f;

    CV::text(centroX, centroY, label);
}

bool Botao::colide(int mx, int my) {
    return (mx >= x && mx <= x + largura && my >= y && my <= y + altura);
}

Checkbox::Checkbox(float _x, float _y, float _tam, const char* _label, bool _ativoInicio) {
    x = _x;
    y = _y;
    tamanho = _tam;
    ativo = _ativoInicio;
    strcpy(label, _label);
}

void Checkbox::render() {
    CV::color(1.0f, 1.0f, 1.0f);
    CV::rectFill(x, y, x + tamanho, y + tamanho);
    CV::color(0.0f, 0.0f, 0.0f);
    CV::rect(x, y, x + tamanho, y + tamanho);

    if (ativo) {
        CV::line(x, y, x + tamanho, y + tamanho);
        CV::line(x + tamanho, y, x, y + tamanho);
    }
    CV::text(x + tamanho + 8, y + tamanho / 2 + 4, label);
}

bool Checkbox::colide(int mx, int my) {
    return (mx >= x && mx <= x + tamanho && my >= y && my <= y + tamanho);
}

void Checkbox::inverte() {
    ativo = !ativo;
}

bool Checkbox::isAtivo() {
    return ativo;
}

Slider::Slider(float _x, float _y, float _larg, float _alt) {
    x = _x;
    y = _y;
    largura = _larg;
    altura = _alt;
    valor = 0.5f;
    arrastando = false;
}

void Slider::render() {
    CV::color(0.4f, 0.4f, 0.4f);
    CV::rectFill(x, y + altura / 2 - 2, x + largura, y + altura / 2 + 2);

    float pinoX = x + (valor * largura);
    CV::color(0.2f, 0.2f, 0.8f);
    CV::rectFill(pinoX - 5, y, pinoX + 5, y + altura);
}

bool Slider::colidePino(int mx, int my) {
    float pinoX = x + (valor * largura);
    return (mx >= pinoX - 10 && mx <= pinoX + 10 && my >= y - 5 && my <= y + altura + 5);
}

void Slider::setArrastando(bool v) {
    arrastando = v;
}

bool Slider::isArrastando() {
    return arrastando;
}

void Slider::atualiza(int mx) {
    if (!arrastando) return;

    valor = (float)(mx - x) / largura;

    if (valor < 0.0f) valor = 0.0f;
    if (valor > 1.0f) valor = 1.0f;
}

float Slider::getValor() {
    return valor;
}

void Slider::setValor(float v) {
    valor = v;
    if (valor < 0.0f) valor = 0.0f;
    if (valor > 1.0f) valor = 1.0f;
}

GuiManager::GuiManager() {
    nBotoes = 0;
    nCheckboxes = 0;
    nSliders = 0;
}

void GuiManager::addBotao(Botao* b) {
    if (nBotoes < 20) botoes[nBotoes++] = b;
}

void GuiManager::addCheckbox(Checkbox* c) {
    if (nCheckboxes < 20) checkboxes[nCheckboxes++] = c;
}

void GuiManager::addSlider(Slider* s) {
    if (nSliders < 20) sliders[nSliders++] = s;
}

void GuiManager::renderAll() {
    for (int i = 0; i < nBotoes; i++) botoes[i]->render();
    for (int i = 0; i < nCheckboxes; i++) checkboxes[i]->render();
    for (int i = 0; i < nSliders; i++) sliders[i]->render();
}

Botao* GuiManager::getBotaoClicado(int mx, int my) {
    for (int i = 0; i < nBotoes; i++) {
        if (botoes[i]->colide(mx, my)) return botoes[i];
    }
    return NULL;
}

Checkbox* GuiManager::getCheckboxClicado(int mx, int my) {
    for (int i = 0; i < nCheckboxes; i++) {
        if (checkboxes[i]->colide(mx, my)) return checkboxes[i];
    }
    return NULL;
}

Slider* GuiManager::getSliderClicado(int mx, int my) {
    for (int i = 0; i < nSliders; i++) {
        if (sliders[i]->colidePino(mx, my)) return sliders[i];
    }
    return NULL;
}

void GuiManager::atualizaSlidersArrastados(int mx) {
    for (int i = 0; i < nSliders; i++) {
        if (sliders[i]->isArrastando()) sliders[i]->atualiza(mx);
    }
}

void GuiManager::soltaSliders() {
    for (int i = 0; i < nSliders; i++) {
        sliders[i]->setArrastando(false);
    }
}

bool GuiManager::isAlgumSliderArrastando() {
    for (int i = 0; i < nSliders; i++) {
        if (sliders[i]->isArrastando()) return true;
    }
    return false;
}