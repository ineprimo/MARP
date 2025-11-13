
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


template <typename Valor>
class Dijkstra {
private:

	using Camino = deque<Valor>;
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<Valor> dist;
	std::vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;


	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}
public:
	Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	bool hayCamino(int v) const { return dist[v] != INF; }

	deque<AristaDirigida<int>> camino(int v) const {
		deque<AristaDirigida<int>> sol;
		// recuperamos el camino retrocediendo
		AristaDirigida<Valor> a;
		for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
			sol.push_front(a);
		sol.push_front(a);
		return sol;
	}

};


bool resuelveCaso() {
	// leer los datos de la entrada
	int V, A;
	cin >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;

	DigrafoValorado<int> grafo(V);

	int a, b, j;

	for (int i = 0; i < A; i++) {
		//cin 
		cin >> a >> b >> j;
		grafo.ponArista({a-1, b-1, j});
		grafo.ponArista({b-1, a-1, j});	// en ambos sentidos
	}


	int origen, destino, casos;
	cin >> casos;
	for (int i = 0; i < casos; i++) {
		cin >> origen >> destino;

		Dijkstra<int> caminos = Dijkstra<int>(grafo, origen - 1);

		if (caminos.hayCamino(destino - 1)) {
			int tiempo = 0;
			string sol = "";
			deque<AristaDirigida<int>> cam = caminos.camino(destino - 1);
			while (!cam.empty()) {
				AristaDirigida<int> a = cam.front(); cam.pop_front();

				// escribir en strng
				sol += to_string(a.desde() + 1);
				sol += " -> ";
				tiempo += a.valor();
			}

			//	SOLUCION
			cout << tiempo << ": " << sol << destino << "\n";
		}
		else
			cout << "NO LLEGA" << "\n";
	}
	cout << "---" << "\n";

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
