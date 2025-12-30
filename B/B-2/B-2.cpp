
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

Definicion recursiva: siendo i el indice desde la posicion 0 de la palabra y j el indice de la posicion n - 1 de la palabra, siendo n el tamaño de la palabra

				|	p(i + 1, j - 1)				si pi == pj			si ambos extremos son iguales simplemente vamos a la siguente letra
	p(i, j) =	|
				|	min( p(i + 1, j),			si pi != pj			si ambos extremos son distintos, calculamos la mejor opcion ya sea añadiendo
				|		 p(i, j - 1)) + 1							la letra de la izquierda o la de la derecha, le sumamos 1 porque hay que añadir
																	una letra

Casos base:
	p(i, j) = 0,	si i > j
	p(i, j) = 1,	si i == j

Llamada inicial:
	p(0, n)

Tabla y memoria: Como queremos poder reconstruir el palindromo, no podemos minimizar el uso de memoria mas alla de una tabla bidimensional (n,n), aun que solo se use
el triangulo superior por encima de la diagonal principal

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


class Palindromo {
public:
	Palindromo(std::string _p) {
		palabra = _p;

		tabla = Matriz<int>(palabra.size() + 1, palabra.size() + 1, -1);

		// resuelve el caso
		extras = p(0, palabra.size() - 1);

		// devuelve una solucion
		sol = rec(0, palabra.size() - 1);
	}

	int getExtra() { return extras; }
	std::string getPalindromo() { return sol; }

private:
	int extras = 0;
	std::string palabra;
	std::string sol;
	Matriz<int> tabla;

	// descendente recursiva porque queremos rehacer la solucion
	int p(int i, int j) {

		// si el caso ya existe
		if (tabla[i][j] != -1) return tabla[i][j];

		// casos base
		if (j - i < 0) return 0;		// no hay letras
		else if (j - i == 0) return 0;	// solo hay 1 letra

		// si ambos lados son iguales no hay que añadir nada
		else if (palabra[i] == palabra[j]) {
			tabla[i][j] = p(i + 1, j - 1);
			return tabla[i][j];
		}
		else {
			// si hay un lado que es distintos tenemos que añadir una letra
			tabla[i][j] = min(p(i + 1, j), p(i, j - 1)) + 1;
			return tabla[i][j];
		}
	}


	// mas comodo hacerlo recursivo
	std::string rec(int i, int j) {

		if (i > j) return {};
		else if (i == j) 
			return { palabra[i] };
		else if (palabra[i] == palabra[j])
			return palabra[i] + rec(i + 1, j - 1) + palabra[j];
		// si esta solucion es > que la de la izquierda (1) es porque añadir a la derecha es optimo
		else if(tabla[i][j] > tabla[i + 1][j])
			return palabra[i] + rec(i + 1, j) + palabra[i];
		// si el valor en i, j es menor que el de i+1,j es porque la solucion es la otra
		else
			return palabra[j] + rec(i, j - 1) + palabra[j];
	}

};

bool resuelveCaso() {
	// leer los datos de la entrada
	std::string palabra;
	std::cin >> palabra;

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	Palindromo p(palabra);

	// solucion
	std::cout << p.getExtra() << " " << p.getPalindromo() << std::endl;

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
