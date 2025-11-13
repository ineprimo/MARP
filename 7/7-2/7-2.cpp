
/*@ <authors>
 *
 * MARP52 Ines Primo
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
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
class TiempoDeCarga {
public:
	TiempoDeCarga(DigrafoValorado<Valor> const& g, int orig, vector<int> _tiempos) : origen(orig),
		dist(g.V(), INF), ulti(g.V()), pq(g.V()), tiempos(_tiempos) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}


	using Camino = deque<AristaDirigida<Valor>>;

	bool hayCamino(int v) const { return dist[v] != INF; }
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

	int costeAPagina(int v) {
		Camino cam = camino(v);
		int coste = tiempos[origen];
		while (!cam.empty()) {
			AristaDirigida<int> a = cam.front(); cam.pop_front();
			coste += a.valor();
			coste += tiempos[a.hasta()];
		}
		return coste;
	}

private:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<Valor> dist;
	std::vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;

	vector<int> tiempos;
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor() + tiempos[w]) {
			dist[w] = dist[v] + a.valor(); ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}
};


bool resuelveCaso() {
	// leer los datos de la entrada
	int t;
	cin >> t;

	if (t == 0)
		return false;

	// tiempos de carga de las paginas
	int tiempo = 0, aux;
	vector<int> tiempos = vector<int>(tiempo);
	for (int i = 0; i < t; i++) {
		cin >> aux;
		tiempos.push_back(aux);
	}

	// conexiones de las paginas
	int p = 0, a, b, j;
	cin >> p;
	DigrafoValorado<int> paginas = DigrafoValorado<int>(t);
	for (int i = 0; i < p;i++) {
		cin >> a >> b >> j;
		paginas.ponArista({a-1, b-1, j});

	}

	// resolver el caso posiblemente llamando a otras funciones
	TiempoDeCarga<int> carga = TiempoDeCarga<int>(paginas, 0, tiempos);

	//deque<AristaDirigida<int>> cam = carga.camino(t);

	int sol = carga.costeAPagina(t);

	// escribir la solución
	cout << sol << "\n";

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
