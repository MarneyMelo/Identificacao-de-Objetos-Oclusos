#ifndef ALGORITMOS_HPP
#define ALGORITMOS_HPP

#include "objeto.hpp"
#include "cena.hpp"

// estrategia 1: ordenar a cada movimentação
void InsertionSort(Objeto* arr, int tamanho);

// estrategia 2: ordenar ao fim 1.0
void MergeSort(Objeto* arr, int tamanho);

// estrategia 3: ordenar ao fim 2.0
void QuickSort(Objeto* arr, int tamanho);

//ordenar a saida
void MergeSortSegmentos(SegmentoVisivel* arr, int tamanho);

#endif