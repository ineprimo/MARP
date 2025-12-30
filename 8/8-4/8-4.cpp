
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


fecha getNextHour(vector<pelicula> const& peliculas, int const& i) {

	int currHora = peliculas[i].f.hora, 
		currMin = peliculas[i].f.min, 
		currDia = peliculas[i].f.dia;

	int min = currMin + peliculas[i].duracion + 10;

	int h = min / 60;
	int m = min % 60;

	currMin = m;
	currHora += h;

	// si pasa de dia
	if (currHora > 24) {
		currDia++;
		currHora = currHora % 24;
	}

	return{ currDia, currHora, currMin };
}

bool earlierThan(const pelicula& a, const pelicula& b)
{
	return a.f.dia < b.f.dia
		|| (a.f.dia == b.f.dia && a.f.hora < b.f.hora)
		|| (a.f.dia == b.f.dia && a.f.hora == b.f.hora && a.f.min < b.f.min)
		|| (a.f.dia == b.f.dia && a.f.hora == b.f.hora && a.f.min == b.f.min && a.duracion < b.duracion);
}

bool earlierThanDate(const fecha& a, const fecha& b)
{
	return a.dia < b.dia
		|| (a.dia == b.dia && a.hora < b.hora)
		|| (a.dia == b.dia && a.hora == b.hora && a.min <= b.min);
}

int maraton(vector<pelicula> peliculas) {
	int cont = 1;
	int i = 1;

	fecha currFecha = getNextHour(peliculas, 0);

	while (i < peliculas.size()) {
		if (earlierThanDate(currFecha, peliculas[i].f)) {

			currFecha = getNextHour(peliculas, i);
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


	std::sort(peliculas.begin(), peliculas.end(), earlierThan);

	// solucion
	cout << maraton(peliculas) << std::endl;

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
