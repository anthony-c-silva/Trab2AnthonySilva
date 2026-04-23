#ifndef GUI_H
// Aluno: Anthony Silva

#define GUI_H

#include "gl_canvas2d.h"
#include <string.h>

class Botao {
private:
    float x, y, largura, altura;
    char label[100];

public:
    Botao(float _x, float _y, float _larg, float _alt, const char* _label);
    void render();
    bool colide(int mx, int my);
};

class Checkbox {
private:
    float x, y, tamanho;
    char label[100];
    bool ativo;

public:
    Checkbox(float _x, float _y, float _tam, const char* _label, bool _ativoInicio = false);
    void render();
    bool colide(int mx, int my);
    void inverte();
    bool isAtivo();
};

class Slider {
private:
    float x, y, largura, altura, valor;
    bool arrastando;

public:
    Slider(float _x, float _y, float _larg, float _alt);
    void render();
    bool colidePino(int mx, int my);
    void atualiza(int mx);
    void setArrastando(bool v);
    bool isArrastando();
    float getValor();
    void setValor(float v);
};

class GuiManager {
private:
    Botao* botoes[20];
    Checkbox* checkboxes[20];
    Slider* sliders[20];
    int nBotoes, nCheckboxes, nSliders;

public:
    GuiManager();
    void addBotao(Botao* b);
    void addCheckbox(Checkbox* c);
    void addSlider(Slider* s);

    void renderAll();

    Botao* getBotaoClicado(int mx, int my);
    Checkbox* getCheckboxClicado(int mx, int my);
    Slider* getSliderClicado(int mx, int my);

    void atualizaSlidersArrastados(int mx);
    void soltaSliders();
    bool isAlgumSliderArrastando();
};

#endif