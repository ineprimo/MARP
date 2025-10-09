
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

// clase solucion wonldsfhlf
class OptimizacionFarolil {
private:

	using Camino = std::deque<int>;

	// solucion que se devuelve
	vector<int> sol;
	vector<bool> visit;	// vector de nodos visitados
	vector<int> ant;	// vector de los nodos anteriores
	vector<int> dist;	// distancia de caminos
	int pan;			// panaderia
	int alex;			// origen alex
	int lucas;			// origen lucas


public: 
	OptimizacionFarolil(Grafo const &g, int origenAlex, int origenLucas, int Panaderia)
		: visit(g.V(), false), ant(g.V()), dist(g.V()), alex(origenAlex), lucas(origenLucas), pan(Panaderia) {

		// aqui va la fiesta

		// busqueda de caminos desde alex (origen aleatorio)
		bfs(g, pan);

		// camino para lucas
		Camino c = camino(pan, lucas);

		// camino para alex
		Camino t = camino(pan, alex);

		// calculo del trabajo si no quedan
		int trabajoPorSeparado = c.size() + t.size() - 2;

		bfs(g, alex);

		// calculo del trabajo si quedan
		//Camino a = camino(alex, inter);
		//Camino l = camino(inter, lucas);

		c;
		t;


		// calculo de trabajo
	}

	// busqueda en profundiad
	void bfs(Grafo const& g, int orig) {
		std::queue<int> q;
		dist[orig] = 0; visit[orig] = true;
		q.push(orig);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if (!visit[w]) {
					ant[w] = v; 
					dist[w] = dist[v] + 1;
					visit[w] = true;
					q.push(w);
				}
			}
		}
	}

	bool hayCamino(int v) {
		return visit[v];
	}

	int distancia(int v) {
		return dist[v];
	}


	Camino camino(int v, int orig) {
		if (!hayCamino(v)) throw std::domain_error("No existe el camino");
		Camino cam;
		for (int x = orig; x != v; x = ant[x]) {
			cam.push_front(x);
		}
		cam.push_front(v);
		return cam;
	}

	vector<int> getViaje() {
		return sol;
	}

};


bool resuelveCaso() {
	// leer los datos de la entrada
	int V, A, Alex, Lucas, Panaderia;
	cin >> V;

	if (!std::cin)  // fin de la entrada
		return false;

	cin >> A >> Alex >> Lucas >> Panaderia;

	Grafo grafo = Grafo(V);

	int a, b;
	for (int i = 0; i < A; i++) {
		cin >> a >> b;
		grafo.ponArista(a - 1, b - 1);
	}	


	OptimizacionFarolil op(grafo, Alex - 1, Lucas - 1, Panaderia - 1);


	


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
