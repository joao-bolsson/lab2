// Calculadora.hpp
// TAD que implementa uma calculadora
//
// The MIT License (MIT)
// 
// Copyright (c) 2016 João V. Lima, UFSM
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once 

#include <stack>

#include <iostream>
#include <math.h> 

using namespace std;

template<typename T>
struct Calculadora {
    // ver http://en.cppreference.com/w/cpp/container/stack
    std::stack<T> operandos; // números, basicamente
    std::stack<char> operadores; // operadores: +, -, /, *
    // podem incluir mais dados, se necessário

    // cria a calculadora

    void cria(void) {
    }

    // destroi a calculadora, limpa as pilhas

    void destroi(void) {
        while (operandos.empty() == false)
            operandos.pop();
        while (operadores.empty() == false)
            operadores.pop();
    }

    // insere um novo operando para o calculo

    void operando(T op) {
        operandos.push(op);
    }

    bool temPrecedencia(char opTopo, char opNovo) {
        char operador[] = {'+', '-', '*', '/', '^'};
        int iTopo = 0, iNovo = 0;
        for (int i = 0; i < 5; i++) {
            if (operador[i] == opTopo) {
                iTopo = i;
            }
            if (operador[i] == opNovo) {
                iNovo = i;
            }
        }
        if (iTopo > iNovo) {
            return true;
        }
        return false;
    }

    // insere um novo operador para o calculo (pode ser '+', '-', '*', '/', '^')
    // se for um abre parenteses '(' tudo ok. 
    // se for um fecha parenteses ')', deve-se calcular tudo dentro.

    void operador(char op) {
        if (operadores.empty()) {
            operadores.push(op);
            return;
        }
        if (op == ')') {
            while (operadores.top() != '(') {
                // pega o operador
                char operador = operadores.top();
                operadores.pop();
                // pega os dois ultimos operandos
                T a = operandos.top();
                operandos.pop();
                T b = operandos.top();
                operandos.pop();
                calcula(operador, a, b);
            }
            operadores.pop();
        } else if (op != '(') {
            // pega o operador
            char opTopo = operadores.top();
            if (temPrecedencia(opTopo, op)) {
                // pega o operador
                char operador = operadores.top();
                operadores.pop();
                // pega os dois ultimos operandos
                T a = operandos.top();
                operandos.pop();
                T b = operandos.top();
                operandos.pop();
                calcula(operador, a, b);
            }
            operadores.push(op);
        } else {
            operadores.push(op);
        }
    }

    void calcula(char operador, T a, T b) {
        float result = 0;
        if (operador == '+') {
            result = soma(a, b);
        } else if (operador == '*') {
            result = multiplica(a, b);
        } else if (operador == '/') {
            result = divide(a, b);
        } else if (operador == '-') {
            result = subtrai(a, b);
        } else if (operador == '^') {
            result = potencia(a, b);
        }
        cout << a << operador << b << ": " << result << endl;
        operando(result);
    }

    float potencia(float a, float b) {
        return pow(b, a);
    }

    float divide(float a, float b) {
        return a / b;
    }

    float multiplica(float a, float b) {
        return a * b;
    }

    float subtrai(float a, float b) {
        return a - b;
    }

    float soma(float a, float b) {
        return a + b;
    }

    // finaliza o calculo, retorna false se erro detectado

    bool fim() {
        int i = 0;
        // limita o while - evita loop infinito
        while (operadores.size() > 0 && i < 10) {
            // pega o operador
            char operador = operadores.top();
            operadores.pop();
            // pega os dois ultimos operandos
            T a = operandos.top();
            operandos.pop();
            T b = operandos.top();
            operandos.pop();
            calcula(operador, a, b);
            i++;
        }
        return operadores.empty();
    }

    // retorna o resultado calculo (topo da pilha de operandos)
    // esse resultado sera parcial se ainda nao foi chamado calc_fim().

    T resultado(void) {
        return operandos.top();
    }
};
