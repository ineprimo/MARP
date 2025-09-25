
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

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


struct comic {
	int id;
	int position;
	int stack;
};

//bool operator <(comic const& a, comic const& b) {
//	if (a.stack == b.stack)
//		return a.position < b.position;
//	else
//		return a.id > b.id;
//};

bool operator <(comic const& a, comic const& b) {
	return (a.stack == b.stack && a.position > b.position)
		|| (a.stack != b.stack && a.id < b.id);
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	cin >> n;
	if (!std::cin)  // fin de la entrada
		return false;
	int qpos = 0;

	PriorityQueue<comic> queue;

	int k, c;
	for (int i = 0; i < n; ++i) {
		cin >> k;
		for (int j = 0; j < k; ++j) {
			cin >> c;
			queue.push({c, j, i});
		}
	}

	cout << qpos << "\n";

	// resolver el caso posiblemente llamando a otras funciones

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
