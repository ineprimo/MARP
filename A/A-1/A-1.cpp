/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Matriz.h"
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

class Cometa {
public:
	Cometa(std::vector<int> _longitudes, std::vector<int> _costes, int _longitud) {
		longitudes = _longitudes;
		costes = _costes;
		longitud = _longitud;

		tabla = Matriz<EntInf>(longitudes.size() + 1, longitud + 1, Infinito);
		formasT = Matriz<EntInf>(longitudes.size() + 1, longitud + 1, Infinito);

		// 
		cometa();

		// para el numero de formas
		cuerdaUsada = std::vector<bool>(longitudes.size(), false);

		numFormas = formas(0,0,longitud);

		std::vector<int> sol = getSolution();
		for (int a : sol) {
			cost += costes[a];
		}
	}
	
	EntInf getNum() {
		return tabla[longitudes.size()][longitud];
	}

	EntInf getNumFormas() {
		return numFormas;
	}

	int getCoste() {
		return cost;
	}

private:
	std::vector<int> longitudes;
	std::vector<int> costes;
	int longitud;
	Matriz<EntInf> tabla;
	Matriz<EntInf> formasT;
	EntInf numFormas = 0;
	int cost = 0;
	std::vector<bool> cuerdaUsada;


	// calcula cuantas cuerdas hacen falta
	void cometa() {
		// bucle que recorre las cuerdas
		for (int i = 1; i < tabla.numfils(); i++) {
			// settea el conjunto vacio
			tabla[i][0] = 0;

			// recorremos la longitud total
			for (int l = 1; l < tabla.numcols(); l++) {
				
				// si podemos usar esta cuerda la usamos
				if (l < longitudes[i - 1]) {
					tabla[i][l] = tabla[i - 1][l];
				}
				// si no podemos usar esta cuerda
				else {
					EntInf a = tabla[i - 1][l];
					EntInf b = tabla[i][l - longitudes[i - 1]] + 1;

					tabla[i][l] = min(a, b);
				}
			}
		}
	}

	// i -> indice de cuerdas
	// j -> indice de longitud
	EntInf formas(int i, int j, int c) {
		// si la cuerda ha sido usada o no nos quedan cuerdas devolvemos
		if ((i > longitudes.size() && c <= 0) || cuerdaUsada[i]) return 0;
		// si ya lo tenemos en la tabla 
		else if (formasT[i][j] != -1) return formasT[i][j];
		// si no esta calculado
		else {
			// hacemos un divide et impera
			// calculamos hacia abajo
			EntInf a = formas(i + 1, j, c - 1);
			// calculamos hacia la derecha
			EntInf b = formas(i, j + 1, c - 1);
			// unimos solucion
			formasT[i][j] = a + b;
		}
		// devolvemos la solucion
		return formasT[i][j];
	}

	vector<int> getSolution() {
		vector<int> sol;
		if (tabla[longitudes.size()][longitud] != Infinito) {
			int i = longitudes.size(), j = longitud;
			while (j > 0) { // no se haya completado al cometa 
				if (longitudes[i - 1] <= j && tabla[i][j] == tabla[i][j - longitudes[i - 1]] + 1) {
					// tomamos una moneda de tipo i
					sol.push_back(i - 1);
					j = j - longitudes[i - 1];
				}
				else // no tomamos más monedas de tipo i
					--i;
			}
		}
		return sol;
	}
};



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
	Cometa c(longitudes, costes, L);

	// escribir la solución
	if(c.getNum() > longitudes.size())
		std::cout << "NO" << std::endl;
	else {
		std::cout << "SI " 
			// formas totales
			<< c.getNumFormas() << " "
			// minimo de cuerdas (solucion optima)
			<< c.getNum() << " "
			// coste minimo (optimo)
			<< c.getCoste() << " "
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
