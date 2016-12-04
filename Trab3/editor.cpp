// editor.cpp
// Arquivo com funções da estrutura Editor
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
// The above copyright notice and this permission notice shall be included in
// all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>
#include <fstream>
#include <functional>
#include "editor.hpp"
#include "Tela.hpp"

#define LARG 600
#define ALT 400
// Utiliza as funções de tela
using namespace tela;
// Elimina o uso de std:: no código
using namespace std;
void Editor::inicia(void)
{
  // esta função está pronta
  tela.inicia(LARG, ALT, "Editor de texto");
  lin1 = 0;
  col1 = 0;
  col2 = 0;
  colcur = 0;
  lincur = 0;

  // apenas calcula o tamanho de uma letra em pixels
  const char* texto { "A" } ;
  fonte = tela.tamanho_texto(texto);
  /// mostra o texto que couber na janela
  lin2 = ALT / fonte.alt;
}

void Editor::destroi(void)
{
  // TODO terminar
  tela.finaliza();
}

void Editor::desenha(void)
{
  // TODO terminar
  Cor preto = {0.0, 0.0, 0.0};
  Ponto pt;

  // primeiro, limpamos a tela
  tela.limpa();
  // cor do texto é preta
  tela.cor(preto);
  for(auto i = lin1; i < lin2; i++) {
    // calcula posicao da nova linha
    pt.x = 1;
    pt.y = (i - lin1)*fonte.alt + 1;

    /* muda cor e desenha linha */
    tela.texto(pt, linhas[i].c_str());
  }

  // chama função para desenhar cursos no texto
  desenha_cursor();
}

void Editor::atualiza(void)
{
  // TODO terminar
  desenha();
  tela.mostra();
  tela.espera(30);
}

void Editor::desenha_cursor(void)
{
  Cor preto = {0.0, 0.0, 0.0};
  Ponto pt1, pt2;
  /* posicao x (horizontal) do cursor */
  pt1.x = fonte.larg*colcur + 1;
  /* posicao y (vertical) do cursor */
  pt1.y = lincur * fonte.alt;
  pt2.x = pt1.x;
  pt2.y = pt1.y + fonte.alt;
  tela.cor(preto);
  tela.linha(pt1, pt2);
}

bool Editor::processa_comandos(void)
{
  // TODO terminar, remove_char com backspace e delete
  int tecla = tela.tecla();
  int modificador = tela.tecla_modif();

  if( tecla == ALLEGRO_KEY_Q && (modificador & ALLEGRO_KEYMOD_CTRL) ) {
    std::cout << "CTRL+Q SAIR\n";
    return false;
  } else if( tecla == ALLEGRO_KEY_S && (modificador & ALLEGRO_KEYMOD_CTRL) ) {
    std::cout << "CTRL+S SALVAR e PARAR DE EDITAR\n";
    // muda estado na variável para não editar
    estado = Estado::nada;
    return true;
  } else if( tecla == ALLEGRO_KEY_E && (modificador & ALLEGRO_KEYMOD_CTRL) ) {
    std::cout << "CTRL+E EDITAR\n";
    // muda estado na variável para editando
    estado = Estado::editando;
    return true;
  } else if( tecla == ALLEGRO_KEY_J && (modificador & ALLEGRO_KEYMOD_CTRL) ) {
    std::cout << "CTRL+J GRUDAR (JUNTAR) LINHAS\n";
    // muda estado na variável para editando
    return true;
  } else if( tecla == ALLEGRO_KEY_N && (modificador & ALLEGRO_KEYMOD_CTRL) ) {
    std::cout << "CTRL+N QUEBRAR LINHAS\n";
    // muda estado na variável para editando
    return true;
  } else if( tecla == ALLEGRO_KEY_LEFT ) {
    move_esq();
    return true;
  } else if( tecla == ALLEGRO_KEY_RIGHT ) {
    move_dir();
    return true;
  } else if( tecla == ALLEGRO_KEY_UP ) {
    move_cima();
    return true;
  } else if( tecla == ALLEGRO_KEY_DOWN ) {
    move_baixo();
    return true;
  } else if( (tecla >= ALLEGRO_KEY_A)
      && (tecla <= ALLEGRO_KEY_Z)
      && estado == Estado::editando ) {
    insere_char(static_cast<char>(tecla + 96));
    return true;
  } else if ( (tecla == ALLEGRO_KEY_BACKSPACE)
      && estado == Estado:: editando) {
    remove_char();
    return true;
  }

  return true;
}

void Editor::le_arquivo(const char* nome)
{
  std::cout << __PRETTY_FUNCTION__ << " lendo arquivo: " << nome << "\n";

  string line;
  ifstream myfile (nome);
  if (myfile.is_open()) {
    while(!myfile.eof()) {
      getline (myfile,line);
      linhas.push_back(line);
    }
    myfile.close();
  } else {
    cout << "Erro ao abrir o arquivo" << endl;
  }
}

void Editor::move_cima(void)
{
  /// evita que o cursor se perca
  if (lincur == lin1 && lin1 != 0) {
    lin1--;
    lin2--;
  } else {
    lincur--;
  }
}

void Editor::move_baixo(void)
{
  /// evita que o cursor se perca
  if (lincur < linhas.size()) {
    lincur++;
    if (lincur == lin2) {
      lin1++;
      lin2++;
    }
  }
  /*
  /// se não tiver chegado no final do arquivo continua
  if (lincur == lin2 && lin2 < linhas.size()) {
    lin1++;
    lin2++;
  }
  */
}

void Editor::move_esq(void)
{
  if (colcur > 0) {
    colcur--;
  }
}

void Editor::move_dir(void)
{
  colcur++;
}

void Editor::insere_char(const char c)
{
  if(static_cast<int unsigned>(lincur) > linhas.size())
    return;
  std::string& linha = std::ref(linhas[lincur]);
  /// se o cursor estiver além do tamanho da linha insere espaços até chegar nele
  while (colcur > linhas.at(lincur).size()) {
    linha.insert(linhas.at(lincur).size(), 1, ' ');
  }
  linha.insert(colcur, 1, c);
  move_dir();
}

void Editor::remove_char(void)
{
  // TODO terminar
  int index = colcur - 1;
  if (colcur == 0) {
    return;
  }
  linhas.at(lincur).erase(index, 1);
  move_esq();
}

void Editor::gruda_linha(void)
{
  // TODO terminar
}

void Editor::quebra_linha(void)
{
  // TODO terminar
}

void Editor::salvar(void)
{
  // TODO terminar
}
