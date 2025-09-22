
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 * 
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct registro {
	int momento;	// cuando le toca
	int id;
	int periodo;	// tiempo entre consultas
};

bool operator<(registro const& a, registro const& b) {
	return b.momento < a.momento ||
		(a.momento == b.momento && b.id < a.id);
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	cin >> n;
	if (n == 0)  // fin de la entrada
		return false;

	priority_queue<registro> queue;
	for (int i = 0; i < n; ++i) {
		int id, period;
		cin >> id >> period;
		queue.push({period, id, period});
	}

	int envios;
	cin >> envios;
	while (envios--) {
		auto e = queue.top(); queue.pop();
		cout << e.id << "\n";
		e.momento += e.periodo;
		queue.push(e);

	}
	cout << "---\n";
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
