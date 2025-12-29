/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
 //#include <...>

using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool greaterThan(int const& a, int const& b) {
	return a > b;
}

int coches(std::deque<int> pilas, int V) {
	int coches = 0;

	while (!pilas.empty() && pilas.size() > 1) {
		if(pilas.front() + pilas.back() >= V) {
			coches++;
			pilas.pop_front();
			pilas.pop_back();

		}
		else {
			pilas.pop_back();
		}
	}


	return coches;
}

void resuelveCaso() {
	// leer los datos de la entrada
	int N, V;
	std::cin >> N >> V;
	
	std::deque<int> pilas;
	int aux;
	for (int i = 0; i < N; i++) {
		std::cin >> aux;
		pilas.push_back(aux);
	}

	std::sort(pilas.begin(), pilas.end(), greaterThan);

	// resolver el caso posiblemente llamando a otras funciones
	int sol = coches(pilas, V);

	// escribir la solución
	std::cout << sol << std::endl;
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

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif

	return 0;
}
