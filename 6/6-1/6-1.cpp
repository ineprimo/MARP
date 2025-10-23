
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "ConjuntosDisjuntos.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

El coste del problema es O(N + M*ln**N), siendo N el numero de elementos del mapa (F*C), y M el numero de llamadas a unir y buscar:
	llamadas a buscar = numero de manchas
	llamadas a unir = numero de manchas * size de la mancha

	M = manchas + (manchas*size(mancha))

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Manchas {

private:
	vector<string> mapa;
	vector<vector<bool>> visit;
	int biggest;
	int fil, col;

	ConjuntosDisjuntos manchas;	// conjuntos de manchas

	const vector<pair<int, int>> directions = { {1, 0}, {1, 1},			// der y diagonal arriba der 
												{0, 1}, {-1, 1},		// arriba y diagonal arriba izq
												{-1, 0}, {-1, -1},		// izq y diagonal abajo izq
												{0, -1}, {1, -1} };		// abajo y diagonal abajo der


	int index(int i, int j) {
		return col * (i + 1) - (col - j);
	}

	bool inside(int i, int j) {
		return i < fil && i >= 0
			&& j < col && j >= 0;
	}

	// 
	void setManchas() {

		// recorremos todo el mapa para settear los conjuntos
		for (int i = 0; i < fil; i++) {
			for (int j = 0; j < col; j++) {
				char m = mapa[i][j];

				// la posicion esta manchada
				if (!visit[i][j] && m == '#') {

					// exploras las direcciones para ver si hay mas mancha
					checkMancha(i, j);

					// mira el tamaño
					int size = manchas.cardinal(manchas.buscar(index(i, j)));
					if (size > biggest) biggest = size;
				}

			}
		}

	};

	void checkMancha(int i, int j) {

		// marca esta posicion como visitada
		visit[i][j] = true;

		// recorre todas las direcciones para ver si la tiene que unir a algo
		for (pair<int, int> dir : directions) {

			int posi = i + dir.first;
			int posj = j + dir.second;

			//chequea en la direccion si hay una mancha (primero se guarda la fila y luego la columna)
			if (inside(posi, posj) && !visit[posi][posj] && mapa[posi][posj] == '#') {
				// si hay mancha, la une:

				int nueva = index(posi, posj);
				int old = index(i, j);

				manchas.unir(nueva, old);

				// seguimos mirando desde esta posicion donde hay mancha
				checkMancha(posi, posj);
			}
		}
	}


public:
	Manchas(vector<string> const& map, int F, int C) : mapa(map), biggest(0), fil(F), col(C), manchas(F*C), visit(F, vector<bool>(C, false))  {
		setManchas();
		
	}

	int getBiggest() {
		return biggest;
	}

	void update(int i, int j) {
		// se le añade la mancha
		mapa[i][j] = '#';

		// mira todas las direcciones 
		for (pair<int, int> dir : directions) {

			int posi = i + dir.first;
			int posj = j + dir.second;

			//chequea en la direccion si hay una mancha
			if (inside(posi, posj) && mapa[posi][posj] == '#') {

				// si hay mancha, la une:
				int nueva = index(posi, posj);
				int old = index(i, j);

				manchas.unir(nueva, old);
			}
		}


		// mira el size
		int size = manchas.cardinal(manchas.buscar(index(i, j)));
		if (size > biggest) biggest = size;
	};
};


bool resuelveCaso() {
	// leer los datos de la entrada
	int F, C;
	cin >> F >> C;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<string> mapa;
	string aux;
	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < F; i++) {
		cin >> aux;
		mapa.push_back(aux);
	}

	//
	Manchas m = Manchas(mapa, F, C);
	cout << m.getBiggest() << " ";

	int casos, x, y;
	cin >> casos;

	// lee los datos
	for (int i = 0; i < casos; i++) {
		cin >> x >> y;

		m.update(x - 1, y - 1);

		// escribir la solución
		cout << m.getBiggest() << " ";
	}
	cout << "\n";

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
