
/*@ <authors>
 *
 * Ines Primo MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Pajaro {
	int id;
	int age;
};

bool operator <(Pajaro const& a, Pajaro const& b) {
	return a.age < b.age ||
		(a.age == b.age && a.id < b.id);
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int pajaro, n;
	cin >> pajaro >> n;
	if (pajaro == 0)  // fin de la entrada
		return false;

	// cola de prioridad de minimos
	IndexPQ<Pajaro> queue((n*2)+1);

	int pos = 0;
	queue.push(pos++, {pos, pajaro});

	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < n; i++) {
		int p1, p2;
		cin >> p1 >> p2;

		queue.push(pos++, {pos, p1});
		queue.push(pos++, {pos, p2});

		int index = (pos+1) / 2;

		// solution
		cout << queue.priority(index).age << " ";
	}

	cout << endl;

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
