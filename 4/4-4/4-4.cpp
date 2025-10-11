
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

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

using Mapa = vector<string>;

class Mancha {
private:
	int F, C;
	vector<vector<bool>> visit;
	int num;
	int maxim;

	bool correcta(int i, int j) const {
		return 0 <= i&& i < F && 0 <= j && j < C;
	}

	const vector<pair<int, int>>dirs = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	
	int dfs(Mapa const& m, int i, int j) {
		visit[i][j] = true;
		int tam = 1;
		for (auto d : dirs) {
			int ni = i + d.first;
			int nj = j + d.second;
			if (correcta(ni, nj) && m[ni][nj] == '#' && !visit[ni][nj]) {
				tam += dfs(m, ni, nj);
			}
		}
		return tam;
	}


public:
	Mancha(Mapa const& M) : F(M.size()), C(M[0].size()),
							visit(F, vector<bool>(C, false)), num(0), maxim(0) {
		for (int i = 0; i < F; ++i) {
			for (int j = 0; j < C; ++j) {
				if (!visit[i][j] && M[i][j] == '#') {
					++num;
					int nt = dfs(M, i, j);
					maxim = max(maxim, nt);
				}
			}
		}
	};

	int numero() { return num; }
	int maximo() { return maxim; }
};


bool resuelveCaso() {
	// leer los datos de la entrada
	int F, C;
	cin >> F >> C;
	if (!std::cin)  // fin de la entrada
		return false;

	Mapa mapa(F);
	for (string & linea : mapa) {
		cin >> linea;
	}

	// resolver el caso posiblemente llamando a otras funciones
	Mancha manchas(mapa);

	// escribir la solución
	cout << manchas.numero() << " " << manchas.maximo() << "\n";

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
