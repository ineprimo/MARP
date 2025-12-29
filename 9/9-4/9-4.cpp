
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
//#include <...>

using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int sillas(std::deque<int> personas, int peso) {
	int viajes = 0;

	while (personas.size() > 1) {
		if (personas.front() + personas.back() <= peso) {
			personas.pop_back();
			personas.pop_front();
			viajes++;
		}
		else if (personas.back() <= peso) {
			viajes++;
			personas.pop_back();
		}
		else
			personas.pop_back();
	}

	if (!personas.empty() && personas.front() <= peso)
		viajes++;

	return viajes;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int P, N;
	std::cin >> P >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	std::deque<int> personas;
	int aux;
	for (int i = 0; i < N; i++) {
		std::cin >> aux;
		personas.push_back(aux);
	}

	// ordena de menor a mayor
	std::sort(personas.begin(), personas.end());

	// resolver el caso posiblemente llamando a otras funciones
	int sol = sillas(personas, P);

	// escribir la solución
	std::cout << sol << std::endl;

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
