
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <algorithm>




 /*@ <answer>

  Escribe aquí un comentario general sobre la solución, explicando cómo
  se resuelve el problema y cuál es el coste de la solución, en función
  del tamaño del problema.

  @ </answer> */


  // ================================================================
  // Escribe el código completo de tu solución aquí debajo
  // ================================================================
  //@ <answer>

int alien(std::vector<std::pair<int, int>> tareas, int begin, int end) {
	int sol = 0;
	int i = 1;
	int best = 0;
	int possible = 0;

	if (tareas[best].first > begin)
		return sol;
	sol++;
	// busqueda
	while (i < tareas.size() && tareas[best].second < end && sol > 0) {
		// mira posible opcion
		if (tareas[i].first <= tareas[best].second) {
			// si la nueva opcion es mejor que la que teniamos guardada
			if(tareas[possible].first <= tareas[i].first && tareas[i].second > tareas[possible].second)
				possible = i;
		}
		else if (tareas[i].first - tareas[best].second > 0 && possible == best) {
			sol = 0;
		}
		else {
			if (tareas[possible].first > tareas[best].second) {
				sol = 0;
			}
			else {
				best = possible;
				sol++;
			}
		}
		i++;
	}

	// miramos la ultima tarea si es que es una posible opcion
	if (possible == tareas.size() - 1) {
		if (tareas[possible].second >= end) {
			best = possible;
			sol++;
		}
		else sol = 0;
	}

	// miramos la ultima tarea si es que con lo que tenemos no llegamos al final
	if (tareas[best].second < end) {
		if (tareas[tareas.size() - 1].first <= tareas[best].second && tareas[tareas.size() - 1].second >= end) {
			sol++;
		}
		else
			sol = 0;
	}

	return sol;
}

bool lessThan(const std::pair<int, int>& a, const  std::pair<int, int>& b) {
	return a.second < b.second;
}

bool resuelveCaso() {
	// leer los datos de la entrada

	int C, F, N;
	std::cin >> C >> F >> N;

	if (C == 0 && F == 0 && N == 0)  // fin de la entrada
		return false;

	// vector con los valores de los billetes
	std::vector<std::pair<int, int>> tareas;
	int a, b;
	for (int i = 0; i < N; i++) {
		std::cin >> a >> b;
		tareas.push_back({ a, b });
	}

	// los ordena de menor a mayor (por defecto)
	std::sort(tareas.begin(), tareas.end(), lessThan);

	// resuelve el problema
	b = alien(tareas, C, F);

	// escribir la solución
	if(b == 0)
		std::cout << "Imposible" << std::endl;
	else
		std::cout << b << std::endl;


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
