
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

struct Pajaro {
	int id;
	int age;
};

// probar con dos colas de prioridad 

bool resuelveCaso() {
	// leer los datos de la entrada
	int pajaro, n;
	cin >> pajaro >> n;
	if (pajaro == 0)  // fin de la entrada
		return false;

	PriorityQueue<int, greater<int>> izquierda;
	PriorityQueue<int, less<int>> derecha;

	int pos = 0;
	//queue.push(pos++, {pos, pajaro});
	izquierda.push(pajaro);


	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < n; i++) {
		int p1, p2;
		cin >> p1 >> p2;

		if (p1 < izquierda.top()) {
			izquierda.push(p1);
		}
		else
			derecha.push(p1);

		if (p2 < izquierda.top()) {
			izquierda.push(p2);
		}
		else
			derecha.push(p2);

		// si hay de mas en la cola de la izqueirda
		if (izquierda.size() - derecha.size() > 1) {
			int aux = izquierda.top(); izquierda.pop();
			derecha.push(aux);
		}

		// Si hay de mas en la de la derecha
		if (derecha.size() - izquierda.size() > 0) {
			int aux = derecha.top(); derecha.pop();
			izquierda.push(aux);
		}

		// solution
		cout << izquierda.top() << " ";
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
