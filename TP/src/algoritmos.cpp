#include "../include/algoritmos.hpp"

// ---------------------------
// ESTRATÉGIA 1: INSERTION SORT
// ----------------------------

void InsertionSort(Objeto* arr, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        Objeto key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].GetY() > key.GetY()) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

//-------------------------
// ESTRATÉGIA 2: MERGE SORT
// -------------------------

void merge(Objeto* array, int const left, int const mid, int const right) {
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    Objeto* leftArray = new Objeto[subArrayOne];
    Objeto* rightArray = new Objeto[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne].GetY() <= rightArray[indexOfSubArrayTwo].GetY()) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        } else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSortRecursive(Objeto* array, int const begin, int const end) {
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;
    mergeSortRecursive(array, begin, mid);
    mergeSortRecursive(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void MergeSort(Objeto* arr, int tamanho) {
    mergeSortRecursive(arr, 0, tamanho - 1);
}


// -----------------------------
// ESTRATÉGIA 3: QUICK SORT
// ------------------------------------

void TrocarObjetos(Objeto& a, Objeto& b) {
    Objeto temp = a;
    a = b;
    b = temp;
}

int particao(Objeto* arr, int baixo, int alto) {
    Objeto pivo = arr[alto];
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (arr[j].GetY() <= pivo.GetY()) {
            i++;
            TrocarObjetos(arr[i], arr[j]); 
        }
    }
    TrocarObjetos(arr[i + 1], arr[alto]);
    return (i + 1);
}

// func recursiva principal do QuickSort
void quickSortRecursivo(Objeto* arr, int baixo, int alto) {
    if (baixo < alto) {
        int pi = particao(arr, baixo, alto);
        quickSortRecursivo(arr, baixo, pi - 1);
        quickSortRecursivo(arr, pi + 1, alto);
    }
}

// func de fachada para iniciar o QuickSort
void QuickSort(Objeto* arr, int tamanho) {
    quickSortRecursivo(arr, 0, tamanho - 1);
}

//ordenar a saida
void mergeSegmentos(SegmentoVisivel* array, int const left, int const mid, int const right) {
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    SegmentoVisivel* leftArray = new SegmentoVisivel[subArrayOne];
    SegmentoVisivel* rightArray = new SegmentoVisivel[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        // A ÚNICA MUDANÇA É AQUI: compara pelo id_obj
        if (leftArray[indexOfSubArrayOne].id_obj <= rightArray[indexOfSubArrayTwo].id_obj) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        } else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSortSegmentosRecursive(SegmentoVisivel* array, int const begin, int const end) {
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;
    mergeSortSegmentosRecursive(array, begin, mid);
    mergeSortSegmentosRecursive(array, mid + 1, end);
    mergeSegmentos(array, begin, mid, end);
}

void MergeSortSegmentos(SegmentoVisivel* arr, int tamanho) {
    mergeSortSegmentosRecursive(arr, 0, tamanho - 1);
}