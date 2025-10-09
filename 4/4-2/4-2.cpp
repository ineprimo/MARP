
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <utility>
#include <queue>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>



class Bipartito {
private:
	using Camino = deque<int>;

	vector<bool> visit;
	vector<int> ant;
	int orig;
	bool ciclico = false;



	void dfs(Grafo const& g, int v) {
		visit[v] = true;

		auto a = g.ady(v);
		int w = 0;
		while (w < a.size() && !ciclico) {
			if (!visit[w]) {
				ant[w] = v;
				dfs(g, w);
			}
			// si no es su padre
			else if (ant[v] != w && w != orig) {
				ciclico = true;
			}

			w++;
		}

	}

public:

	Bipartito(Grafo const& g, int orig)
		: visit(g.V(), false), ant(g.V()), orig(orig) {


		dfs(g, orig);

	}

	bool hayCamino(int v) const {
		return visit[v];
	}

	Camino camino(int v) const {
		if (!hayCamino(v)) throw domain_error("No existe camino");
		Camino cam;
		for (int x = v; x != orig; x = ant[x])
			cam.push_back(x);
		cam.push_back(orig);
		return cam;
	}

	bool esLibre() {

		return !ciclico;
	}


};


bool resuelveCaso() {
	// leer los datos de la entrada

	int v, a, aux1, aux2;
	cin >> v;
	cin >> a;

	if (!std::cin)  // fin de la entrada
		return false;

	// grafo
	Grafo graph = Grafo(v);

	vector<pair<int, int>> visitados;

	bool esLibre = true;

	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < a; i++) {
		cin >> aux1 >> aux2;

		graph.ponArista(aux1, aux2);
	}

	// escribir la solución
	Bipartito b = Bipartito(graph, 0);

	if (b.esLibre())
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
