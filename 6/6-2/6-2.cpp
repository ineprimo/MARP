
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


class canPass {

private:
	vector<bool> visit;
	GrafoValorado<int> g;
	bool can;
	int orig, dest, size;

	void dfs(GrafoValorado<int> const& g, int v, int threshold) {
		visit[v] = true;
		if (can) return;
		for (auto a : g.ady(v)) {
			if (a.valor() >= threshold) {
				int w = a.otro(v);
				if (w == dest) {
					can = true;
					return;
				}
				if (!visit[w])
					dfs(g, w, threshold);
			}
		}
	}

public:
	canPass(GrafoValorado<int> const& g, int orig, int dest, int size) : g(g), visit(g.V(), false), can(false),
		orig(orig), dest(dest), size(size) {
		dfs(g, orig, size);
	};

	bool canItPass() {
		return can;
	};

};

bool resuelveCaso() {
	// leer los datos de la entrada

	int V, A;
	cin >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;

	GrafoValorado<int> g(V);

	int u, v, valor;
	for (int i = 0; i < A; i++) {
		cin >> u >> v >> valor;
		g.ponArista({u - 1, v - 1, valor});
	}

	int cases, orig, dest, size;
	cin >> cases;

	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < cases; i++) {
		// 
		cin >> orig >> dest >> size;
		canPass pass(g, orig - 1, dest - 1, size);

		// escribir la solución
		if (pass.canItPass())
			cout << "SI\n";
		else
			cout << "NO\n";
	}

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
