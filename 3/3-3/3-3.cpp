
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
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

struct Tarea {
	int init;
	int fin;
	int periodic;
};

bool operator>(const Tarea& a, const Tarea& b) {

	return a.init > b.init;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int n, m, t;
	cin >> n >> m >> t;

	if (!std::cin)  // fin de la entrada
		return false;

	priority_queue<Tarea, vector<Tarea>, greater<Tarea>> queue;
	int init, fin, per;

	// tareas unicas
	for (int i = 0; i < n; i++) {
		cin >> init >> fin;

		if(init < t) 
			queue.push({init, fin, 0});

	}
	// tareas periodicas
	for (int i = 0; i < m; i++) {

		cin >> init >> fin >> per;

		if(init < t)
			queue.push({ init, fin, per });
	}

	// bucle para ver problemas
	bool conflicto = false, ended = false;
	while (!conflicto && !ended && queue.size() > 1 ) {

		Tarea aux1 = queue.top(); queue.pop();
		Tarea aux2 = queue.top();

		if (aux2.init <= aux1.fin)
			conflicto = true;

		if (aux1.periodic > 0 && aux1.init + aux1.periodic < t)
			queue.push({ aux1.init + aux1.periodic,
						aux1.fin + aux1.periodic,
						aux1.periodic });
	}

	// escribir la solución
	if (conflicto)
		cout << "SI\n";
	else
		cout << "NO\n";

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
