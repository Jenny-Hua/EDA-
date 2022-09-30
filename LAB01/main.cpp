#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <ctime>
#include <climits>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int MAXNUM = 10000; // INT_MAX;
const int TAM = 1500000;
string NUMFILE = "in.txt";
string TIMEFILE = "times.txt";

/*************************
 *  AUXILIARY FUNCTIONS
 *************************/
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
        cout << A[i] << "\n";
    cout << endl;
}

void generadorNumRandom(int tamanio)
{
    // Crear archivo
    ofstream numbersFile;
    numbersFile.open(NUMFILE);

    int num;
    for (int i = 0; i < tamanio; i++)
    {
        num = 1 + rand() % (MAXNUM);
        numbersFile << num << "\n";
    }
    numbersFile.close();
}

// Guardar los tiempos de ejecución 
void timesFile(string name, microseconds duration)
{
    // Crear archivo
    ofstream outfile;
    outfile.open(TIMEFILE, ios::app);
    int _duration = duration.count();
    outfile << name << ", " <<_duration << "\n";
    outfile.close();
}

// Implementacion de los siguientes algoritmos:
//   1. Bubble sort
//   2. Heap sort
//   3. Insertion sort
//   4. Selection sort
//   5. Shell sort
//   4. Selection sort
//   5. Shell sort
//   6. Merge sort
//   7. Quick sort

/*************************
 *   1. Bubble sort
 *************************/

void bubbleSort(int array[], int n)
{
    for (int step = 0; step < n; ++step)
    {
        for (int i = 0; i < n - step; ++i)
        {
            if (array[i] > array[i + 1])
            {
                swap(&array[i], &array[i + 1]);
            }
        }
    }
}

/*************************
 *   2. Heap sort
 *************************/
void heapify(int array[], int n, int i)
{
    // 1ro. Encontrar el elemento más grande entre una raiz y sus 2 hijos
    int high = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && array[left] > array[high])
        high = left;

    if (right < n && array[right] > array[high])
        high = right;

    // 2do. Intercambiar y continuar acumulando si la raíz no es la más grande
    if (high != i)
    {
        swap(&array[i], &array[high]);
        heapify(array, n, high);
    }
}

void heapSort(int array[], int n)
{
    // 1ro. Construir el max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    // Heap sort
    for (int i = n - 1; i >= 0; i--)
    {
        swap(&array[0], &array[i]);

        // Heapify la raíz para volver a obtener el elemento más alto en la raíz
        heapify(array, i, 0);
    }
}

/*************************
 * 3. Insertion sort
 *************************/
