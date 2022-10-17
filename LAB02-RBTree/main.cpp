/**
 * Implemente el  ́arbol Red-Black. Ejecute el algoritmo varias veces con datos desde 10 a 10 000 y mida el
tiempo medio de accesos partiendo desde la ra ́ız hasta un nodo aleatorio. Tendr ́a que obtener un gr ́afico
similar al que se muestra en Fig. 2
* 2. Analizar la complejidad computacional
**/

#include <iostream>
#include <chrono>
#include "rwfile.h"
#include "RBTree.h"
using namespace std;
using namespace std::chrono;

// Constantes para RWFILE
const int MAXNUM = 10000;
const int TAM = 10000;
string NUMFILE = "numbers.txt";
string TIMEFILE = "times.csv";

// Archivo para gráfico
string GRAPHDOT = "./graph.dot";
string GRAPHFILE = "./graph.dot";

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int forInterval = 100;
    int nCase = MAXNUM / 100; // valor inicial 100
    for (; nCase <= MAXNUM; nCase += 100)
    {
        // 1. Creación de un RBTree
        RBTree mytree;

        // 2. Insertar nCase elementos (comenzando por 100)
        int counter = 0;
        while ( ++counter <= nCase)
        {
            mytree.insert(counter);
        }

        // 3. Guardar el tiempo de acceso (búsqueda)
        std::ofstream outfile;
        outfile.open(TIMEFILE, std::ios::app);
        outfile << "\nCase " << nCase << "\n";
        outfile.close();
        int pruebas[7] = {10, 20, 30, 40, 50, 60, 70};
        for (int i = 0; i < 7; i++)
        {
            // Números de prueba para la búsqueda
            int k = pruebas[i];

            // Calculo de la duracion (mili)
            auto start = high_resolution_clock::now();
            mytree.search(k);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start);

            // Guardar tiempo de busqueda
            timesFile(TIMEFILE, k, duration);
        }
    }
    // 4. Impresión de arbol
    // mytree.graphic(GRAPHDOT);
    return 0;
}