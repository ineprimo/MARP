
/*@ <authors>
 *
 * MARP52 Ines Primo
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <limits>
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
class CaminosMinimos {
public:
	CaminosMinimos(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), ulti(g.V()), pq(g.V()), num(0), cost(g.V(), 0), count(g.V(), 0) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			if (v == 4)
				int a = 0;

			for (auto a : g.ady(v))
				relajar(a);
		}

		dist;
		count;
	}


	using Camino = deque<AristaDirigida<Valor>>;

	bool hayCamino(int v) const { return dist[v] != INF; }
	int numCaminos(int v) const { return count[v]; }
	Valor distancia(int v) const { return dist[v]; }
	Camino camino(int v) const {
		Camino cam;
		// recuperamos el camino retrocediendo
		AristaDirigida<Valor> a;
		for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
			cam.push_front(a);
		cam.push_front(a);
		return cam;
	}

private:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<Valor> dist;
	std::vector<int> cost;
	std::vector<int> count;
	std::vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;

	int num;
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ulti[w] = a;

			if (count[v] == 0)
				count[w] = 1;
			else
				count[w] = count[v];

			// no tiene en cuenta que si encuentra otro camino (4 -> 7) despues del primero (4 -> 5 -> 7) pasa de count 2 a count 4
			pq.update(w, dist[w]);
		}
		else if (dist[w] == dist[v] + a.valor()) {
			count[w]++;
		}
	}
};


bool resuelveCaso() {
	// leer los datos de la entrada
	int V, A;
	cin >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;

	DigrafoValorado<int> grafo(V);

	int a, b, c;
	// lectura del grafo
	for (int i = 0; i < A; i++) {
		cin >> a >> b >> c;
		grafo.ponArista({a - 1, b - 1, c});
		grafo.ponArista({b - 1, a - 1, c});
	}

	//
	CaminosMinimos<int> min = CaminosMinimos<int>(grafo, 0);

	cout << min.numCaminos(V-1) << "\n";

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
