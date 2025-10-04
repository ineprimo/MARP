
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Dron {
	int a;
	int b;
};
//
//bool operator>(const Tarea& a, const Tarea& b) {
//
//	return a.init > b.init;
//}

bool resuelveCaso() {
	// leer los datos de la entrada
	int d, a, b;
	cin >> d >> a >> b;

	if (!std::cin)  // fin de la entrada
		return false;

	priority_queue<int> pilasA;
	priority_queue<int> pilasB;
	int aux;
	bool ended = false;

	for (int i = 0; i < a; i++) {
		cin >> aux;
		pilasA.push(aux);
	}

	for (int i = 0; i < b; i++) {
		cin >> aux;
		pilasB.push(aux);
	}

	priority_queue<Dron> drones;
	vector<int> pilas_gastadas_A;
	vector<int> pilas_gastadas_B;
	vector<int> horas_por_sabado;
	int horas;

	while (!pilasA.empty() && !pilasB.empty()) {
		horas = 0;

		// le damos las pilas al dron x
		int i = 0;
		while(i < d && !pilasA.empty() && !pilasB.empty()) {
			int a = pilasA.top(); pilasA.pop();
			int b = pilasB.top(); pilasB.pop();

			Dron dron = { a, b };

			if (a > b) {
				aux = a - b;
				horas += b;
				if(aux > 0)
					pilas_gastadas_A.push_back(aux);
			}
			else { 
				aux = b - a; 
				horas += a;
				if(aux > 0)
					pilas_gastadas_B.push_back(aux);
			}
			i++;
		}

		horas_por_sabado.push_back(horas);

		for (int j = 0; j < pilas_gastadas_A.size(); j++) {
			pilasA.push(pilas_gastadas_A[j]);
		}
		for (int j = 0; j < pilas_gastadas_B.size(); j++) {
			pilasB.push(pilas_gastadas_B[j]);
		}
		pilas_gastadas_A.clear();
		pilas_gastadas_B.clear();
	}
	

	for (int i = 0; i < horas_por_sabado.size(); i++) {
		cout << horas_por_sabado[i] << " ";
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
