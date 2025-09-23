
/*@ <authors>
 *
 *  Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


struct caso {
	char type;
	string name;
	int gravedad;
	int tiempo;
};

bool operator <(caso const& a, caso const& b) {
	return b.gravedad < a.gravedad ||
		(a.gravedad == b.gravedad && b.tiempo < a.tiempo);
};

bool operator >(caso const& a, caso const& b) {
	return b.gravedad > a.gravedad ||
		(a.gravedad == b.gravedad && b.tiempo < a.tiempo);
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	cin >> n;
	if (n == 0)  // fin de la entrada
		return false;

	priority_queue<caso, vector<caso>, greater<caso>> queue;
	for (int i = 0; i < n; i++) {
		caso c;
		caso sol;
		cin >> c.type;
		
		if (c.type == 'A') {
			sol = queue.top(); queue.pop();
			cout << sol.name << "\n";
		}
		else {
			cin >> c.name >> c.gravedad;
			c.tiempo = i;
			queue.push(c);
		}
		
	}
	cout << "---\n";


	// resolver el caso posiblemente llamando a otras funciones

	// escribir la solución

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
