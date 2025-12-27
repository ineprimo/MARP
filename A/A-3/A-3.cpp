
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Matriz.h"

/*@ <answer>

Definicion recursiva, siendo i el indice del sector que estamos mirando y j la cantidad de puntos que quedan por conseguir:

						|
						|	si c < 0	0
caminoMinimo(i, j, c) =	|	si 
						|	


 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminoMinimo {
public:
	CaminoMinimo(std::vector<std::string> _cruces, int _camino) {
		cruces = _cruces;
		camino = _camino;
		N = cruces.size();
		M = cruces[0].size();

		// creamos la tabla 
		tabla = Matriz<int>(cruces.size(), cruces[0].size(), -1);

		sol = caminoMinimo(0,0, _camino);
	}

	int getSol() { return sol; }

private:
	std::vector<std::string> cruces;
	int camino;
	Matriz<int> tabla;
	int N, M;

	int sol;

	int caminoMinimo(int i, int j, int c) {
		// caso base si se sale de bounds o si encuentra una X o si es demasiado largo
		if (i >= N || j >= M || cruces[i][j] == 'X' || c < 0 ) return 0;
		// caso base si ha llegado al final (suponiendo que no es mas largo que el camino minimo supuesto)
		else if (i == N - 1 && j == M - 1) return 1;
		// si ya lo tenemos en la tabla
		else if (tabla[i][j] != -1) return tabla[i][j];
		// si no esta calculado
		else {
			// hacemos un divide et impera
			// calculamos hacia abajo
			int a = caminoMinimo(i + 1, j, c - 1);
			// calculamos hacia la derecha
			int b = caminoMinimo(i, j + 1, c - 1);
			// unimos solucion
			tabla[i][j] = a + b;
		}
		// devolvemos la solucion
		return tabla[i][j];
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, M;
	std::cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;

	std::vector<std::string> cruces;
	int aux;
	for (int i = 0; i < N; i++) {
		std::string aux = "";
		std::cin >> aux;
		cruces.push_back(aux);
	}

	int camino = (N - 1) + (M - 1);
	
	CaminoMinimo c(cruces, camino);
	
	std::cout << c.getSol() << std::endl;

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
