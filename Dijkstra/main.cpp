/**
 * Implementado no NetBeans 8.2, compilado com:
 * 
 * make -f Makefile CONF=Debug (raiz do projeto)
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

    void dijkstra(const int fonte) {
        for (map<int, Vertice>::iterator it = begin(grafo); it != end(grafo); ++it) {
            // inicianliza todos os vertices com chave infinita
            it->second.chave = std::numeric_limits<float>::infinity();
        }
        // cria heap minimo
        auto compara = [](Vertice* v1, Vertice * v2) {
            return v1->chave > v2->chave;
        };
        Heap < Vertice*, decltype(compara) > heap(compara);

        grafo[fonte].chave = 0;
        // insere todos os vertices do grafo na heap
        for (auto& i : grafo) {
            heap.insere(&i.second);
        }
        // atualiza a heap
        heap.atualiza();

        while (!heap.vazio()) {
            auto u = heap.topo();
            for (auto a = u->aresta.begin(); a != u->aresta.end(); a++) {
                if (grafo[a->v].chave > u->chave + a->peso) {
                    grafo[a->v].anterior = u->info;
                    grafo[a->v].chave = u->chave + a->peso;
                }
            }
            heap.remove();
            heap.atualiza();
        }
    }

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

