#include <iostream>
#include <fstream>
#include <functional>
#include <stack>
#include <algorithm>

#define KEY_WORDS 4
using namespace std;

bool line_contains(string line, const char** keyWords) {
  for (auto i = 0; i < KEY_WORDS; i++) {
    if (keyWords[i] == line) {
      return true;
    }
  }
  return false;
}

void le_arquivo(const char* nome)
{
  stack<string> linhas;
  const char* keyWords[] = {"begin", "repeat", "case", "else"};
  string line;
  ifstream myfile (nome);
  if (myfile.is_open()) {
    while(!myfile.eof()) {
      getline (myfile,line);
      line.erase(remove(line.begin(), line.end(), ' '), line.end());
      line.erase(remove(line.begin(), line.end(), '\t'), line.end());
      if (line.size() >= 1) { /// apenas linhas com conteudo
        if (line_contains(line, keyWords)) {
          linhas.push(line);
        } else if (line.at(line.size() - 1) == ';' && line != "end;") {
          /// ignora
        } else if (line == "end" && linhas.top() == "begin") {
          linhas.pop();
        } else if (line == "until" && linhas.top() == "repeat") {
          linhas.pop();
        } else if (line == "end;" && linhas.top() == "else") {
          linhas.pop(); /// desempilha else
          linhas.pop(); /// desempilha case
        } else {
          myfile.close();
          cout << "Errado" << endl;
          return;
        }
      }
    }
    myfile.close();
    if (linhas.empty()) {
      cout << "Certo" << endl;
    } else {
      cout << "Errado" << endl;
    }
    /// limpa a pilha
    int unsigned tam = linhas.size();
    for (int unsigned i = 0; i < tam; i++) {
      linhas.pop();
    }
  } else {
    cout << "Erro ao abrir o arquivo" << endl;
  }
}
int main(int argc, char *argv[])
{
    if (argc < 2) {
      cout << "Insira o caminho do arquivo\nABORTADO\n" << endl;
      return 0;
    }
    const char* path = argv[1];
    le_arquivo(path);
    return 0;
}
