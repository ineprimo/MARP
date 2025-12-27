
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
#include "Matriz.h"
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

EntInf diana(int puntos, std::vector<int> const& sectores) {
	int n = sectores.size();
	// crea la tabla setteandola toda a infinito representando esto que no tiene solucion
	// el tamanyo de la tabla es el numero de sectores que haya + 1 para poder representar el conjunto vacio en i
	// y todos los puntos de 0 a puntos, +1 (en el primer caso es 100 +1), por el conjunto vacio tmb
	Matriz<EntInf> tabla(n + 1, puntos + 1, Infinito);

	// recorremos primero la i (filas)
	for (int i = 1; i < tabla.numfils(); i++) {
		// setteamos el conjunto vacio (a 0)
		tabla[i][0] = 0;

		// recorremos el resto de la fila teniendo en cuenta la definicion recursiva
		for (int j = 1; j < tabla.numcols(); j++) {

			// si se puede usar este sector entonces:
			if (j < sectores[i - 1]) {
				// quitamos este sector de las opciones, aka vamos al siguiente sector
				tabla[i][j] = tabla[i - 1][j];
			}
			// si no se puede entonces:
			else {

				EntInf a = tabla[i - 1][j];
				EntInf b = tabla[i][j - sectores[i - 1]] + 1;
				// cogemos el minimo de sectores posibles
				tabla[i][j] = min(a, b);
			}
		}
	}
	return tabla[n][puntos];
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int P, S;
	std::cin >> P >> S;

	if (!std::cin)  // fin de la entrada
		return false;

	std::vector<int> sectores;
	int aux;
	for (int i = 0; i < S; i++) {
		std::cin >> aux;
		sectores.push_back(aux);
	}

	EntInf sol = diana(P, sectores);

	// 
	std::cout << sol << std::endl;

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
