
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "bintree.h"
// propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename T>
struct sol {
	T min;
	T max;
	int h;
};

template<typename T>
bool AVL(BinTree<T> tree, sol<T>& solution) {

	sol<T> solleft;
	sol<T> solright;

	if (tree.empty()) return true;

	solleft.min = tree.root();
	solleft.max = tree.root();
	solleft.h = 0;
	solright.min = tree.root();
	solright.max = tree.root();
	solright.h = 0;

	// si no tiene hijos
	if (tree.left().empty() && tree.right().empty()) {
		solution.h++;
		solution.min = tree.root();
		solution.max = tree.root();
		return true;
	}

	bool left = AVL(tree.left(), solleft);
	bool right = AVL(tree.right(), solright);

	if (!left || !right) return false;

	if (!tree.left().empty()) {
		if (solleft.max >= tree.root()) 
			return false;
	}
	if (!tree.right().empty()) {
		if (solright.min <= tree.root()) 
			return false;
	}

	// altura h
	if (abs(solleft.h - solright.h) > 1) 
		return false;

	// ajusta los min y max
	solution.min = solleft.min;
	solution.max = solright.max;

	if (solleft.h > solright.h) solution.h = solleft.h;
	else solution.h = solright.h;
	solution.h++;


	return true;

}

bool resuelveCaso() {
	// leer los datos de la entrada
	string type;
	cin >> type;
	if (!std::cin)  // fin de la entrada
		return false;

	if (type == "N") {
		BinTree<int> tree = read_tree<int>(std::cin);
		sol<int> solution;
		bool result = AVL<int>(tree, solution);

		if (result)
			cout << "SI" << endl;
		else
			cout << "NO" << endl;
	}
	else if(type == "P") {
		BinTree<string> tree = read_tree<string>(std::cin);
		sol<string> solution;
		bool result = AVL<string>(tree, solution);

		if (result)
			cout << "SI" << endl;
		else
			cout << "NO" << endl;
	}


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
