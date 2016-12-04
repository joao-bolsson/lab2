#include <iostream>
#include <map>
using namespace std;

int main(int argc, char *argv[])
{
	map<int, string> mapa;
	map<int, string> mapa2;
    
    // Método de inserção tradicional - Parecido com vetor
	mapa[1] = "joao";
	mapa[2] = "maria";
	mapa[3] = "pedro";
	
	mapa2[1] = "agua";
	mapa2[2] = "terra";
	mapa2[3] = "fogo";
	
	//Método de inserção definido na classe MAP.
	mapa.insert(pair<int, string>(4, "jose")); 
	mapa.insert(pair<int, string>(5, "jesus"));
	
	mapa.emplace(7,"augusto");
	mapa.emplace(3, "rogerio");

	// alterando o valor associado a uma chave
	mapa.at(1) = "carol";
	mapa[2] = "simone";

	if(mapa.empty()){
		cout << "Mapa vazio!!\n" << endl;
		cout << "Capacidade do Mapa: " << mapa.max_size() << endl; 
      }
	else{
		cout << "Mapa NAO vazio!!\n" << endl;
		cout << "Tamanho do Mapa: " << mapa.size() << endl;
		cout << "Capacidade do Mapa: " << mapa.max_size() << endl; 
	}
		


	if(mapa.count(4) > 0)
		cout << "4 eh elemento do mapa\n";
	else
		cout << "4 NAO eh elemento do mapa\n";

	// mostrando todos os elementos
	map<int, string>::iterator it;
	for(it = begin(mapa); it != end(mapa); ++it)
		cout << "A chave " << it->first << " => " << it->second << endl;
	
	 for (auto& x: mapa)
         std::cout << " [" << x.first << ":" << x.second << "]";
    std::cout << "\n";
	
	// procura um elemento a partir da chave repassada.
	it = mapa.find(2); 
	
	// remove o elemento que foi repassado a chave.
	mapa.erase(it);    
    mapa.erase(3); 
    
	// verificando se uma chave existe
	if(mapa.find(2) == mapa.end())
		cout << "\nChave 2 NAO existe!\n\n";
	else
		cout << "\nChave 2 existe!\n\n";

	it = mapa.begin();
	mapa.insert(pair<int, string>(2, "maria"));
	
	//Trocando elementos entre map's.
	mapa2.swap(mapa);

	// mostrando todos os elementos
	for(it = mapa.begin(); it != mapa.end(); ++it)
		cout << "A chave de Mapa eh " << it->first << " => " << it->second << endl;
	
	for(it = begin(mapa2); it != end(mapa2); ++it)
		cout << "A chave de Mapa2 eh " << it->first << " => " << it->second << endl;
		
		
	//remove todos os elementos do Map.
	mapa.clear();
	
	return 0;
}
