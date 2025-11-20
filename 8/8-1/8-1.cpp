
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

int manguera(vector<int> const& agujeros, int L, vector<bool>& g) {
	g[0] = false; // empezamos sin parche
	int parches = 0;
	int p = 0;	// puntos recorridos desde el ultimo parche
	int sigAgujero = 0;
	int ultimoParche = 0;
	bool parcheando = false;
	for (int i = 0; i < agujeros[agujeros.size() - 1]; ++i) { // estamos en gi

		// si el parche aun tapa
		if (p < L && parcheando) {
			// seguimos y marcamos que esta parcheado
			g[i] = true; // 
			p++; // aumentamos el contador de puntos del parche
			while(i == agujeros[sigAgujero] - 1)
				sigAgujero++;

		}
		// si hay agujero pero el parche no lo tapa
		else if(i == agujeros[sigAgujero] - 1) {
			// le ponemos un parche
			g[i] = true;
			++parches;
			p = 0;
			ultimoParche = i;
			parcheando = true;

			// marcamos el siguiente agujero
			sigAgujero++;
		}
		else {
			parcheando = false;
			p = 0;
		}




	}
	return parches;
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
	vector<bool> filled(agujeros[agujeros.size()-1], false);

	//
	cout << manguera(agujeros, L, filled) << "\n";

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
