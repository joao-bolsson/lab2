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

int main() {
    Calculadora<float> calc;
    float x;

    calc.operador('(');
    calc.operando(3.0);
    calc.operador('+');
    calc.operando(6.0);
    calc.operador(')');

    if (!calc.fim()) {
        std::cout << "ERRO: formula errada!" << std::endl;
    }
    x = calc.resultado();
    std::cout << "EXEMPLO: (3+6) = " << x << std::endl;
    calc.destroi();
    return 0;
}