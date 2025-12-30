
/*@ <authors>
 *
 * MARP52 Ines Primo
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"

/*@ <answer>

Definicion recursiva: siendo i el indice de la izquierda, j el indice de la derecha y t el turno de la vaca; n es la cantidad de cubos y ci/cj el valor del cubo

					|	v(i + 1, j, !t)				si t == false && ci > cj			si es el turno de DEVORADORA 3000 y el cubo de la izquierda tiene mas comida
					|	v(i, j - 1, !t)				si t == false && ci <= cj			si es el turno de DEVORADORA 3000 y el cubo de la derecha tiene mas comida
	v(i, j , t) =	|	
					|	max( v(i + 1, j, !t) + ci,		si t == true					si es el turno de nuestra vaca compara ambas posibilidades
					|		 v(i, j - 1, !t) + cj)

casos base:
	v(i, j, t) = 0, si i > j
	v(i, j, t) = ci, si i == j

Llamada inicial:
	v(0, n - 1, true)

Memoria y tabla:

	[TODO]

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Vacas {
public:
	Vacas(std::vector<int> c) {
		cubos = c;
		n = cubos.size();

		tabla = Matriz<int>(n + 1,n + 1, -1);
		vec = std::vector<int>(n + 1, -1);

		// resuelve el problema
		//sol = v(0, n - 1, true);
		sol = v2();
	}

	int getSol() {
		return sol;
	}

private:
	std::vector<int> cubos;
	int n;
	int sol;
	Matriz<int> tabla;
	std::vector<int> vec;


	//
	int v(int i, int j, bool t) {
		if (i > j) return 0;

		// si este caso ya ha pasado
		if (tabla[i][j] != -1) 
			return tabla[i][j];

		// casos base
		else if (i == j && t) {
			return cubos[i];
		}

		// si es el turno de la vaca
		else if (t) {
			int a = v(i + 1, j, !t) + cubos[i];
			int b = v(i, j - 1, !t) + cubos[j];
			tabla[i][j] = max(a, b);
			return tabla[i][j];
		}
		// si es el turno de DEVORADORA LESBOTRON 3000  
		else {
			if(cubos[i] > cubos[j])
				return v(i + 1, j, !t);
			else 
				return v(i, j - 1, !t);
		}
	}

	// metodo ascendente para poder luego optimizar (????)
	int v2() {
		bool t = true;
		// conjunto vacio
		//tabla[0][0] = 0;
		vec[0] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = n; j >= 1; j--) {
				// si es el turno de la vaca
				if (t) {
					// hay que recorrer la tabla al reves creo lol
					vec[j];
					vec[j - 1];
					int a = tabla[i + 1][j] + cubos[i];
					int b = tabla[i][j - 1] + cubos[j];
					vec[j] = max(a, b);
				}
				// si es el turno de DEVORADORA LESBOTRON 3000  
				else {
					if (cubos[i - 1] > cubos[j])
						i++;
					else
						j--;
				}
				t = !t;
			}
		}
		return vec[n];

	};
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	std::cin >> n;

	if (n == 0)
		return false;
	 
	int aux;
	std::vector<int> cubos;
	for (int i = 0; i < n; i++) {
		std::cin >> aux;
		cubos.push_back(aux);
	}

	// resolver el caso posiblemente llamando a otras funciones
	Vacas v(cubos);

	// escribir la solución
	std::cout << v.getSol() << std::endl;

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
