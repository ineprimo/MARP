
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#include "Matriz.h"

/*@ <answer>

Definicion recursiva: siendo la posicion vertical del tablero (y) y j la posicion horizontal del tablero (x)

						|					-1								si i < N && i >= 0 && j < N && j >= 0
	puntuacion(i, j) =	| tablero[i][j] + max(puntuacion(i - 1, j - 1),
						|						puntuacion(i - 1, j),					si i > 0
						|						puntuacion(i - 1, j + 1))
						|
						|				tablero[i][j]									si i = 0

Si los indices estan fuera de rango devolvemos -1, en caso contrario devolvemos la suma de la posicion actual mas la puntuacion maxima
de entre las tres opciones de movimiento.

Casos base:

puntuacion(0, j) = tablero[i][j]
puntuacion(i, -1) = -1, o cualquier numero no valido
puntuacion(-1, j) = -1, o cualquier numero no valido

Llamada inicial:
hay que llamar a la funcion desde todas las casillas de la fila inicial para poder calcular la solucion de cada casilla por lo que:
	
	puntuacion(N - 1, j)

N - 1 porque empezamos desde abajo a calcular.

Tabla y memoria:
no podemos mejorar el guardado de la tabla en memoria ya que podriamos estar sobreescribiendo casos que nos son utiles.

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class ResuelveTablero {
public:
	ResuelveTablero(std::vector<std::vector<int>> _tablero) {

		tablero = _tablero;
		N = tablero.size();
		tabla = Matriz<int>(N, N, -1);

		// rellena la tabla para cada casilla de la ultima fila
		for (int j = 0; j < N; j++) {
			tabla[N - 1][j] = puntuacion(N - 1, j);
		}
	}

	int getBestStart() {
		int best = 0;
		for (int j = 0; j < N; j++) {
			if (tabla[N - 1][j] > tabla[N - 1][best]) {
				best = j;
			}
		}
		return best;
	}

	int getPuntuacion(int j) {
		return tabla[N - 1][j];
	}

private:
	Matriz<int> tabla;
	int N;
	std::vector<std::vector<int>> tablero;

	// metodo que rellena la tabla
	int puntuacion(int i, int j) {

		// si no es una posicion valida devuelve -1. No hay que guardar nada
		if (!inBounds(i, j)) return -1;
		// si ya esta la solucion en la tabla se devuelve eso
		if (tabla[i][j] > -1) return tabla[i][j];
		// si hemos llegado al 'final', devuelves este valor
		else if (i == 0) return tablero[i][j];


		// si no, guarda el maximo de las tres opciones
		tabla[i][j] = tablero[i][j] + max({ puntuacion(i - 1, j - 1),
							puntuacion(i - 1, j),
							puntuacion(i - 1, j + 1) });

		// devuelve la solucion que hayamos calculado
		return tabla[i][j];
	}

	bool inBounds(int i, int j) {
		return i < N && i >= 0 && j < N && j >= 0;
	}

};


bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	std::cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	std::vector<std::vector<int>> tablero;
	int aux;
	for (int i = 0; i < N; i++) {
		std::vector<int> vectorAux;
		for (int j = 0; j < N; j++) {
			std::cin >> aux;
			vectorAux.push_back(aux);
		}
		tablero.push_back(vectorAux);
		vectorAux.clear();
	}

	// resuelve
	ResuelveTablero rt(tablero);
	int i = rt.getBestStart();

	// solucion
	std::cout << rt.getPuntuacion(i) << " " << i + 1 << std::endl;

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
