#include <iostream>
#include <fstream>
#include "RBTree.h"

using namespace std;

/////////////////////GRAFICAR//////////////////////////////////
void escribirdot(ofstream &archivo, Nodo<T> *ARBOL, int i)
{
    if (ARBOL)
    {
        escribirdot(archivo, ARBOL->hijo[0], i); // recorrer por la izquierda
        if (ARBOL->hijo[0])
        {
            i++;
            archivo << ARBOL->dato << " -> " << ARBOL->hijo[0]->dato << "\n";
        }
        else
        {
            archivo << "izq" << i << " [style=invis]"
                    << "\n";
            archivo << ARBOL->dato << " -> izq" << i << " [style=invis]"
                    << "\n";
        }

        if (ARBOL->hijo[1])
        {
            archivo << ARBOL->dato << " -> " << ARBOL->hijo[1]->dato << "\n";
        }
        else
        {
            i++;
            archivo << "der" << i << " [style=invis]"
                    << "\n";
            archivo << ARBOL->dato << " -> der" << i << " [style=invis]"
                    << "\n";
        }
        escribirdot(archivo, ARBOL->hijo[1], i); // recorrer por la derecha
    }
}

void graficar()
{
    ofstream archivo;
    archivo.open("./arbolito.dot");
    if (archivo.is_open())
    {
        archivo << "digraph G { \n";
        escribirdot(archivo, raiz, 0);
        archivo << "}\n";
        archivo.close();
        system("dot -Tpng ./grafico.dot -o ./grafico.png ");
    }
    else
    {
        cout << "error al crear archivo";
    }
}