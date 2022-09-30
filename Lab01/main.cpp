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

const int MAXNUM = 100; // INT_MAX;
const int TAM = 1000;
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
        // cout << num<< " ";
        // Guardar los números en el archivo
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
void insertionSort(int array[], int n)
{
    for (int step = 1; step < n; step++)
    {
        int key = array[step];
        int j = step - 1;

        while (key < array[j] && j >= 0)
        {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

/*************************
 *   4. Selection sort
 *************************/
void selectionSort(int array[], int n)
{
    for (int step = 0; step < n - 1; step++)
    {
        int min_idx = step;
        for (int i = step + 1; i < n; i++)
        {

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
void shellSort(int array[], int n)
{
    // Rearrange elements at each n/2, n/4, n/8, ... intervals
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
            // function to merge  two sub-arrays of
            // size sub_size starting from L and Mid
            merge(Arr, L, Mid, R);
        }
    }
}

/*************************
 *   7. Quick sort
 *************************/
int partition(int array[], int start, int end)
{
    // Pick the rightmost element as a pivot from the array
    int pivot = array[end];
 
    // elements less than the pivot goes to the left of `pIndex`
    // elements more than the pivot goes to the right of `pIndex`
    // equal elements can go either way
    int pIndex = start;
 
    // each time we find an element less than or equal to the pivot, `pIndex`
    // is incremented, and that element would be placed before the pivot.
    for (int i = start; i < end; i++)
    {
        if (array[i] <= pivot)
        {
            swap(array[i], array[pIndex]);
            pIndex++;
        }
    }
 
    // swap `pIndex` with pivot
    swap (&array[pIndex], &array[end]);
 
    // return `pIndex` (index of the pivot element)
    return pIndex;
}
 
// Iterative Quicksort routine
void quickSort(int array[], int n)
{
    // create a stack of `std::pairs` for storing subarray start and end index
    stack<pair<int, int>> s;
 
    // get the starting and ending index of the given array
    int start = 0;
    int end = n - 1;
 
    // push the start and end index of the array into the stack
    s.push(make_pair(start, end));
 
    // loop till stack is empty
    while (!s.empty())
    {
        // remove top pair from the list and get subarray starting
        // and ending indices
        start = s.top().first, end = s.top().second;
        s.pop();
 
        // rearrange elements across pivot
        int pivot = partition(array, start, end);
 
        // push subarray indices containing elements that are
        // less than the current pivot to stack
        if (pivot - 1 > start) {
            s.push(make_pair(start, pivot - 1));
        }
 
        // push subarray indices containing elements that are
        // more than the current pivot to stack
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
    // insertionSort(A, TAM);

    // 4. Selection sort
    // selectionSort(A, TAM);

    // 5. Shell sort
    // shellSort(A,TAM);

    // 6. Merge sort
    // mergeSort(A, TAM);

    // 7. Quick sort
    //quickSort(A, TAM);

    // Print sorted array
    printArray(A, TAM);
    cout << endl;

    // Time Execution
    auto start = high_resolution_clock::now();
 
    // Call the function, here sort()
    quickSort(A, TAM);
     
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
 
    timesFile("Quick" , duration);

     start = high_resolution_clock::now();
 
    // Call the function, here sort()
    mergeSort(A, TAM);
     
     stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
 
    timesFile("Merge" , duration);
    return 0;
}