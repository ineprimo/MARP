
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

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

int manguera(vector<int> const& agujeros, int L) {
	int n = agujeros[agujeros.size() - 1];
	int agujero = 0;
	int cont = 0;
	int parche = - L - 1;
	for (int i = 0; i < n; i++) {
		// si tiene un agujero
		if (i == agujeros[agujero] - 1) {
			// si no hay parche se lo pone
			if (i - parche > L) {
				parche = i;
				cont++;
				i += L;

				// actualiza los agujeros
				while (agujero < agujeros.size() && (i == agujeros[agujero] - 1 || agujeros[agujero] - 1 < i))
					agujero++;
			}
		}
	}
	return cont;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int L, N;

	cin >> N >> L;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> agujeros;
	int aux;
	for (int i = 0; i < N; i++) {
		cin >> aux;
		agujeros.push_back(aux);
	}

	// solucion
	cout << manguera(agujeros, L) << "\n";

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
