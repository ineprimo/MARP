
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "EnterosInf.h"
//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

static const int INF = 1000000000;

struct solucion {
	// formas
	std::vector<int>formas;
	// cuerdas
	std::vector<int>cuerdas;
	// costes
	std::vector<int>costes;
};

// metodo que resuelve el problema
void cometa(const std::vector<int>& longitudes, const std::vector<int>& costes, const int& longitud, solucion& sol) {
	// bucle que recorre las cuerdas
	for (int i = 0; i < longitudes.size(); i++) {
		// recorremos la longitud total
		for (int l = longitud; l >= longitudes[i]; l--) {
			// estamos recorriendo todas las posibles longitudes (vamos de 1 en 1 hasta el maximo que queremos) 
			// para poder luego dividir el problema en subproblemas, es decir, calculamos las soluciones para cuando 
			// la longitud sea de 10 para cuando volvamos a pedir esa longitud ya la tengamos
			
			//Primero contamos el número de formas posibles
			sol.formas[l] += sol.formas[l - longitudes[i]];

			// Contamos el mínimo de cuerdas necesarias
			sol.cuerdas[l] = min(sol.cuerdas[l], sol.cuerdas[l - longitudes[i]] + 1);

			//Contamos el mínimo coste necesario
			sol.costes[l] = min(sol.costes[l], sol.costes[l - longitudes[i]] + costes[i]);


		}
	}
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, L;
	std::cin >> N >> L;

	if (!std::cin)  // fin de la entrada
		return false;

	// donde guardamos los datos
	int longitud, cost;
	std::vector<int>longitudes(0, 0);
	std::vector<int>costes(0, 0);

	// lee el resto de datos
	for (int i = 0; i<N; i++) {
		std::cin >> longitud >> cost;
		longitudes.push_back(longitud);
		costes.push_back(cost);
	}

	// solucion por cada longitud 'posible' hasta L
	solucion sol;
	sol.formas = std::vector<int>(L + 1, 0);	// inicialmente hay 0 formas de resolver cada 
	sol.costes = std::vector<int>(L + 1, INF);	// inicializamos todos los costes a infinito
	sol.cuerdas = std::vector<int>(L + 1, INF);	// inicializamos todas las cuerdas que usamos (infinito)

	sol.formas[0] = 1;
	sol.costes[0] = 0;
	sol.cuerdas[0] = 0;

	// resolver el caso posiblemente llamando a otras funciones
	cometa(longitudes, costes, L, sol);
	
	// escribir la solución
	if(sol.formas[L] == 0)
		std::cout << "NO" << std::endl;
	else {
		std::cout << "SI " 
			// formas totales
			<< sol.formas[L] << " "
			// minimo de cuerdas (solucion optima)
			<< sol.cuerdas[L] << " "
			// coste minimo (optimo)
			<< sol.costes[L] << " "
			<< std::endl;
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
