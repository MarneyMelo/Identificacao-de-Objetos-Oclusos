#ifndef GERENCIADOR_OBJETOS_HPP
#define GERENCIADOR_OBJETOS_HPP

#include "objeto.hpp"

const int MAX_OBJETOS = 5000;

class GerenciadorDeObjetos {
private:
    Objeto array_de_objetos[MAX_OBJETOS];
    int num_objetos_atual;
    int movimentos_desde_ordenacao;
    long long tempo_total_ordenacao_ns = 0; 

public:
    GerenciadorDeObjetos();

    // adiciona um novo objeto ao array, return false se o array tiver cheio
    bool AdicionarObjeto(int id, double x, double y, double largura);

    // Encontra um objeto pelo ID e atualiza sua pos
    bool MoverObjeto(int id, double novo_x, double novo_y, int LIMIAR);
    
    // Retorna um ponteiro para o início do array de objetos (necessário para a ordenação)
    Objeto* GetArray();

    // Retorna o número de objetos atualmente no array
    int GetNumObjetos() const;
};

#endif