// editor.cpp
// Arquivo com funções da estrutura Cobra
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
#include <memory>
#include <chrono>
#include <random>

#include "cobra.hpp"
#include "Tela.hpp"

// Utiliza as funções de tela
using namespace tela;

// estruturas geométicas
using namespace geom;

// elimina uso de std::
using namespace std;

bool pausa = false;

void Cobra::inicia(const int x, const int y)
{
  // esta função está pronta (pode ser alterada)
  tela.inicia(600, 400, "Jogo da Cobra");

  // apenas calcula o tamanho de uma letra em pixels
  const char* texto { "A" } ;
  fonte = tela.tamanho_texto(texto);

  // tamanho de um pedaço
  tam.larg = 10;
  tam.alt = 10;

  Pedaco* pcs = new Pedaco;
  pcs->p.x = x;
  pcs->p.y = y;
  pcs->cor = {0.0, 0.0, 0.0}; // inicia com cor preta
  pcs->dir = Direcao::direita;
  pedacos.push_front(pcs);
  // direção inicial
  dir = Direcao::direita;

  // inicia o tempo
  crono_mov = std::chrono::system_clock::now();
  crono_insere = std::chrono::system_clock::now();

  // calcula tempo dado uma frequencia (Hz): 4x por segundo
  t_mov = std::chrono::microseconds(int(1000000/4));
  // tempo para inserção de novos pedaços
  t_insere = std::chrono::seconds(1);
}

void Cobra::destroi(void)
{
  /// limpa a lista
  while(pedacos.size() > 0) {
    pedacos.pop_back();
  }
  tela.finaliza();
}

void Cobra::desenha(void)
{
  // Função pronta
  // primeiro, limpamos a tela
  tela.limpa();

  // Laço for do c++11 sobre uma lista
  for(auto psc : pedacos){
    Retangulo r;
    r.pos = psc->p;
    r.tam = tam;
    tela.cor(psc->cor);
    tela.retangulo(r);
  }
}

void Cobra::atualiza(void)
{
  // Função pronta (se quiser, alterar)
  /// if adicionado em caso de pausa
  if (!pausa) {
    insere();
    movimenta();
  }

  desenha();
  tela.mostra();
  tela.espera(30);
}

void Cobra::insere(void)
{
  // TODO terminar
  auto t_agora = std::chrono::system_clock::now();

  // conta quanto tempo passou e converte para milisegundos
  auto t_passado = std::chrono::duration_cast<std::chrono::milliseconds>(t_agora - crono_insere);
  if(t_passado > t_insere) {
    // insere novo pedaço aqui
    Pedaco* pcs = new Pedaco;
    pcs->p.x = pedacos.front()->p.x;
    pcs->p.y = pedacos.front()->p.y;
    srand((unsigned)time(NULL));
    /// 155 para evitar cores muito claras
    float r = (1 + (rand() % 155)) * 0.01;
    float g = (1 + (rand() % 155)) * 0.01;
    float b = (1 + (rand() % 155)) * 0.01;
    pcs->cor = {r, g, b}; /// inicia com uma cor aleatória
    pcs->dir = dir;
    pedacos.push_front(pcs);
    crono_insere = t_agora;
  }

}

void Cobra::dobra(Direcao _dir)
{
  if (dir == Direcao::direita || dir == Direcao::esquerda) {
    /// só pode mover para cima ou para baixo
    if (_dir == Direcao::cima || _dir == Direcao::baixo) {
      dir = _dir;
      pedacos.front()->dir = dir;
    }
  } else if (dir == Direcao::baixo || dir == Direcao::cima) {
    /// só pode mover para direita ou esquerda
    if (_dir == Direcao::direita || _dir == Direcao::esquerda) {
      dir = _dir;
      pedacos.front()->dir = dir;
    }
  }
}

void Cobra::movimenta(void)
{
  if( tempo_movimenta() == false ) {
    return;
  }
  if (dir == Direcao::esquerda) {
    pedacos.front()->p.x -= tam.larg;
  } else if (dir == Direcao::direita) {
    pedacos.front()->p.x += tam.larg;
  } else if (dir == Direcao::cima) {
    pedacos.front()->p.y -= tam.alt;
  } else {
    pedacos.front()->p.y += tam.alt;
  }
  pedacos.front()->dir = dir;
  if (pedacos.front()->p.x >= tela.tam.larg
    || pedacos.front()->p.x <= -tam.larg
    || pedacos.front()->p.y >= tela.tam.alt
    || pedacos.front()->p.y <= -tam.alt) {
    destroi();
    return;
  }
  Pedaco* next = new Pedaco;
  Pedaco* prev = new Pedaco;

  next->p = pedacos.front()->p;
  next->dir = dir;

  /// percorrendo a lista com os pedaços
  for(auto it = begin(pedacos); it != end(pedacos); it++) {
    Pedaco* ped = *it;

    /// o anterior recebe a posição do iterador
    prev->p = ped->p;
    /// o iterador recebe a posição do proximo
    ped->p = next->p;
    /// o proximo recebe a antiga posição do iterador
    next->p = prev->p;
    /// o anterior recebe a direção do atual
    prev->dir = ped->dir;
    /// o atual recebe a direção do proximo
    ped->dir = next->dir;
    /// o proximo recebe a direção do anterior
    next->dir = prev->dir;
  }
}
bool Cobra::tempo_movimenta(void)
{
  auto crono_agora = std::chrono::system_clock::now();

  // conta quanto tempo passou e converte para milisegundos
  auto t_passado = std::chrono::duration_cast<std::chrono::milliseconds>(crono_agora - crono_mov);

  // se passou meio segundo ?
  if(t_passado > t_mov) {
    crono_mov = std::chrono::system_clock::now();
    return true;
  }
  return false;
}

bool Cobra::processa_comandos(void)
{
  // Função pronta.
  int tecla = tela.tecla();
  /* apertou Q ? */
  if( tecla == ALLEGRO_KEY_Q ){
    cout << "SAIR\n";
    return false;
  }
  /// trecho adicionado para função de pausa
  if (tecla == ALLEGRO_KEY_P) {
    pausa = !pausa;
    return true;
  }
  if( tecla == ALLEGRO_KEY_LEFT )
    dobra(Direcao::esquerda);
  else if( tecla == ALLEGRO_KEY_RIGHT )
    dobra(Direcao::direita);
  else if( tecla == ALLEGRO_KEY_UP )
    dobra(Direcao::cima);
  else if( tecla == ALLEGRO_KEY_DOWN )
    dobra(Direcao::baixo);

  return true;
}
