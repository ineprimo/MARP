
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

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

EntInf min(EntInf& const a, EntInf& const b) {
	if (a < b)
		return a;
	else
		return b;
}

EntInf cambio(vector<int> const& M, int C) {
	
	// crea la matriz de size (n+1, c+1) y la settea toda a 1 porque el numero maximo de monedas que hay de cada 'tipo' es 1
	int n = M.size();
	Matriz<EntInf> billetes(n+1, C+1, Infinito);

	// pone la primera posicion a 0
	billetes[0][0] = 0;


	//
	for (int i = 1; i <= n; ++i) {

		// pone la primera columna a 0 (la primera posicion de la fila i)
		billetes[i][0] = 0;

		// recorre la fila i para mirar los casos recursivos
		for (int j = 1; j <= C; ++j) {

			if (j == 500)
				int a = 0;
			else if (j == 1000)
				int a = 0;
			else if (j == 1400)
				int a = 0;

			// siempre se tiene que poder pagar por lo que no hay caso recursivo en el que no se pueda pagar (te puedes pasar)
			// este caso simplemente pone la cantidad 
			if (M[i - 1] > j) {
				billetes[i][j] = C;
			}
			// si si se puede pagar la cantidad j con el tipo de billete Mi
			else {
				EntInf a = billetes[i - 1][j];
				EntInf b = billetes[i][j - M[i - 1]] + 1;
				billetes[i][j] = min(a, b);

				EntInf sol1 = billetes[i][500];
				EntInf sol2 = billetes[i][1000];
				EntInf sol3 = billetes[i][1400];

				int hola = 0;
			}
		}
	}
	return billetes[n][C];
}

bool resuelveCaso() {
	// leer los datos de la entrada

	int C, N;
	cin >> C >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	// vector con los valores de los billetes
	vector<int> billetes = vector<int>(0);
	int b;
	for (int i = 0; i < N; i++) {
		cin >> b;
		billetes.push_back(b);
	}

	// resolver el caso posiblemente llamando a otras funciones
	EntInf a = cambio(billetes, C);

	// escribir la solución
	cout << a << "\n";

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
