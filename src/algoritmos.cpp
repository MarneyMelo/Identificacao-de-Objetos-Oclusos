#include "../include/algoritmos.hpp"

// algoritmos tirados das fontes contidas na documentação (geeksforgeeks)
// ---------------------------
// ESTRATÉGIA 1: INSERTION SORT
// ----------------------------

// Function to sort an array of Objeto using insertion sort
void InsertionSort(Objeto* arr, int n) 
{
    int i, j;
    Objeto key;
    for (i = 1; i < n; i++) 
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        
        // ADAPTAÇÃO
        // A comparação é feita pela coordenada Y do Objeto
        while (j >= 0 && arr[j].GetY() > key.GetY()) 
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
//-------------------------
// ESTRATÉGIA 2: MERGE SORT
// -------------------------

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(Objeto* arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays (using new/delete instead of vector)
    Objeto* L = new Objeto[n1];
    Objeto* R = new Objeto[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp arrays back 
    // into arr[left..right]
    while (i < n1 && j < n2) {
        // --- ADAPTAÇÃO NECESSÁRIA #1 ---
        // A comparação é feita pela coordenada Y do Objeto
        if (L[i].GetY() <= R[j].GetY()) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], 
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], 
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // Free the memory
    delete[] L;
    delete[] R;
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(Objeto* arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Função a ser chamada
void MergeSort(Objeto* arr, int size) 
{
    // O tipo do array é Objeto* e o tamanho é 'size'.
    if (size > 1) {
        mergeSort(arr, 0, size - 1);
    }
}
// -----------------------------
// ESTRATÉGIA 3: QUICK SORT
// ------------------------------------

// A função para troca
void swap(Objeto& a, Objeto& b) 
{
    Objeto temp = a;
    a = b;
    b = temp;
}

int partition(Objeto* arr, int low, int high) 
{
    // choose the pivot
    Objeto pivot = arr[high];

    // index of smaller element and indicates 
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[low..high] and move all smaller
    // elements on left side. Elements from low to 
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {
        // ADAPTAÇÃO 1
        // A comparação é feita pela coordenada Y do Objeto
        if (arr[j].GetY() < pivot.GetY()) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    // move pivot after smaller elements and
    // return its position
    swap(arr[i + 1], arr[high]);  
    return i + 1;
}

// the QuickSort function implementation
void quickSort(Objeto* arr, int low, int high) 
{
    if (low < high) {
        
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Função a ser chamada
void QuickSort(Objeto* arr, int size) 
{
    if (size > 1) {
        quickSort(arr, 0, size - 1);
    }
}


//ordenar a saida
// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void mergeSegmentos(SegmentoVisivel* arr, int left, int mid, int right)
{
    // Create sizes of two subarrays to be merged
    int const n1 = mid - left + 1;
    int const n2 = right - mid;

    // Create temp arrays
    SegmentoVisivel* L = new SegmentoVisivel[n1];
    SegmentoVisivel* R = new SegmentoVisivel[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Initial indexes
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    // Merge the temp arrays back into arr[left..right]
    while (i < n1 && j < n2) {
        //ADAPTAÇÃO
        // A comparação é feita pelo ID do objeto do SegmentoVisivel.
        if (L[i].id_obj <= R[j].id_obj) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

// Main recursive function that sorts arr[left..right] using the merge() helper.
void mergeSortSegmentos(SegmentoVisivel* arr, int left, int right)
{
    if (left >= right)
        return; // Base case

    int mid = left + (right - left) / 2;
    mergeSortSegmentos(arr, left, mid);
    mergeSortSegmentos(arr, mid + 1, right);
    mergeSegmentos(arr, left, mid, right);
}

// Função a ser chamada
void MergeSortSegmentos(SegmentoVisivel* arr, int size) 
{
    if (size > 1) {
        mergeSortSegmentos(arr, 0, size - 1);
    }
}