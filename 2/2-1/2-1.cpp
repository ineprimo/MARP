
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>+

using namespace std;

#include "PriorityQueue.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
long sum(PriorityQueue<long>& queue) {

	long a = 0, b = 0;

	long result = 0;

	while (queue.size() > 1) {

		a = queue.top();
		queue.pop();

		b = queue.top();
		queue.pop();

		long aux = a + b;
		result += aux;

		// mete el esfuerzo de la suma anterior en al cola, como que 'reemplaza' los valores anteriores con su esfuerzo
		queue.push(aux);
	}

	return result;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int num;
	cin >> num;
	if (num == 0)  // fin de la entrada
		return false;
	
	long dato;
	PriorityQueue<long> queue;
	for (int i = 0; i < num; i++) {
		cin >> dato;
		queue.push(dato);
	}

	// resolver el caso posiblemente llamando a otras funciones
	// escribir la solución
	cout << sum(queue) << endl;

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
