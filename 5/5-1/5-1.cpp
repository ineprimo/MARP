
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Como estamos recorriendo el grafo, en el peor de los casos el coste sera de O(V + A), 
 en este caso el coste seria de O(3 + 3*pulsacione)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


const int MAX = 10000;
const int INF = 1000000000;

int adyacente(int v, int i) {
	switch (i)
	{
	case 0:
		return (v + 1) % MAX;
	case 1:
		return (v * 2) % MAX;
	case 2:
		return (v / 3) % MAX;
	}

}

int bfs(int origen, int destino) {
	// si el valor que queremos (destino) es el valor en el que empezamos, devolvemos 0 movimientos 
	if (origen == destino) return 0;

	// vector de distancia, todos inicializacos a INF para indicar que no han sido alcanzados aun (se guarda el numero de movimientos)
	vector<int> distancia(MAX, INF);
	distancia[origen] = 0;

	// queue para guardar el recorrido
	queue<int> cola; cola.push(origen);

	//
	while (!cola.empty()) {
		int v = cola.front(); cola.pop();

		// for para recorrer todos los adyacentes posibles (3 siempre por el enunciado) a v
		for (int i = 0; i < 3; i++) {
			int w = adyacente(v, i);

			// si la distancia es INF para w, es que no ha sido visitaod asi que lo setteamos
			if (distancia[w] == INF) {
				// la distancia es la del nodo anterior + 1
				distancia[w] = distancia[v] + 1;

				// si es el resultado return
				if (w == destino) return distancia[w];
				// si no es resultado, añadimos el valor a la cola del recorrido
				cola.push(w);
			}
		}
	}


}

bool resuelveCaso() {
	// leer los datos de la entrada
	int orig, dest;

	cin >> orig >> dest;

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones

	cout << bfs(orig, dest) << "\n";

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
