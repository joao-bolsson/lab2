/**
* ======================================================================
*
* João Víctor Bolsson Marques           201610816
*
* Trabalho 2 da disciplina de Laboratório de Programação II
* O Programa lê um arquivo .txt e imprime na tela.
*
* compilado com:
* g++ -std=c++11 -std=c++0x -O2 -Wall -g -o main main.cpp
*
* São aceitos os seguintes comandos:
*
* q -> Sai do editor
* w -> Move para cima (scroll)
* s -> Move para baixo (scroll)
*
* ======================================================================
*/
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
/// elimina o uso do std:: no código
using namespace std;

struct Editor {
  char *nome;     // nome do arquivo de entrada
  char **linhas;  // as linhas do texto
  int nlinhas;    // total de linhas do texto
  int lin1;       // linha do texto na 1a linha da tela
  int col1;       // coluna do texto na 1a coluna da tela
  int lin2;       // linha do texto na última linha da tela
  int col2;       // coluna do texto na última coluna da tela

  void limpa_tela()
  {
    #if defined(__linux__)
    system("clear");
    #endif
  }
  // Abaixo estão as funções básicas do editor.
  // Se achar necessário, pode-se inserir outras funções.

  // inicia o editor
  void inicia(void)
  {
    nlinhas = 0;
    lin1 = 0;
    lin2 = 23;
  }

  // destroi o editor
  void destroi(void)
  {
    for(auto i = 0; i <= nlinhas; i++) delete[] linhas[i];
    delete[] linhas;
    limpa_tela();
    cout << "Editor destruído" << endl;
  }
  // desenha o texto na tela
  void desenha(void){
    limpa_tela();
    cout << "Linha 1: " << lin1 << " | Linha 2: " << lin2 << endl;
    for(int l= lin1; l < lin2; l++) {
      cout << linhas[l] << endl;
    }
  }

  // le um arquivo 'nome' e armazena na estrutura de dados
  void le_arquivo(const char* nome)
  {
    ifstream entrada {"entrada.txt"};
    string linha;
    linhas = new char*[100];
    while(!entrada.eof()) {
        getline(entrada, linha);
        linhas[nlinhas] = new char[linha.size() + 1];
        linha.copy(linhas[nlinhas], linha.size(), 0);
        linhas[nlinhas][linha.size()] = '\0';
        nlinhas++;
    }
    linhas[nlinhas] = nullptr;
  }

  // move o texto uma linha para cima
  void move_cima(void)
  {
    if(lin1 > 0){
      lin1--;
      lin2--;
    }
    desenha();
  }

  // move o texto uma linha para baixo
  void move_baixo(void)
  {
      if(lin2 < nlinhas){
        lin1++;
        lin2++;
      }
      desenha();
  }
};

#if defined(__linux__) || defined(__APPLE__)

#include <termios.h>

void termios_off(void)
{
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~ICANON;
  t.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void termios_on(void)
{
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag |= ICANON;
  t.c_lflag |= ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
#endif // __linux__

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#endif // WINDOWS

int main(void)
{
  char c;
  Editor ed;
  ed.inicia();
  ed.le_arquivo("entrada.txt");
  ed.desenha();
    #if defined(__linux__) || defined(__APPLE__)
    termios_off();
    #endif
  while(true) {
    #if defined(__linux__) || defined(__APPLE__)
    c = getchar();
    #elif defined(_WIN32) || defined(_WIN64)
    c = _getch();
    #endif
    if(c == 'q' || c == 'Q') break;
    // adicione outros comandos abaixo
    if(c == 'w') ed.move_cima();
    if(c == 's') ed.move_baixo();
  }
  #if defined(__linux__) || defined(__APPLE__)
  termios_on();
  #endif
  ed.destroi();
  return 0;
}
