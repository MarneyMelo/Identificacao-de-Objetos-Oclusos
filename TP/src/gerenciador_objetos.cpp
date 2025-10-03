#include "../include/gerenciador_objetos.hpp"
#include "../include/algoritmos.hpp"
#include <iostream>

GerenciadorDeObjetos::GerenciadorDeObjetos() {
    this->num_objetos_atual = 0;
}

bool GerenciadorDeObjetos::AdicionarObjeto(int id, double x, double y, double largura) {
    if (num_objetos_atual >=MAX_OBJETOS) {
        std::cerr << "Erro: Limite máximo de objetos atingido." << std::endl;
        return false;
    }
    
    // Cria o objeto na próxima posição livre do array
    array_de_objetos[num_objetos_atual] =Objeto(id, x, y, largura);
    num_objetos_atual++;
    return true;
}
bool GerenciadorDeObjetos::MoverObjeto(int id, double novo_x, double novo_y, int LIMIAR) {
    // procura o objeto pelo ID (linear)
    for (int i = 0; i < num_objetos_atual; i++) {
        if (array_de_objetos[i].GetId()== id) {
            array_de_objetos[i].AtualizaPosicao(novo_x, novo_y);
            this->movimentos_desde_ordenacao++;

            if (LIMIAR > 0 && this->movimentos_desde_ordenacao >= LIMIAR) {
                // Use o algoritmo que preferir para a reordenação (QuickSort é uma boa escolha)
                QuickSort(this->array_de_objetos, this->num_objetos_atual);
                //MergeSort(this->array_de_objetos, this->num_objetos_atual);
                this->movimentos_desde_ordenacao = 0; // Reseta o contador após ordenar
            }
            return true; // encontrou e moveu com sucesso
        }
    }
    return false; // obj n encontrado
}

Objeto* GerenciadorDeObjetos::GetArray() {
    return this->array_de_objetos;
}

int GerenciadorDeObjetos::GetNumObjetos() const {
    return this->num_objetos_atual;
}