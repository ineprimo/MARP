
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

bool greaterThan(int i, int j) { return (i > j); }

int extra(vector<int> const& chavales, vector<int> const& equipamiento) {
	int cont = 0;
	int i = 0, j = 0;
	while (i < chavales.size() && j < equipamiento.size()) {
		int talla = equipamiento[j];
		int c = chavales[i];
		// si el chaval puede llevar el equipamiento
		if (chavales[i] == equipamiento[j] || chavales[i] + 1 == equipamiento[j]) {
			i++; j++; }
		else if (chavales[i] < equipamiento[j]) j++;
		else { i++; cont++; }
	}
	cont += chavales.size() - i;
	return cont;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, M;

	cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> chavales;
	vector<int> equipacion;
	int aux;
	for (int i = 0; i < N; i++) {
		cin >> aux;
		chavales.push_back(aux);
	}
	for (int i = 0; i <M; i++) {
		cin >> aux;
		equipacion.push_back(aux);
	}

	// los ordenamos de mayor a menor
	std::sort(chavales.begin(), chavales.end(), greaterThan);
	std::sort(equipacion.begin(), equipacion.end(), greaterThan);

	// solucion
	cout << extra(chavales, equipacion) << "\n";

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
