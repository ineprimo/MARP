
/*@ <authors>
 *
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

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

//bool greaterThan(int i, int j) { return i.dia < j.dia 
//	|| (i.dia == j.dia) && i.hora > j.hora 
//	|| (i.dia == j.dia && i.hora == j.hora && i.min < j.min) ; }


struct fecha {
	int dia;
	int hora;
	int min;
};
struct pelicula {
	fecha f;
	int duracion;
};


fecha getNextHour(vector<pelicula> peliculas, int i) {

	int currHora = peliculas[i].f.hora, currMin = peliculas[i].f.min, currDia = peliculas[i].f.dia;

	int h = peliculas[i].duracion / 60;
	int m = peliculas[i].duracion % 60;

	int a = m + currMin;
	h += a / 60;
	currMin = a % 60;
	currHora += h;

	if (currHora > 24) {
		h = currHora%24;
		int dia = currHora / 24;
		currDia += dia;
		currHora = h;
	}

	return{ currDia, currHora, currMin };
}

int maraton(vector<pelicula> peliculas) {
	int cont = 1;
	int i = 0;
	int currHora = peliculas[0].f.hora, currMin = peliculas[0].f.min;
	int currDia = peliculas[0].f.dia;
	fecha next = getNextHour(peliculas, i);
	currDia = next.dia; 
	currHora = next.hora; 
	currMin = next.min;

	while (i < peliculas.size()) {
		if (currDia < peliculas[i].f.dia 
			|| (currDia == peliculas[i].f.dia && currHora < peliculas[i].f.hora) 
			|| (currDia == peliculas[i].f.dia && currHora == peliculas[i].f.hora && currMin <= peliculas[i].f.min)) {
			fecha next = getNextHour(peliculas, i);
			currDia = next.dia;
			currHora = next.hora;
			currMin = next.min;

			cont++;
		}
		i++;
	}
	return cont;
}



bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;

	if (N == 0)  // fin de la entrada
		return false;

	vector<pelicula> peliculas;
	int aux;
	pelicula p;
	std::string a;
	for (int i = 0; i < N; i++) {
		cin >> aux;
		p.f.dia = aux;

		// lee la hora
		cin >> a;
		p.f.hora = std::atoi(&a[0]);
		p.f.min = std::atoi(&a[3]);

		cin >> aux;
		p.duracion = aux;

		peliculas.push_back(p);
	}


	// los ordenamos de mayor a menor
	//std::sort(peliculas.begin(), peliculas.end());

	// solucion
	cout << maraton(peliculas) << "\n";

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
