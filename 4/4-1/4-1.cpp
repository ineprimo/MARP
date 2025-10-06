
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <utility>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


//
bool esCircular(int a, int b, vector<pair<int, int>>& g, const vector<int>& ady) {

	int i = 0;
	
	while (i < ady.size()) {

		//


		i++;
	}

}

bool resuelveCaso() {
	// leer los datos de la entrada

	int v, a, aux1, aux2;
	cin >> v;
	cin >> a;

	if (!std::cin)  // fin de la entrada
		return false;

	// grafo
	Grafo graph = Grafo(v);

	vector<pair<int, int>> visitados;

	bool esLibre = true;

	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < a; i++) {
		cin >> aux1 >> aux2;

		graph.ponArista(aux1, aux2);

		
	}

	// escribir la solución

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
