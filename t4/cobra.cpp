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
  t_insere = std::chrono::seconds(2);
}

void Cobra::destroi(void)
{
  // TODO terminar
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
  movimenta();
  insere();
  
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
  }
}

void Cobra::dobra(Direcao _dir)
{
  dir = _dir;
}

void Cobra::movimenta(void)
{
  if( tempo_movimenta() == false )
    return;
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
  int modificador = tela.tecla_modif();
  /* apertou CRTL + Q ? */
  if( tecla == ALLEGRO_KEY_Q ){
    std::cout << "SAIR\n";
    return false;
  }

  /* teclas direcionais 
     ALLEGRO_KEY_LEFT
     ALLEGRO_KEY_RIGHT
     ALLEGRO_KEY_UP
     ALLEGRO_KEY_DOWN
  */
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
