/** 
 * Implemente el  ́arbol Red-Black. Ejecute el algoritmo varias veces con datos desde 10 a 10 000 y mida el
tiempo medio de accesos partiendo desde la ra ́ız hasta un nodo aleatorio. Tendr ́a que obtener un gr ́afico
similar al que se muestra en Fig. 2
* 2. Analizar la complejidad computacional
**/

#include <iostream>
#include "rwfile.h"
#include "RBTree.h"
using namespace std;


 
// Constantes para RWFILE
const int MAXNUM = 100000; 
const int TAM = 100000;
std::string NUMFILE = "numbers.txt";
std::string TIMEFILE = "times.csv";

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //0. Generacion de archivo 'numbers.txt' con 100 000 datos
    /* srand(time(NULL));
    generadorNumRandom(NUMFILE, TAM, MAXNUM); */

    //1. Creación de un RBTree
    RBTree mytree;

    //2. Leer el archivo NUMFILE para agregar cada file Number a RBTree
    int num, counter=0;
    ifstream numbers;
    numbers.open(NUMFILE);
    while (numbers>>num)
    {
        // Insertar num a mytree
        cout<<num<<"\n";
        mytree.insert(num);
        counter++;
    }
    
    //3. Guardar el tiempo de acceso (búsqueda)
    //      con datos desde 10 a 10 000 y mida el tiempo medio de accesos 
    //      partiendo desde la ra ́ız hasta un nodo aleatorio.
    
    
    //4. Impresión de arbol
	mytree.prettyPrint();
    cout<<"\nReadFileCounter: "<<counter<<"\n\n";
	return 0;
}