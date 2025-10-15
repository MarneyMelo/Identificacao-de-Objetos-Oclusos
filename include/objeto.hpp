// objeto.hpp 
#ifndef OBJETO
#define OBJETO

class Objeto{
    private:
    int id_obj;
    double x, y, largura, posInit, posFinal;

    public:
    //default constructor
    Objeto();
    //main constructor
    Objeto(int id_obj, double centro_x, double profundidade_y, double larg);

    // Atualiza a posição e recalcula os limites
    void AtualizaPosicao(double novo_x, double novo_y);

    // -- getters -- 
    int GetId() const;
    double GetY() const;
    double GetPosInit() const;
    double GetPosFinal() const;
};
#endif