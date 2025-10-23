
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

 Como lo que se hace en el peor de los casos es recorrer todo el grafo para buscar el orden topologico, la complejidad 
 es la misma que el del recorrido del grafo: O(V+A). En este problema, el coste es O(tareas + dependencias)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

using Orden = deque<int>;

class OrdenTareas {

private:
	vector<bool> apilado;
	vector<bool> visit;
	Orden orden;
	bool ciclico;


	void dfs(Digrafo const& g, int v) {
		apilado[v] = true;
		visit[v] = true;

		// recorre todos los adyacentes al vertice
		for (int w : g.ady(v)) {

			// si hay ciclo devolvemos, por lo que el orden es IMPOSIBLE
			if (ciclico) return;

			// si el vertice es nuevo, se apunta como visitado
			if (!visit[w]) {
				// y se empieza el dfs como w
				dfs(g, w);
			}
			// si el vertice no es nuevo y esta apilado, entonces es un ciclo y es IMPOSIBLE
			else if(apilado[w]) {
				//
				ciclico = true;
			}
		}
		orden.push_front(v);
		apilado[v] = false;
	}

public:
	OrdenTareas(Digrafo const& g) : visit(g.V(), false), apilado(g.V()), ciclico(false){

		// llamada a dfs 
		for (int v = 0; v < g.V(); v++) {
			if (!visit[v])
				dfs(g, v);
		}
	}

	bool esImposible() {
		return ciclico;
	}

	Orden getOrden() {
		if (!ciclico)
			return orden;
		else return Orden();
	}

};

bool resuelveCaso() {
	// leer los datos de la entrada
	// vertices    aristas
	int tareas, dependencias;

	cin >> tareas >> dependencias;

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	Digrafo g = Digrafo(tareas);

	// rellena las adyacencias
	int a1, a2;
	for (int i = 0; i < dependencias; i++) {
		cin >> a1 >> a2;
		g.ponArista(a1 - 1, a2 - 1);
	}

	// clase que resuelve el caso
	OrdenTareas ot = OrdenTareas(g);

	// escribir la solución
	if (ot.esImposible())
		cout << "Imposible\n";
	else {
		Orden o = ot.getOrden();
		while (!o.empty()) {
			cout << o.front() + 1 << " "; 
			o.pop_front();
		}
		cout << "\n";
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
