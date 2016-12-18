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

int main() {
    Calculadora<float> calc;
    float x;

    string expressao("5*(((9+8)*(4*6))+7)");

    calc.operador('(');
    calc.operando(3.0);
    calc.operador('+');
    calc.operando(6.0);
    calc.operador(')');

    if (!calc.fim()) {
        cout << "ERRO: formula errada!" << endl;
    }
    x = calc.resultado();
    cout << "EXEMPLO: (3+6) = " << x << endl;
    calc.destroi();
    return 0;
}