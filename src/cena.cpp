/*Cena: A linha do tipo cena se inicia com C e contem apenas uma marca de tempo.
O seu formato é C <tempo>

O TAD cena armazena os objetos ou partes deles que vão aparecer numa cena
gerada no momento indicado. Lembre-se que você tem que criar funções que colocam
objetos (ou parte deles) numa cena e gravar a cena (colocar num arquivo de saída).
*/

#include "../include/cena.hpp"
#include "../include/algoritmos.hpp"
#include <iostream>
#include <iomanip>

Cena::Cena() {
    this->num_segmentos_atual = 0;
}

void Cena::Limpar() {
    this->num_segmentos_atual = 0;
}

bool Cena::AdicionarSegmento(int id, double inicio, double fim) {
    if (num_segmentos_atual >= MAX_SEGMENTOS) {
        std::cerr << "Erro: Limite máximo de segmentos na cena atingido." << std::endl;
        return false;
    }

    array_de_segmentos[num_segmentos_atual].id_obj = id;
    array_de_segmentos[num_segmentos_atual].inicio = inicio;
    array_de_segmentos[num_segmentos_atual].fim = fim;
    num_segmentos_atual++;
    return true;
}

void Cena::Imprimir(int tempo) const {
    SegmentoVisivel* segmentos = const_cast<SegmentoVisivel*>(this->array_de_segmentos);
    int num_segmentos = this->num_segmentos_atual;
    // Ordena a saíde de acordo com os ids
    MergeSortSegmentos(segmentos, num_segmentos);

    for (int i = 0; i < num_segmentos; i++) {
        // formato: S <tempo> <objeto> <inicio> <fim>
        std::cout << "S " << tempo << " " 
                  << segmentos[i].id_obj << " "
                  << std::fixed << std::setprecision(2) 
                  << segmentos[i].inicio << " "
                  << segmentos[i].fim << std::endl;
    }
}