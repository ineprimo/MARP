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


/*@ <answer>

    El problema se resuelve calculando el grupo mayor de instrumentos (mediante el operador <) y recorrer
    el numero de partituras hasta quedarte sin. En el caso de tener mas partituras que musicos no se tiene 
    en cuenta puesto que siempre dara que el grupo mayor es de 1 musico. 

    Para el operador se tiene en cuenta los casos en los que el numero de partituras sea divisor del numero de
    musicos como el que no. En el caso de empatar se compara por id, que representa el orden de lectura.

    la complejidad del algoritmo es de 0(PlogN) en tiempo, siento P el numero de partituras y N la longitud de la
    cola de prioridad, ya que se recorren todas las partituras y en cada vuelta se efectua un push con complejidad logN
    respecto de su tamaño.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

struct Instrumento {
    int id;
    int musicos;
    int partituras;
};

bool operator <(Instrumento const& a, Instrumento const& b) {
    int numA, numB;

    // diferencia si es divisor el numero de partituras o no del numero de musicos para ambos instrumentos
    // instrumento a
    if (a.musicos / a.partituras == 0)
        numA = a.musicos / a.partituras;
    else
        numA = (a.musicos + (a.partituras - 1)) / a.partituras;

    // instrumento b
    if (b.musicos / b.partituras == 0)
        numB = b.musicos / b.partituras;
    else
        numB = (b.musicos + (b.partituras - 1)) / b.partituras;

    // comparacion normal, si empatan elige por id (por orden de lectura)
    return (numA < numB ) || 
        (numA == numB && a.id < b.id);
};

bool resuelveCaso() {

    // leemos la entrada
    int P, N;
    cin >> P >> N;

    if (!cin)
        return false;

    // si hay menos partituras que tipos de instrumentos no se puede dividir como queremos
    if (P < N) return false;

    // leer el resto del caso y resolverlo
    // crea una cola de prioridad por cantidad maxima de musicos
    // y le da una partitura a cada instrumento si es que el numero de instrumentos
    // y partituras es coherente
    priority_queue<Instrumento> orquestra;
    int num, aux;
    Instrumento ins;
    Instrumento auxIns;
    int i = 0;
    while (i<N && P > 0) {
        cin >> num;
        ins = { i, num, 1 };

        orquestra.push(ins);

        // les coloca una partitura a cada grupo
        P--;
        i++;
    }


    // recorre las partituras restantes 
    while (P>0) {

        // recoge el grupo con mas integrantes
        ins = orquestra.top(); orquestra.pop();

        // le da una partitura
        ins.partituras++;

        orquestra.push(ins);

        P--;
    }


    // para calcular el grupo mayor tambien tiene que tener en cuenta los casos donde es divisor o no
    ins = orquestra.top();
    int sol;
    if (ins.musicos % ins.partituras == 0)
        sol = ins.musicos / ins.partituras;
    else
        sol = (ins.musicos + (ins.partituras - 1)) / ins.partituras;

    // solucion
    cout << sol << endl;

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
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
