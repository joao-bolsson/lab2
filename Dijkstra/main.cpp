/**
 *
 * @author João Bolsson (jvmarques@inf.ufsm.br)
 * @since 2016, 28 Nov.
 */

#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <functional>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Aresta {
    int v;
    float peso;
};

struct Vertice {
    int info; // valor do vertice
    float chave; // chave usada no heap
    int anterior; // quem é o anterior (Dijkstra)
    list<Aresta> aresta;
};

template<typename T, typename C>
struct Heap {
    vector<T> dado; // vetor do heap
    C compara; // funcao para comparar elementos

    // inicia o Heap com funcao de comparacao

    Heap(C cmp) : compara(cmp) {
    }

    // insere sem atualizao o heap

    void insere(T v) {
        dado.push_back(v);
    }

    void remove() {
        pop_heap(dado.begin(), dado.end(), compara);
        dado.pop_back();
    }

    // retorna o menor elemento

    T topo() {
        return dado.front();
    }

    bool vazio() {
        dado.empty();
    }

    void atualiza() {
        make_heap(dado.begin(), dado.end(), compara);
    }
};

struct Grafo {
    int nvertices, narestas;
    map<int, Vertice> grafo;

    void inicia(const char* arquivo) {
        ifstream entrada{arquivo};

        if (!entrada.is_open()) {
            throw runtime_error{"ERRO nao foi possivel abrir o arquivo"};
        }
        entrada >> nvertices;
        entrada >> narestas;

        // cria os vertices
        string chave, nome;
        for (auto v = 0; v < nvertices; v++) {
            grafo[v] = Vertice();
            grafo[v].info = v;
        }

        int v1, v2;
        float peso;
        for (auto i = 0; i < narestas; i++) {
            entrada >> v1;
            entrada >> v2;
            entrada >> peso;
            grafo[v1].aresta.push_back(Aresta{v2, peso});
            grafo[v2].aresta.push_back(Aresta{v1, peso});
        }
        entrada.close();
    }

    void dijkstra(const int fonte, Grafo g) {
        // TODO: implementar
        // inicializa todos os vertices do grafo com chave infinita
        g.nvertices = numeric_limits<float>::max();
	// todos os vertices com peso maximo e a fonte com 0
        // cria heap minimo
        auto compara = [](Vertice* v1, Vertice * v2) {
            return v1->chave > v2->chave;
        };
        Heap < Vertice*, decltype(compara) > heap(compara);
        //inseretodos os vértices de G no heap
        for (auto it = begin(g.grafo); it != end(g.grafo); it++) {
            heap.insere(it->second);
        }
	// atualizar
        while (!heap.vazio()) {
            auto u = heap.topo();
            // depois que pega, remover o topo
        }
    }

    /*
     // recebe o grafo, o vertice de fonte 'fonte'
void dijkstra(Grafo G, fonte){
  inicializa todos vertices do grafo G com chave infinita
  cria heap mínimo H 
  inicia chave da fonte com valor 0
  insere todos os vértices de G no heap 
  
  while( heap H não é vazio ){
      u = retira do heap H o vértice mínimo  (ou topo)
      for( cada vértice adjacente v de u ) {
        if( é possível melhorar o caminho entre (u,v) ? (v->chave > u->chave + a->peso) ){
          v->ant = u
          Coloca u como vértice anterior a v 
          Atualiza chave de v com peso de a mais chave de u (u->chave + a->peso)
          atualiza o heap com a chave nova de v 
        }
      }
  }
}
     */

    void imprime() {
        for (const auto& v : grafo) {
            cout << v.first << " -> ";
            for (const auto& a : v.second.aresta) {
                cout << a.v << "(" << a.peso << ")";
            }
            cout << endl;
        }
    }

    void caminho_minimo(int u, int v) {
        if (u == v) {
            cout << grafo[u].info << " ";
            return;
        }

        if (grafo[v].anterior == -1) {
            cout << "ERRO: caminho nao existe!" << endl;
        } else {
            caminho_minimo(u, grafo[v].anterior);
            cout << grafo[v].info << " ";
        }
    }

    void teste(int u, int v) {
        cout << "Gerando caminho minimo por Dijkstra (fonte: " << u << ")" << endl;
        dijkstra(u);
        cout << "Caminho minimo entre u e v (" << u << " -> " << v << ")" << endl;
        caminho_minimo(u, v);
        cout << endl;
    }
};

/*
 * 
 */
int main(int argc, char** argv) {
    Grafo g;

    if (argc > 1) {
        g.inicia(argv[1]);
        cout << "Grafo de entrada: " << endl;
        g.imprime();
        cout << endl;
        g.teste(5, 6);
        g.teste(4, 3);
        g.teste(4, 6);
    }

    return 0;
}

