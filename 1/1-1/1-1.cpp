
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
	bool isAVL;
	bool isEmpty;
	T min;
	T max;
	int h;
};

template<typename T>
sol<T> AVL(BinTree<T> tree) {

	sol<T> solution;

	if (tree.empty())
	{
		solution.isEmpty = true;
		solution.isAVL = true;
		solution.h = 0;
		return solution;
	}

	sol<T> left = AVL(tree.left());
	if (!left.isAVL)
		return left;
	sol<T> right = AVL(tree.right());
	if (!right.isAVL)
		return right;

	if (left.isEmpty && right.isEmpty) {
		solution.isEmpty = false;
		solution.isAVL = true;
		solution.min = tree.root();
		solution.max = tree.root();
		solution.h = 0;
		return solution;
	}


	// altura
	if (left.isEmpty) {
		solution = right;
		solution.min = tree.root();
		solution.h++;

		if (right.h > 1) {
			solution.isAVL = false;
			return solution;
		}
	}
	else if (right.isEmpty) {
		solution = left;
		solution.max = tree.root();
		solution.h++;

		if (left.h > 1) {
			solution.isAVL = false;
			return solution;
		}
	}
	else {
		if (abs(right.h - left.h) > 1) {
			solution.isAVL = false;
			return solution;
		}
		else {
			if (left.h > right.h)
				solution.h = left.h;
			else
				solution.h = right.h;
			solution.h++;
		}

		// orden

		if (left.max < tree.root() && right.min > tree.root()) {
			// si el mayor de la izquierda y el menor de la derecha mantienen el orden con la raiz,
			// suponemos que si estan ordenados ya que suponemos que los arboles anteriores estan ordenados
			solution.min = left.min;
			solution.max = right.max;
		}
		else {
			solution.isAVL = false;
			return solution;
		}
	}
	
	solution.isAVL = true;
	solution.isEmpty = false;

	return solution;
}

// metodo auxiliar
template<typename T>
sol<T> isAVL(BinTree<T> tree) {
	// compara soluciones
	sol<T> solution;

	// casos base
	if (tree.empty()) {
		solution.isEmpty = true;
		solution.isAVL = true;
		solution.h = 0;
		return solution;
	}
	
	// recursion
	sol<T> left = isAVL<T>(tree.left());
	sol<T> right = isAVL<T>(tree.right());

	if (left.isEmpty && right.isEmpty) {
		solution.min = tree.root();
		solution.max = tree.root();
		solution.h = 1;
		solution.isEmpty = false;
		return solution;
	}
	if (left.isEmpty) {
		solution = right;
		if (right.min < tree.root()) {
			solution.min = right.min;
			solution.isAVL = false;
		}
		else {
			solution.min = tree.root();
		}

		if (right.h > 1)
			solution.isAVL = false;
		return solution;
	}
	if (right.isEmpty) {
		solution = left;
		if (left.max > tree.root()) {
			solution.max = left.max;
			solution.isAVL = false;
		}
		else
			solution.max = tree.root();
		if (left.h > 1)
			solution.isAVL = false;
		return solution;

	}


	// is avl
	if (left.isAVL && right.isAVL)
		solution.isAVL = true;
	else {
		solution.isAVL = false;
		return solution;
	}

	// h
	int diff = left.h - right.h;
	if (abs(diff) >= 1) {
		solution.isAVL = false;
	}

	if (left.h > right.h)
		solution.h = left.h;
	else
		solution.h = right.h;

	// se asegura del orden
	if (!left.isEmpty && !right.isEmpty) {
		if (left.min > right.min || left.max > right.min ||
			right.min < left.max || right.max < right.max ||
			left.max > tree.root() || right.min < tree.root()) {
			solution.isAVL = false;
		}

		if (left.max > tree.root()) {
			solution.isAVL = false;
			solution.max = left.max;
		}
		else
			solution.max = right.max;
		if (right.min < tree.root()) {
			solution.isAVL = false;
			solution.max = left.max;
		}
		else
			solution.min = left.min;


		// lmao
		// min

		// max
	}

	solution.isEmpty = false;

	solution.h++;

	// return maximo
	return solution;
}


bool resuelveCaso() {
	// leer los datos de la entrada
	string type;
	cin >> type;
	if (!std::cin)  // fin de la entrada
		return false;

	if (type == "N") {
		BinTree<int> tree = read_tree<int>(std::cin);
		sol<int> solution = AVL<int>(tree);

		if (solution.isAVL)
			cout << "SI" << endl;
		else
			cout << "NO" << endl;
	}
	else if(type == "P") {
		BinTree<string> tree = read_tree<string>(std::cin);
		sol<string> solution = AVL<string>(tree);

		if (solution.isAVL)
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
