#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <list>
#include <vector>

using namespace std;


struct Posicao {
  int linha;
  int coluna;
};

struct Palavra {
  string palavra; // a palavra
  int contagem;        // palavras encontradas
  list<Posicao> lista; // lista com a posição de cada palavra
};

class No {
private:
	No *esq, *dir;
    Palavra palavra;

public:
	No(Palavra palavra) {
		this->palavra = palavra;
		esq = NULL;
		dir = NULL;
	}

	string toString() {
		return palavra.palavra;
	}

  int getContagem() {
    return palavra.contagem;
  }

	void updateContagem() {
    palavra.contagem++;
	}

	void updateLista(Posicao pos) {
    palavra.lista.push_back(pos);
	}

	void printLista() {
    cout << "(";
    for (auto it = palavra.lista.begin(); it != palavra.lista.end(); it++) {
      Posicao pos = *it;
      cout << pos.linha << ":" << pos.coluna << ", ";
    }
    cout << ")\n";
	}

	No* getEsq() {
		return esq;
	}

	No* getDir() {
		return dir;
	}

	void setEsq(No *no) {
		esq = no;
	}

	void setDir(No *no) {
		dir = no;
	}
};

class Arvore {
private:
	No *raiz;

	void inserirAux(No *no, Palavra chave) {
		if(chave.palavra < no->toString()) {
			// verifica se a esquerda é nulo
			if(no->getEsq() == NULL) {
				No *novo_no = new No(chave);
				no->setEsq(novo_no); // seta o novo_no à esquerda
			} else {
				// senão, continua percorrendo recursivamente
				inserirAux(no->getEsq(), chave);
			}
		} else if(chave.palavra > no->toString()) {
			// verifica se a direita é nulo
			if(no->getDir() == NULL) {
				No *novo_no = new No(chave);
				no->setDir(novo_no); // seta o novo_no à direita
			} else {
				// senão, continua percorrendo recursivamente
				inserirAux(no->getDir(), chave);
			}
		} else if (chave.palavra == no->toString()) {
      /// se a palavra já tiver na arvore, aumenta a contagem
      no->updateContagem();
      no->updateLista(chave.lista.back());
		}
		// se for igual, não vai inserir
		// não pode existir 2 chaves iguais
	}

public:
	Arvore() {
		raiz = NULL;
	}

	void inserir(Palavra chave) {
		if(raiz == NULL) // verifica se a árvore está vazia
			raiz = new No(chave); // cria um novo nó
		else
			inserirAux(raiz, chave);
	}

	No* getRaiz() {
		return raiz;
	}

	void emOrdem(No* no) {
    //Primeiro a sub-árvore esquerda, depois a raiz, e finalmente a sub-árvore direita
		if(no != NULL) {
			emOrdem(no->getEsq());
			cout << no->toString() << " " << no->getContagem();
			no->printLista();
			emOrdem(no->getDir());
		}
	}
};

const vector<string> explode(const string& s, const char& c)
{
	string buff{""};
	vector<string> v;

	for(auto n:s) {
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);

	return v;
}

Arvore le_arquivo(const char* nome) {
  Arvore arv;
  string line;
  ifstream myfile (nome);
  if (myfile.is_open()) {
    int line_cont = 1; /// contagem das linhas no arquivo
    while(!myfile.eof()) {
      getline (myfile,line);
      vector<string> v{explode(line, ' ')};
      int tam = v.size();
      Posicao pos;
      pos.linha = line_cont;
      pos.coluna = 1;
      for (int i = 0; i < tam; i++) {
        Palavra word;
        if (i != 0) {
          pos.coluna = v[i - 1].size() + 1;
        }
        word.palavra = v[i];
        word.contagem = 1;
        word.lista.push_back(pos);
        arv.inserir(word);
      }
      line_cont++;
    }
    myfile.close();
  } else {
    cout << "Erro ao abrir o arquivo" << endl;
  }
  return arv;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
    cout << "Insira o caminho do arquivo\nABORTADO\n" << endl;
    return 0;
  }

  const char* path = argv[1];
  Arvore arv = le_arquivo(path);
  if (arv.getRaiz() == NULL) {
    cout << "Ocorreu um erro na leitura do arquivo\n" << endl;
    return 0;
  }
	// percorre a árvore
	cout << "Percorrendo em ordem...\n";
	arv.emOrdem(arv.getRaiz());
	cout << '\n';
	return 0;
}
