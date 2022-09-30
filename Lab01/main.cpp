#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <climits>
#include <cmath>

using namespace std;



const int MAXNUM = 100; // INT_MAX;
const int TAM = 1000010;
string NUMFILE = "in.txt";

/*************************
 *  AUXILIARY FUNCTIONS
 *************************/
void swap(int *a, int *b) {
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
        // cout << num<< " ";
        // Guardar los números en el archivo
        numbersFile << num << "\n";
    }
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
    // loop to access each array element
    for (int step = 0; step < n; ++step)
    {

        // loop to compare array elements
        for (int i = 0; i < n - step; ++i)
        {

            // compare two adjacent elements
            // change > to < to sort in descending order
            if (array[i] > array[i + 1])
            {

                // swapping elements if elements
                // are not in the intended order
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
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && array[left] > array[largest])
        largest = left;

    if (right < n && array[right] > array[largest])
        largest = right;

    // Swap and continue heapifying if root is not largest
    if (largest != i)
    {
        swap(array[i], array[largest]);
        heapify(array, n, largest);
    }
}

// main function to do heap sort
void heapSort(int array[], int n)
{
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    // Heap sort
    for (int i = n - 1; i >= 0; i--)
    {
        swap(array[0], array[i]);

        // Heapify root element to get highest element at root again
        heapify(array, i, 0);
    }
}
/*************************
 * 3. Insertion sort
 *************************/
void insertionSort(int array[], int n) {
  for (int step = 1; step < n; step++) {
    int key = array[step];
    int j = step - 1;

    while (key < array[j] && j >= 0) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = key;
  }
}

/*************************
 *   4. Selection sort
 *************************/
void selectionSort(int array[], int n) {
  for (int step = 0; step < n - 1; step++) {
    int min_idx = step;
    for (int i = step + 1; i < n; i++) {

      // To sort in descending order, change > to < in this line.
      // Select the minimum element in each loop.
      if (array[i] < array[min_idx])
        min_idx = i;
    }

    // put min at the correct position
    swap(&array[min_idx], &array[step]);
  }
}

/*************************
 *   5. Shell sort
 *************************/
void shellSort(int array[], int n) {
  // Rearrange elements at each n/2, n/4, n/8, ... intervals
  for (int interval = n / 2; interval > 0; interval /= 2) {
    for (int i = interval; i < n; i += 1) {
      int temp = array[i];
      int j;
      for (j = i; j >= interval && array[j - interval] > temp; j -= interval) {
        array[j] = array[j - interval];
      }
      array[j] = temp;
    }
  }
}

/*************************
 *   6. Merge sort
 *************************/
void merge(int A[], int p, int q, int r)
{
    // nro de elementos en cada submatriz
    int n1 = q - p + 1; // + 1 para contener el elemento medio
    int n2 = r - q;

    // Crear las submatrices L[] y R[] con un espacio extra c/una
    int L[n1 + 1];
    int R[n2 + 1];

    // Llenado de submatriz L con la mitad izquierda de A[] incluyendo el medio
    for (int i = 0; i < n1; i++)
    {
        L[i] = A[p + i]; // L[0..n1-1] = A[p..n1-1]
    }
    // Llenado de submatriz R con la mitad derecha de A[],
    //  comenzando por el siguiente elemento despúes del medio (+1)
    for (int j = 0; j < n2; j++)
    {
        R[j] = A[q + j + 1]; // R[0..n2-1] = A[n2+1..r]
    }

    // Llenando el último elemento de c/submatriz con un inf (numero max grande)
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0;
    int j = 0;
    for (int k = p; k <= r; k++)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i = i + 1;
        }
        else
        {
            A[k] = R[j];
            j = j + 1;
        }
    }
}

void mergeSort(int A[], int p, int r)
{
    if (p < r)
    {
        int q = floor((p + r) / 2);
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

/*************************
 *   7. Quick sort
 *************************/
// function to rearrange array (find the partition point)
int partition(int array[], int low, int high) {
    
  // select the rightmost element as pivot
  int pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }
  
  // swap pivot with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
      
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on righ of pivot
    int pi = partition(array, low, high);

    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);

    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
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
    generadorNumRandom(TAM);

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
    // 1. Bubble sort
    // bubbleSort(A, TAM);

    // 2. Heap sort
    // heapSort(A, TAM);

    // 3. Insertion sort
    //insertionSort(A, TAM);

    // 4. Selection sort
    // selectionSort(A, TAM);

    // 5. Shell sort
    // shellSort(A,TAM);
    
    // 6. Merge sort
    // mergeSort(A, 0, TAM-1);
    
    // 7. Quick sort
    quickSort(A, 0, TAM-1);

    // Print sorted array
    printArray(A, TAM);


    cout << endl;
    return 0;
}