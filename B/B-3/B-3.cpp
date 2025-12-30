
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"

/*@ <answer>



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct entrada {
	int grupos;
	int precio;
};

class Festival {

public:
	Festival(std::vector<entrada> e, int P) {
		entradas = e;
		presupuesto = P;
		n = entradas.size();

		// se puede optimizar a un vector
		tabla = Matriz<int>(n + 1, presupuesto + 1, 0);
		vec = std::vector<int>(presupuesto + 1, 0);

		// resuelve el problema
		num = f();

	}

	int maxGroups() {
		return num;
	}

private:
	std::vector<entrada> entradas;
	int presupuesto;
	int num = 0;
	int n;
	Matriz<int> tabla;
	std::vector<int> vec;
	

	// metodo ascendente para mejorar luego en espacio la solucion
	int f() {
		tabla[0][0] = 0;
		for (int i = 1; i <= n; i++) {
			// settea el conjunto vacio
			tabla[i][0] = 0;

			// recorre los precios
			for (int j = 1; j <= presupuesto; j++) {

				// si no da para ir a este festival
				if (entradas[i - 1].precio > j)
				{
					tabla[i][j] = tabla[i - 1][j];
				}
				// si si que da el presupuesto
				else {
					// opcion si no usamos este festival (pasamos al siguiente)
					int a = tabla[i - 1][j];
					// opcion si usamos este festival (hay que quitarle lo que cuesta y sumarle los grupos que vamos a ver)
					int b = tabla[i - 1][j - entradas[i - 1].precio] + entradas[i - 1].grupos;

					// settea la solucion
					tabla[i][j] = max(a, b);
				}
			}
		}
		return tabla[n][presupuesto];
	}



};

bool resuelveCaso() {
	// leer los datos de la entrada
	int P, N;
	std::cin >> P >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	int num, precio;
	std::vector<entrada> entradas;
	for (int i = 0; i < N; i++) {
		std::cin >> num >> precio;
		entradas.push_back({num, precio});
	}

	// resolver el caso posiblemente llamando a otras funciones
	Festival f(entradas, P);

	// solucion
	std::cout << f.maxGroups() << std::endl;

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
