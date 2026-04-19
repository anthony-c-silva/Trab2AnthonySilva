#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "Vector2.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int screenWidth = 500, screenHeight = 500;
int opcao = 51;
int mouseX, mouseY;

Vector2 rectPos(250.0f, 250.0f);
float rectAngulo = 0.0f;
float rectVelocidade = 10.0f;
float rectVelRotacao = 0.1f;

void render()
{
    if (opcao == 49)
    {
        CV::clear(1.0f, 1.0f, 1.0f);

        Vector2 centro((float)screenWidth / 2.0f, (float)screenHeight / 2.0f);
        Vector2 ref(150.0f, 0.0f);

        CV::color(1.0f, 0.0f, 0.0f);
        Vector2 pontaRef = centro + ref;
        CV::line(centro, pontaRef);

        Vector2 mousePos((float)mouseX, (float)mouseY);
        Vector2 vetorMouse = mousePos - centro;

        CV::color(0.0f, 0.0f, 1.0f);
        CV::line(centro, mousePos);

        float anguloRad = atan2f(vetorMouse.y, vetorMouse.x);
        float anguloDeg = anguloRad * 180.0f / PI;

        if (anguloDeg < 0) {
            anguloDeg += 360.0f;
        }

        char texto[100];
        sprintf(texto, "Angulo: %.3f", anguloDeg);
        CV::color(0.0f, 0.0f, 0.0f);
        CV::text(20, 20, texto);

        if (vetorMouse.length() > 0)
        {
            Vector2 direcao = vetorMouse;
            direcao.normalize();

            Vector2 p1(
                mousePos.x - direcao.x * 20 - direcao.y * 10,
                mousePos.y - direcao.y * 20 + direcao.x * 10
            );
            Vector2 p2(
                mousePos.x - direcao.x * 20 + direcao.y * 10,
                mousePos.y - direcao.y * 20 - direcao.x * 10
            );

            float vx[3] = { mousePos.x, p1.x, p2.x };
            float vy[3] = { mousePos.y, p1.y, p2.y };
            CV::triangleFill(vx, vy);
        }
    }

    if (opcao == 50)
    {
        CV::clear(1.0f, 1.0f, 1.0f);

        Vector2 vOriginal[4];
        vOriginal[0].set(-50.0f, -25.0f);
        vOriginal[1].set(50.0f, -25.0f);
        vOriginal[2].set(50.0f, 25.0f);
        vOriginal[3].set(-50.0f, 25.0f);

        float vx[4], vy[4];

		//calcula os angulos uma vez fora do loop para otimizar o codigo ja que todos os vertices usam o mesmo angulo
        float cosseno = cosf(rectAngulo);
        float seno = sinf(rectAngulo);

		//rotaciona os vertices do retangulo usando a formula de rotacao 2D: x' = x * cos(theta) - y * sin(theta) | y' = x * sin(theta) + y * cos(theta)
        for (int i = 0; i < 4; i++)
        {
            float rx = vOriginal[i].x * cosseno - vOriginal[i].y * seno;
            float ry = vOriginal[i].x * seno + vOriginal[i].y * cosseno;

            vx[i] = rx + rectPos.x;
            vy[i] = ry + rectPos.y;
        }


		//desenha o retangulo usando os vertices rotacionados
        CV::color(0.0f, 0.0f, 0.0f);
        CV::text(20, 40, "Setas: Mover | Espaco: Girar");
        CV::text(20, 20, "Tecla 1 ou 2 para trocar exercicio");
        CV::color(0.0f, 0.5f, 0.0f);
        CV::polygon(vx, vy, 4);

		//desenha a linha de direcao do retangulo
        Vector2 dir(cosseno, seno);
        CV::color(1.0f, 0.0f, 0.0f);
        CV::line(rectPos, rectPos + (dir * 60.0f));
    }
    if(opcao == 51)
    {
        CV::clear(1.0f, 1.0f, 1.0f);

        Vector2 vOriginal[4];
        vOriginal[0].set(-100.0f, -25.0f);
        vOriginal[1].set(50.0f, -25.0f);
        vOriginal[2].set(50.0f, 25.0f);
        vOriginal[3].set(-50.0f, 25.0f);

        float vx[4], vy[4];

        //calcula os angulos uma vez fora do loop para otimizar o codigo ja que todos os vertices usam o mesmo angulo
        float cosseno = cosf(rectAngulo);
        float seno = sinf(rectAngulo);

        for (int i = 0; i < 4; i++)
        {
            float rx = vOriginal[i].x * cosseno - vOriginal[i].y * seno;
            float ry = vOriginal[i].x * seno + vOriginal[i].y * cosseno;

            vx[i] = rx + rectPos.x;
            vy[i] = ry + rectPos.y;
        }


        //desenha o retangulo usando os vertices rotacionados
        CV::color(0.0f, 0.0f, 0.0f);
        CV::text(20, 40, "Setas: Mover | Espaco: Girar");
        CV::text(20, 20, "Tecla 1 ou 2 para trocar exercicio");
        CV::color(0.0f, 0.5f, 0.0f);
        CV::polygon(vx, vy, 4);

        //desenha a linha de direcao do retangulo
        Vector2 dir(cosseno, seno);
        CV::color(1.0f, 0.0f, 0.0f);
        CV::line(rectPos, rectPos + (dir * 60.0f));

     
	}

    Sleep(10);
}

void keyboard(int key)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 49:
    case 50:
    case 51:
        opcao = key;
        break;
    case 201: // Seta Cima
        rectPos.y += rectVelocidade;
        break;
    case 203: // Seta Baixo
        rectPos.y -= rectVelocidade;
        break;
    case 200: // Seta Esquerda
        rectPos.x -= rectVelocidade;
        break;
    case 202: // Seta Direita
        rectPos.x += rectVelocidade;
        break;
    case 32: // Espaco
        rectAngulo += rectVelRotacao;
        break;
    }
}

void keyboardUp(int key)
{
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    mouseX = x;
    mouseY = y;
}

int main(void)
{
    CV::init(&screenWidth, &screenHeight, "Exercicios - Digite 1 OU 2");
    CV::run();
}