#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

#include <math.h>
#include <stdio.h>

class Vector2
{
public:
    float x, y;

    Vector2()
    {
        x = y = 0;
    }

    Vector2(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    void set(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    void normalize()
    {
        float norm = (float)sqrt(x * x + y * y);

        if (norm == 0.0)
        {
            x = 1;
            y = 1;
            return;
        }
        x /= norm;
        y /= norm;
    }

    Vector2 operator - (const Vector2& v)
    {
        Vector2 aux(x - v.x, y - v.y);
        return(aux);
    }

    Vector2 operator + (const Vector2& v)
    {
        Vector2 aux(x + v.x, y + v.y);
        return(aux);
    }

    // Multiplicacao por escalar: Pega o vetor e aumenta seu tamanho por um numero X (fator).
    // O vetor continua apontando para a mesma direcao, apenas fica mais comprido ou invertido se for numero negativo.
    Vector2 operator * (float s)
    {
        return Vector2(x * s, y * s);
    }

    // Divisao por escalar: O inverso da multiplicacao. Reduz o tamanho do vetor sem alterar sua direcao.
    Vector2 operator / (float s)
    {
        return Vector2(x / s, y / s);
    }

    // Produto Escalar (Dot Product): Multiplica o X com o X do outro vetor, o Y com o Y e soma tudo em um unico numero.
    //operacao muito importante na computacao grafica para saber se dois vetores estao apontando para o mesmo lado.
    float dot(const Vector2& v)
    {
        return x * v.x + y * v.y;
    }

    // Magnitude (Tamanho/Length): Usa o teorema de Pitagoras (a^2 + b^2 = c^2) para calcular
    // exatamente qual e o tamanho da reta do vetor, do ponto 0 ate a ponta dele.
    float length()
    {
        return (float)sqrt(x * x + y * y);
    }
};

#endif