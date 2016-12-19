/**
 * Implementado no NetBeans 8.2, compilado com:
 * 
 * make -f Makefile CONF=Debug (raiz do projeto)
 * 
 * @author João Bolsson (jvmarques@inf.ufsm.br)
 * @since 2016, 18 Dez.
 */

#include "Calculadora.hpp"
#include <iostream>

using namespace std;

float charToInt(char c) {
    if (c >= '0' && c <= '9') {
        float num = 0.0;
        for (int i = '0'; i <= '9'; i++) {
            if (c == i) {
                i = '9'; // achou
            } else {
                num++; // continua procurando
            }
        }
        return num;
    } else {
        return -1; // erro
    }
}

int main() {
    Calculadora<float> calc;
    float x;

//    string expressao("5*(((9+8)*(4*6))+7)");
//    int unsigned len = expressao.length();
//    for (int unsigned i = 0; i < len; i++) {
//        char ch = expressao.at(i);
//        if (ch >= '0' && ch <= '9' && ch == '5') {
//            // eh um numero
//            float num = charToInt(ch);
//            calc.operando(num);
//        } else {
//            calc.operador(ch);
//        }
//    }
//    cout << '\n';

    calc.operando(5.0);
    calc.operador('*');
    calc.operador('(');
    calc.operador('(');
    calc.operador('(');
    calc.operando(9.0);
    calc.operador('+');
    calc.operando(8.0);
    calc.operador(')');
    calc.operador('*');
    calc.operador('(');
    calc.operando(4.0);
    calc.operador('*');
    calc.operando(6.0);
    calc.operador(')');
    calc.operador(')');
    calc.operador('+');
    calc.operando(7.0);
    calc.operador(')');


    if (!calc.fim()) {
        cout << "ERRO: formula errada!" << endl;
    }
    x = calc.resultado();
    cout << "EXEMPLO: = " << x << endl;
    calc.destroi();
    return 0;
}