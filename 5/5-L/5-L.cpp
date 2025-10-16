
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class ProgramaOscuro {

public:

	ProgramaOscuro(Digrafo& const g) : visit(g.V(), false) {
		for (int v = 0; v < g.V(); ++v) {
			if (!visit[v])
				dfs(g, v);
		}
	}


private:
	vector<bool> visit;
	deque<int> orden;

	void dfs(Digrafo &const g, int v) {
		visit[v] = true;
		for (int w : g.ady(v)) {
			if (!visit[w]) {
				dfs(g, w);
			}
			orden.push_front(w);
		}
	}
	
};


bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	//
	Digrafo g = Digrafo(N + 1);
	char aux1, aux2; int aux3;
	vector<char> types;

	// primer caso
	cin >> aux1;
	types.push_back(aux1);
	g.ponArista(0, 1);
	if (aux1 == 'J' || aux1 == 'C') {
		cin >> aux3;
		g.ponArista(0, aux3 - 1);
	}

	for (int i = 1; i < N; i++) {
		cin >> aux2;
		types.push_back(aux2);

		g.ponArista(i, i + 1);

		if (aux2 == 'J' || aux2 == 'C') {
			cin >> aux3;
			g.ponArista(i, aux3 - 1);
		}
	}

	// el ultimo vertice (auxiliar)
	types.push_back('F');

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
