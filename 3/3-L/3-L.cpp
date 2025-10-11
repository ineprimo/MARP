/*@ <authors>
 *
 * MARP52 Ines Primo
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
#include <unordered_map>
using namespace std;

#include "IndexPQ.h"

/*@ <answer>

esoty probando la solucion del profe porque la mia no va :(

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>



bool resuelveCaso() {

    // leemos la entrada
    int D, C, N;
    cin >> D >> C >> N;
    if (!cin) return false;
    //
    IndexPQ<int, greater<int>> viewers(C);
    for (int i = 0; i < C; ++i) {
        int v;
        cin >> v;
        viewers.update(i, v);
    }
    unordered_map<int, int> minutos;
    int anterior = 0;
    for (int i = 0; i < N; ++i) {
        int tiempo;
        cin >> tiempo;
        minutos[viewers.top().elem] += tiempo - anterior;
        int canal;
        cin >> canal;
        while (canal != -1) {
            int espectador;
            cin >> espectador;
            viewers.update(canal - 1, espectador);
            cin >> canal;
        }
        anterior = tiempo;
    }
    minutos[viewers.top().elem] += D - anterior;

    // resultado
    vector<pair<int, int>> sol;
    for (auto p : minutos) {
        sol.push_back({p.first, p.second});
    }
    // sort con expresion lambda
    sort(sol.begin(), sol.end(),
        [](pair<int, int> a, pair<int, int> b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        });

    for (int i = 0; i < sol.size(); ++i) {
        cout << sol[i].first + 1 << " " << sol[i].second << "\n";
    }
    cout << "---\n";
    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
