
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <sstream>
#include <fstream>
#include <array>

using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

*** CASO RECURSIVO ***
playlist con las canciones coincidentes en el mismo orden de ambas playlist

					// si la cancion en playlist1 es igual a la de playlist 2, se
					// guarda la cancion en la solucion y se avanza en ambas playlists
			     |	playlist(i+1, j+1)			si playlist1[i] == playlist2[j]
playlist(i, j) = |
				 |	max(size(playlist(i+1, j)),	si playlist1[i] != playlist2[j]
						size(playlist(i, j+1))
						)
					// si la cancion es distinta en ambas playlists, se compara la
					// solucion que devuelve si probamos con una posicion mas en i y
					// una posicion mas en j y cogemos el resultado mas largo

*** CASOS BASE ***
// si o i o j llegan al final del vector, se devuelve nada
playlist(i, size(playlist2)) = 0
playlist(size(playlist1), j) = 0

*** LLAMADA INICIAL ***
// llamada inicial con los indices de playlist1 y playlist 2
playlist(0, 0)

*** MATRIZ ***
[...]

*** COSTE ***
[...]

@ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class PlayList {
public:
	PlayList(vector<string>& const playlist1, vector<string>& const playlist2) 
	: playlist1(playlist1), playlist2(playlist2) {
		// matriz de vectores de string inicializadas a vectores vacios
		matriz = Matriz<vector<string>>(playlist1.size() + 1, playlist2.size() + 1, vector<string>(1, "*"));
	}

	vector<string> playlist(int i, int j) {
		vector<string>& res = matriz[i][j];

		if (res.empty()) return res;
		// si no se ha mirado la solucion en esta posicion aun 
		if (res[0] == "*") {
			// casos base: si cualquiera de los indices llega al maximo, devuelve un vector vacio
			if (i >= playlist1.size() || j >= playlist2.size())
				return vector<string>();
			// si ambas canciones son iguales
			if (playlist1[i] == playlist2[j]) {

				//
				res = playlist(i + 1, j + 1);
				res.push_back(playlist1[i]);
				// mete la cancion
				return res;
			}
			// si ambas canciones son distintas
			else {
				//
				vector<string> a = playlist(i + 1, j);
				vector<string> b = playlist(i, j + 1);
				res = max_playlist(a, b);
				return res;
			}
		}
		return res; 
	}

	vector<string> getSol() {
		return vector<string>();
	}

private:
	vector<string> playlist1;
	vector<string> playlist2;
	Matriz<vector<string>> matriz;

	vector<string> max_playlist(vector<string> a, vector<string> b) {
		if (a.size() > b.size())
			return a;
		else
			return b;
	}
};


bool resuelveCaso() {
	// leer los datos de la entrada

	string aux;
	vector<string> playlist1;
	vector<string> playlist2;

	if (!std::cin)  // fin de la entrada
		return false;

	bool next = false;
	char a = ' ';
	string word = "";
	
	// lee las dos playlists

	a = cin.get();
	while (a != '\n') {
		if(a != ' ')
			word.push_back(a);
		else {
			playlist1.push_back(word);
			word.clear();
		}
		a = cin.get();
	}
	playlist1.push_back(word);
	word.clear();

	a = cin.get();
	while (a != '\n') {
		if (a != ' ')
			word.push_back(a);
		else {
			playlist2.push_back(word);
			word.clear();
		}
		a = cin.get();
	}
	playlist2.push_back(word);
	word.clear();
	
	// resolver el caso posiblemente llamando a otras funciones
	PlayList pl(playlist1, playlist2);
	pl.playlist(0,0);

	vector<string> sol = pl.getSol();
	// escribir la solución
	for (int i = 0; i < sol.size(); i++)
		cout << sol[i] << " ";
	cout << "n";

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	if (!in.is_open())
		std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif
	return 0;
}
