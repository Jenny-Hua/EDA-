#include <iostream>
#include <fstream>
#include <ctime>
#include <climits>
#include <cmath>

using namespace std;

const int MAX = INT_MAX;
// Generar una cantidad de números aleatorios y almacenarlos en un archivo
// (El archivo se encuentra en la raiz del proyecto)
void generadorNumRandom(int tamanio)
{
    // Crear archivo
    ofstream numbersFile;
    numbersFile.open("./numbersFile.txt");

    int num;
    for(int i= 0; i < tamanio; i++)
    {
        num = 1 + rand() % (MAX);
        // cout << num<< " ";

        // Guardar los números en el archivo
        numbersFile << num << "\n";
    }
}

// Merge Sort 
void merge (int A[], int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int L[n1 + 1];
    int R[n2 + 1];

    for (int i = 0; i < n1; i++)
    {
        L[i] = A [left + i - 1];
    }
    for (int j= 0; j< n2; j++)
    {
        R[j] = A [middle + j];
    }

    L[n1+1] = INT_MAX;
    R[n2+1] = INT_MAX;

    int i = 1;
    int j = 1;
    for (int k = left; i <= right; i++)
    {
        
    }
    
}
void mergeSort(int A[], int left, int right)
{
    if (left < right)
    {
        int middle = floor((left + right) / 2);
        mergeSort(A, left, middle);
        mergeSort(A, middle + 1, right);
        merge(A, left, middle, right);
    }
}

int main ()
{
    // 06_11559 - Event Planning

#include <iostream>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // #ifndef ONLINE_JUDGE
    //     freopen("in.txt", "r", stdin);
    //     freopen("out.txt", "w", stdout);
    // #endif

    
    // Semilla random
    srand(time(NULL));
    generadorNumRandom (1000000);

   
    
    cout << endl;
    return 0;
}