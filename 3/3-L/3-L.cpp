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
using namespace std;

#include "IndexPQ.h"

/*@ <answer>

 Sustituye este párrafo por un comentario general sobre la solución,
 explicando cómo se resuelve el problema y cuál es el coste de la solución,
 en función del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>


struct Canal {

    int id;
    int viewers;
    int prime_mins;
};

bool operator>(const Canal& a, const Canal& b) {
    return a.viewers > b.viewers ||
        (a.viewers == b.viewers && a.id < b.id);
}


struct PrimeTime {

    int id;
    int viewers;
    int prime_mins;
};

bool operator>(const PrimeTime& a, const PrimeTime& b) {
    return a.prime_mins > b.prime_mins ||
        (a.prime_mins == b.prime_mins && a.id < b.id);
}



bool resuelveCaso() {

    // leemos la entrada
    int D, C, N;
    cin >> D >> C >> N;
    if (!cin) return false;


    //
    IndexPQ<int, Canal, greater<Canal>> queue;
    for (int i = 0; i < C; i++) {
        int viewers;
        cin >> viewers;
        Canal c = Canal({i+1, viewers, 0});

        queue.push(i+1, c);
    }



    // leer el resto del caso y resolverlo
    int cont_mins = 0, mins, canal_id, viewers_canal, past_mins = 0;
    

    // primer caso
    cin >> mins;
    // actualiza el primetime
    Canal c = queue.top().prioridad;

    c.prime_mins += mins - past_mins;

    queue.update(c.id, c);
    past_mins = mins;

   
    int i = 0;

    while (i <N) {

        cin >> canal_id >> viewers_canal;

        while (canal_id > -1) {

            // magia de queues

            // actualiza los viewers
            Canal aux = Canal({ canal_id, viewers_canal,  queue.priority(canal_id).prime_mins });

            queue.update(canal_id, aux);


            cin >> canal_id;
               
            if(canal_id != -1)
                cin >> viewers_canal;
        }

        // actualiza el primetime
        Canal c = queue.top().prioridad;

        past_mins = mins;
        cin >> mins;

        c.prime_mins += mins - past_mins;

        queue.update(c.id, c);

        i++;
    }
    
    // ultimo caso
    c = queue.top().prioridad;


    c.prime_mins += D - past_mins;

    queue.update(c.id, c);


    // escritura
     //
    IndexPQ<int, PrimeTime, greater<PrimeTime>> pt_queue;
    i = 0;
    while (i < queue.size()) {

        c = queue.top().prioridad; queue.pop();

        if (c.prime_mins > 0) {

            PrimeTime pt = { c.id, c.viewers, c.prime_mins };
            pt_queue.push(i, pt);

            i++;
        }
    }

    int size = pt_queue.size();
    for (int i = 0; i < size; i++) {
        PrimeTime pt = pt_queue.top().prioridad; pt_queue.pop();

        cout << pt.id << " " << pt.prime_mins << '\n';
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
