
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

int guerreros(vector<int> const& enemigos, vector<int> const& aliados) {
	int cont = 0;
	int i = 0, j = 0;
	while(i<enemigos.size() && j<aliados.size()){
		// si es suficiente
		if (enemigos[i] <= aliados[j]) {
			cont++;
			i++; j++;
		}
		else i++;
	}
	return cont;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> enemigos;
	vector<int> aliados;
	int aux;
	for (int i = 0; i < N; i++) {
		cin >> aux;
		enemigos.push_back(aux);
	}
	for (int i = 0; i < N; i++) {
		cin >> aux;
		aliados.push_back(aux);
	}

	// los ordenamos de mayor a menor
	std::sort(enemigos.begin(), enemigos.end(), greaterThan);
	std::sort(aliados.begin(), aliados.end(), greaterThan);

	// solucion
	cout << guerreros(enemigos, aliados) << "\n";

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
