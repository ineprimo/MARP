
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

/*@ <answer>

Definicion recursiva, siendo i el indice del sector que estamos mirando y j la cantidad de puntos que quedan por conseguir:

					|
					|						diana(i - 1, j)					si s[i] > j			// Si el sector actual da mas puntos de los que
	diana(i, j) =	|																			// nos quedan, lo descartamos
					|	min( diana(i - 1, j), diana(i, j - s[i]) + 1)		si s[i] <= j		// si el sector actual nos sirve para llegar a puntos
					|																			// porque no se pasa, elegimos la solucion que nos de
					|																			// una cantidad menor de sectores, ya sea descartando
																								// este sector o usandolo
Casos base:
	diana(0, j) = +Inf	-> no hay nada con lo que conseguir j, no hay solucion
	diana(i, 0) = 0		-> no hay nada que conseguir, la solucion es 0 

Llamada inicial:
	diana(sectores.size(), puntos)

Tabla:
Usamos una tabla de tamaño (sectores.size() + 1, puntos + 1) para poder representar todos los posibles puntos (del 0 a puntos) asi como el conjunto
vacio, para calcular la solucion (i, j) requeremos de las casillas (i - 1, j) y (i, j - s[i])

Memoria:
Se podria mejorar el uso de memoria transformando la tabla en un vector ya que unicamente nos hace falta la casilla del mismo j cuando cambia el i asi
que la podemos sobreescribir. Ademas, la solucion aun se podria recuperar aun teniendo solo un vector y no toda la tabla. 

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


class Diana {
public:
	Diana(std::vector<int> _sectores, int _puntos) {
		sectores = _sectores;
		puntos = _puntos;

		int n = sectores.size();
		// crea la tabla setteandola toda a infinito representando esto que no tiene solucion
		// el tamanyo de la tabla es el numero de sectores que haya + 1 para poder representar el conjunto vacio en i
		// y todos los puntos de 0 a puntos, +1 (en el primer caso es 100 +1), por el conjunto vacio tmb
		tabla = Matriz<EntInf>(n + 1, puntos + 1, Infinito);

		// resuelve
		cantidad = diana();
	}

	// devuelve la cantidad
	EntInf getCant() { return cantidad; }
	// rehace una de las posibles soluciones, si es que la hay
	std::vector<int> returnSolution() {
		std::vector<int> sol;
		if (cantidad != Infinito) {
			int i = sectores.size(), j = puntos;
			// mientras no se haya llegado a los puntos queridos
			while (j > 0) {
				// si cogemos este sector + la solucion de 'arriba' es igual a esta, significa que podemos coger este sector
				if (sectores[i - 1] <= j && tabla[i][j] != tabla[i - 1][j]) {
					sol.push_back(sectores[i - 1]);
					j -= sectores[i - 1];
				}
				// si no cogemos este sector
				else i--;
			}
		}
		return sol;
	}

private:
	std::vector<int> sectores;
	int puntos;
	Matriz<EntInf> tabla;
	EntInf cantidad;
	
	// rellena la tabla y saca la cantidad de sectores optima. si devuelve Infinito es que no hay solucion
	EntInf diana() {

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
		return tabla[sectores.size()][puntos];
	}
};



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

	Diana d(sectores, P);

	EntInf sol = d.getCant();
	std::vector<int> solution = d.returnSolution();

	// 
	if (sol == Infinito) {
		std::cout << "Imposible" << std::endl;
		return true;
	}

	std::cout << sol << ": "; 
	for (int& i : solution) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

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
