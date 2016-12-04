// map::emplace
#include <iostream>
#include <map>
using namespace std;
int main ()
{
  map<char,int> meu_map;

  meu_map.emplace('x',100);
  meu_map.emplace('y',200);
  meu_map.emplace('z',100);

  std::cout << "Meu Mapa Contem::";
  for (auto& x: meu_map)
    cout << " [" << x.first << ':' << x.second << ']';
  cout << '\n';

  return 0;
}
