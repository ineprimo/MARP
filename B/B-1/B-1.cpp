
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

Definicion recursiva: siendo i el indice del tesoro en el vector de tesoros y j la cantidad de aire que queda por usar

			|		t(i - 1, j)					si 3pi > j			si no hay aire para este tesoro miramos el siguiente
t(i, j) =	|
			|	max( t(i - 1, j),				si 3pi <= j			si hay aire para este tesoro miramos la mejor opcion entre este y el sigueinte,
			|		t(i - 1, j - pi) + vi)						cuando miramos este tesoro le restamos el aire que consume y sumamos a lo que devuelve 
																el valor del tesoro; cogemos el resultado que nos de mas oro

Casos base:

	t(i, 0) = 0		si no queda aire no podemos seguir resolviendo por lo que devolvemos el minimo valor que indique que esta resuelto este caso (0)
	t(0, j) = 0		si no quedan tesoros no podemos seguir resolviendo, hacemos igual que antes (0)

Llamada inicial: como estamos yendo del ultimo al primero de tesoros:

	t(tesoros.size(), T), siendo T la cantidad maxima de aire

Memoria y tabla: como queremos poder recuperar una posible solucion no podemos optimizar el espacio mas alla de una tabla bidimensional (la tabla minima 
necesaria para resolver el probelma)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct tesoro {
	int profundidad;
	int oro;
};

class Tesoro {
public:
	Tesoro(std::vector<tesoro> _t, int _T)
	{
		t = _t;
		T = _T;
		tabla = Matriz<int>(t.size() + 1, T + 1, -1);

		// llama a al resolucion del problema (rellena la tabla)
		maxGold = resuelve(t.size(), T);

		// recupera una de las posibles soluciones
		solution = getSolution();
	} 

	// devuelve una posible solucion
	std::vector<bool> getSol() {
		return solution;
	}

	int getMaxGold() {
		return maxGold;
	}
	int getNumT() {
		return numT;
	}


private:
	std::vector<tesoro> t;
	int T;
	int maxGold;
	Matriz<int> tabla;
	std::vector<bool> solution;
	int numT = 0;


	// resolucion del problema mediante programacion dinamica descendente recursiva
	int resuelve(int i, int j) {

		// miramos si esta en la tabla
		if (tabla[i][j] != -1) return tabla[i][j];

		// caso base
		if (i <= 0 || j <= 0) tabla[i][j] = 0;
		// si no le da el aire
		else if (3 * t[i - 1].profundidad > j) {
			// settea la tabla a 0
			tabla[i][j] = resuelve(i - 1, j);
		}
		else {
			// busca la solucion optima
			tabla[i][j] = max(resuelve(i - 1, j), 
				resuelve(i - 1, j - 3 * t[i - 1].profundidad) + t[i - 1].oro);
		}

		return tabla[i][j];
	}

	std::vector<bool> getSolution() {
		int n = t.size();
		int i = n, j = T;
		std::vector<bool> sol(n, false);

		while (i > 0 && j > 0) {
			// si es distinta la solucion es porque se ha cogido i
			if (tabla[i][j] != tabla[i - 1][j]) {
				sol[i - 1] = true;
				j -= 3*t[i - 1].profundidad;
				numT++;
			}
			i--;
		}
		return sol;
	}

};

bool resuelveCaso() {
	// leer los datos de la entrada
	int T;
	std::cin >> T;

	if (!std::cin)  // fin de la entrada
		return false;

	int n;
	std::cin >> n;
	std::vector<tesoro> tesoros;
	int aux1, aux2;
	for (int i = 0; i < n; i++) {
		std::cin >> aux1 >> aux2;
		tesoros.push_back({aux1, aux2});
	}

	// resolver el caso posiblemente llamando a otras funciones
	Tesoro t(tesoros, T);
	n = t.getSol().size();

	// escribir la solución
	std::cout << t.getMaxGold() << std::endl
		<< t.getNumT() << std::endl;

	for (int i = 0; i < n; i++) {
		if (t.getSol()[i]) {
			std::cout << tesoros[i].profundidad << " " << tesoros[i].oro << std::endl;
		}
	}
	std::cout << "---" << std::endl;

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
