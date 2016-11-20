#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <vector>

using namespace std;

struct Vertice {
  string nome;
  list<string> adj;
};

bool isValidChar(char c) {
  /// aspas simples e hifen deixados propositalmente
  char forbiddenChars[]  = {'!', '"', '#', '$', '%', '&', '*',
    '(', ')', ',', '.', ':', ';', '+', '=', '{', '}', '[', ']', '`', '?'};
  int len = sizeof(forbiddenChars)/sizeof(forbiddenChars[0]);
  for (int i = 0; i < len; i++) {
    if (c == forbiddenChars[i]) {
      return false;
    }
  }
  return true;
}

const vector<string> explode(const string& s, const char& c) {
  string buff{""};
  vector<string> v;

  for(auto n:s) {
    if (isValidChar(n)) {
      if(n != c) buff+=n; else
      if(n == c && buff != "") {
        v.push_back(buff);
        buff = "";
      }
    }
  }
  if(buff != "") v.push_back(buff);

  return v;
}

int getInt(string str_num) {
  char char_num[str_num.size()];
  int i = 0;
  for (auto c:str_num) {
    if (c >= '0' && c <= '9') {
      char_num[i] = c;
    }
    i++;
  }
  return atoi(char_num);
}

map<string, Vertice> le_arquivo(const char* nome) {
  map<string, Vertice> grafo;
  string line;
  ifstream myfile (nome);
  if (myfile.is_open()) {
    int num_vertices = -1, count_vertices = 0;
    while(!myfile.eof()) {
      getline (myfile,line);
      if (line.size() > 0) {
        vector<string> v{explode(line, ' ')};
        if (num_vertices < 0) {
          num_vertices = getInt(v[0]);
          if (num_vertices < 1) return grafo;
        } else if (count_vertices < num_vertices) {
          string nome = "";
          for (int unsigned i = 1; i < v.size(); i++) {
            nome += v[i] + " ";
          }
          grafo[v[0]] = Vertice();
          grafo[v[0]].nome = string{nome};
          count_vertices++;
        } else {
          grafo[v[0]].adj.push_back(v[1]);
          grafo[v[1]].adj.push_back(v[0]);
        }
      }
    }

    myfile.close();
  } else {
    cout << "Erro ao abrir o arquivo" << endl;
  }

  return grafo;
}

void mostraGrafo(map<string, Vertice> grafo) {
	for(auto it = begin(grafo); it != end(grafo); ++it) {
		cout << it->first << " -> ";
		list<string> lista = it->second.adj;
		for (auto it = lista.begin(); it != lista.end(); it++) {
      cout << (*it) << ' ';
		}
		cout << '\n';
  }
}

int main(int argc, char **argv)
{
  if (argc < 2) {
    cout << "Insira o caminho do arquivo\nABORTADO" << endl;
    return 0;
  }

  const char* path = argv[1];

  // Definicao do grafo: string -> Vertice
  map<string, Vertice> grafo = le_arquivo(path);
  mostraGrafo(grafo);
  grafo.clear();
  return 0;
}