void insertionSort(int array[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = array[i];
        int j = i - 1;

        while (key < array[j] && j >= 0)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

/*************************
 *   4. Selection sort
 *************************/
void selectionSort(int array[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minPos = i;
        for (int i = i + 1; i < n; i++)
        {
            if (array[i] < array[minPos])
                minPos = i;
        }
        swap(&array[minPos], &array[i]);
    }
}

/*************************
 *   5. Shell sort
 *************************/
void shellSort(int array[], int n)
{
    // Para reorganizar los elemntos en intervalos de mitad del tamaño que el anterior
    for (int interval = n / 2; interval > 0; interval /= 2)
    {
        for (int i = interval; i < n; i += 1)
        {
            int temp = array[i];
            int j;
            for (j = i; j >= interval && array[j - interval] > temp; j -= interval)
            {
                array[j] = array[j - interval];
            }
            array[j] = temp;
        }
    }
}

/*************************
 *   6. Merge sort
 *************************/
void merge(int Arr[], int l, int m, int r)
{

    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = Arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = Arr[m + 1 + j];
    i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            Arr[k] = L[i];
            i++;
        }
        else
        {
            Arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        Arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        Arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int Arr[], int N)
{
    for (int sub_size = 1; sub_size < N; sub_size *= 2)
    {
        for (int L = 0; L < N; L += (2 * sub_size))
        {
            int Mid = min(L + sub_size - 1, N - 1);
            int R = min(L + 2 * sub_size - 1, N - 1);
            // función para fusionar dos subarreglos de 
            // tamaño sub_size a partir de L y Mid
            merge(Arr, L, Mid, R);
        }
    }
}

/*************************
 *   7. Quick sort
 *************************/
int partition(int array[], int start, int end)
{
    // Pivote: elemento mas a la derecha
    int pivot = array[end];
 
    // alinear los elementos menores a la izquierda del pivote o a la derecha si son mayores
    int pIndex = start;
 
    // los elementos menores al pivote se alinean a la izquierda del pivote
    // pIndex se incrementa
    for (int i = start; i < end; i++)
    {
        if (array[i] <= pivot)
        {
            swap(&array[i], &array[pIndex]);
            pIndex++;
        }
    }
 
    swap (&array[pIndex], &array[end]);

    return pIndex;
}
 
void quickSort(int array[], int n)
{
    // Almacenar el indice de inicio y fin de los subarray en un stack
    stack<pair<int, int>> s;
 
    // indices del array dado
    int start = 0;
    int end = n - 1;
 
    s.push(make_pair(start, end));
 
    while (!s.empty())
    {
        start = s.top().first, end = s.top().second;
        s.pop();
 
        // Reordenar el arreglo usando un pivot
        int pivot = partition(array, start, end);
 
        // Subarrays con elementos menores al pivote 
        // sus indidces se envian al stack
        if (pivot - 1 > start) {
            s.push(make_pair(start, pivot - 1));
        }
 
        // Subarrays con elementos menores al pivote 
        // sus indidces se envian al stack
        if (pivot + 1 < end) {
            s.push(make_pair(pivot + 1, end));
        }
    }
}

/*************************
 *        MAIN
 *************************/
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.tie(NULL);

    // #ifndef ONLINE_JUDGE
    //     freopen("in.txt", "r", stdin);
    //     freopen("out.txt", "w", stdout);
    // #endif

    // Semilla random
    srand(time(NULL));
    
    // GENERADOR DE NUMEROS
    //  generadorNumRandom(TAM);

    // Storing in Array
    int A[TAM];
    int num;
    ifstream infile(NUMFILE);
    for (int i = 0; i < TAM; i++)
    {
        infile >> num;
        A[i] = num;
    }

    // Switch between sort Algorithms:
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    microseconds duration;
    
    int caso = 7;
    switch(caso ) {
        case 1:
            start = high_resolution_clock::now();
            bubbleSort(A, TAM);    
            stop = high_resolution_clock::now();
            //duration = duration_cast<microseconds>(stop - start);
            timesFile("Bubble", duration_cast<microseconds>(stop - start));
            break;
        case 2:
            start = high_resolution_clock::now();
            heapSort(A, TAM);    
            stop = high_resolution_clock::now();
            timesFile("Heap", duration_cast<microseconds>(stop - start));
            break;
        case 3:
            start = high_resolution_clock::now();
            insertionSort(A, TAM);    
            stop = high_resolution_clock::now();
            timesFile("Insertion", duration_cast<microseconds>(stop - start));
            break;
        case 4:
            start = high_resolution_clock::now();
            selectionSort(A, TAM);    
            stop = high_resolution_clock::now();
            timesFile("Selection", duration_cast<microseconds>(stop - start));
            break;
        case 5:
            start = high_resolution_clock::now();
            shellSort(A, TAM);    
            stop = high_resolution_clock::now();
            timesFile("Shell", duration_cast<microseconds>(stop - start));
            break;
        case 6:
            start = high_resolution_clock::now();
            mergeSort(A, TAM);    
            stop = high_resolution_clock::now();
            timesFile("Merge", duration_cast<microseconds>(stop - start));
            break;
        case 7:
            start = high_resolution_clock::now();
            quickSort(A, TAM);    
            stop = high_resolution_clock::now();
            timesFile("Quick", duration_cast<microseconds>(stop - start));
            break;
        default:
            start = high_resolution_clock::now();  
            timesFile("NULL", duration_cast<microseconds>(start - start));
            
    }
    // Separador de casos
    // start = high_resolution_clock::now();  
    // timesFile("END CASE \\\\\\\\\\", duration_cast<microseconds>(start - start));

    // Print sorted array
    //printArray(A, TAM);
    
 
    cout <<"\n";
    return 0;
}