
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <algorithm>




/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int tuneles(std::vector<std::pair<int, int>> edificios) {
	int tunel = 0;
	int currTunel = -1;

	for (int i = 0; i < edificios.size(); i++) {
		if (currTunel <= edificios[i].first) {
			tunel++;
			currTunel = edificios[i].second;
		}
	}
	return tunel;
}

bool lessThan(const std::pair<int, int>& a, const  std::pair<int, int>& b) {
	return a.second < b.second;
}

bool resuelveCaso() {
	// leer los datos de la entrada

	int N;
	std::cin >> N;

	if (N == 0)  // fin de la entrada
		return false;

	// vector con los valores de los billetes
	std::vector<std::pair<int, int>> edificios;
	int a, b;
	for (int i = 0; i < N; i++) {
		std::cin >> a >> b;
		edificios.push_back({a, b});
	}

	// los ordena de menor a mayor (por defecto)
	std::sort(edificios.begin(), edificios.end(), lessThan);

	// resuelve el problema
	b = tuneles(edificios);

	// escribir la solución
	std::cout << b << std::endl;

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
