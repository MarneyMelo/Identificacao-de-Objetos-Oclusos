/*Objeto A linha do tipo objeto se inicia com O e contem o identificador do objeto, a sua
posição inicial (que é o centro do objeto) e a largura do mesmo.
O seu formato é O <objeto> <x> <y> <largura>.


O TAD objeto armazena os objetos que podem aparecer numa cena. Além
da criação dos objetos, lembre-se que você tem que criar funções que atualizam a
posição dos objetos e também suportam a geração da cena.
*/

#include "../include/objeto.hpp"

// Construtor padrão
Objeto::Objeto() {
    this->id_obj = -1; // ID inválido para indicar que não foi inicializado
    this->x = 0;
    this->y = 0;
    this->largura = 0;
    this->posInit = 0;
    this->posFinal = 0;
}

// Construtor principal que calcula os limites
Objeto::Objeto(int id, double centro_x, double profundidade_y, double larg) {
    this->id_obj = id;
    this->x = centro_x;
    this->y = profundidade_y;
    this->largura = larg;
    this->posInit = centro_x - (larg / 2.0);
    this->posFinal = centro_x + (larg / 2.0);
}

// metodo para atualizar a posição após a movimentação
void Objeto::AtualizaPosicao(double novo_x, double novo_y) {
    this->x = novo_x;
    this->y = novo_y;
    this->posInit = novo_x - (this->largura / 2.0);
    this->posFinal = novo_x + (this->largura / 2.0);
}

//getters
int Objeto::GetId() const {
    return this->id_obj;
}

double Objeto::GetY() const {
    return this->y;
}

double Objeto::GetPosInit() const {
    return this->posInit;
}

double Objeto::GetPosFinal() const {
    return this->posFinal;
}