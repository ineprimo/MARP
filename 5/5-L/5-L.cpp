
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

	ProgramaOscuro(Digrafo& const g, vector<char> &const type) : visit(g.V(), false), ant(g.V()), apilado(g.V(), false), hayCiclo(false), types(type) {
		for (int v = 0; v < g.V(); ++v) {

			// si no se ha visitado y aun no se sabe si es siempre o a veces finalizable
			if (!visit[v] && finalizable != SIEMPRE_FINALIZABLE && finalizable != A_VECES_FINAZLIABLE)
				dfs(g, v);
		}
	}

	enum Type {
		SIEMPRE_FINALIZABLE,
		A_VECES_FINAZLIABLE,
		NUNCA_FINALIZABLE
	};
	
	Type getType() {
		return finalizable;
	}


private:
	using Camino = deque<int>;
	vector<bool> visit;
	deque<int> ant;
	deque<bool> apilado;
	Camino ciclo;
	vector<char> types;
	bool hayCiclo;
	bool cond_used = false;

	// tipo
	Type finalizable = NUNCA_FINALIZABLE;		// 

	void dfs(Digrafo& const g, int v) {
		apilado[v] = true;
		visit[v] = true;
		for (int w : g.ady(v)) {
			// !!! tener en cuenta tmb los casos donde se haya encontrado si finalizable
			if (hayCiclo)
				return;
			// seguimos
			if (!visit[w]) {
				ant[w] = v;

				// si el tipo del vertice es F es que es el final y se ha podido llegar al final del programa
				if (types[v] == 'F' && cond_used) {
					finalizable = A_VECES_FINAZLIABLE;
				}
				else if(types[v] == 'F')
					finalizable = SIEMPRE_FINALIZABLE;



				dfs(g, w);
			}
			// deteccion de ciclo	-> si el ciclo detectado es de tipo J entonces no es nunca finalizable 
			//						-> si el ciclo detectado es de tipo C y este llega hasta F entonces es finalizable 
			//							-> si es de tipo C sigue mirando pero por donde salga del bucle
			else if (apilado[w]) {
				// si es de tipo condicional no se tiene en cuenta porque tendra otra adycencia que posiblemente salga del ciclo
				if (types[v] == 'C') {
					cond_used = true;
					continue;
				}
				// si la instruccion actual es de tipo SALTAR o ARITMETICA y su adyacencia es un ciclo, no es finalizable
				hayCiclo = true;
				for (int x = v; x != w;x = ant[x]) {
					ciclo.push_front(x);
				}
				ciclo.push_front(w);
				ciclo.push_front(v);
			}
		}
		apilado[v] = false;
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
	if (aux1 == 'J' || aux1 == 'C') {
		cin >> aux3;
		g.ponArista(0, aux3 - 1);
	}
	else
		g.ponArista(0, 1);

	for (int i = 1; i < N; i++) {
		cin >> aux2;
		types.push_back(aux2);

		if (aux2 == 'J') {
			cin >> aux3;
			g.ponArista(i, aux3 - 1);
		}
		else if (aux2 == 'C') {
			cin >> aux3;
			g.ponArista(i, aux3 - 1);
			g.ponArista(i, i + 1);
		}
		else
			g.ponArista(i, i + 1);
	}

	// el ultimo vertice (auxiliar)
	types.push_back('F');

	// resolver el caso posiblemente llamando a otras 
	ProgramaOscuro po = ProgramaOscuro(g, types);

	// escribir la solución
	switch (po.getType())
	{
	case ProgramaOscuro::Type::SIEMPRE_FINALIZABLE:
		cout << "SIEMPRE\n";
		break;
	case ProgramaOscuro::Type::A_VECES_FINAZLIABLE:
		cout << "A VECES\n";
		break;
	case ProgramaOscuro::Type::NUNCA_FINALIZABLE:
		cout << "NUNCA\n";
		break;
	default:
		cout << "NUNCA\n";
		break;
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
