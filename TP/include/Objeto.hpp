// objeto.hpp 
#ifndef OBJETO
#define OBJETO

class Objeto{
    private:
    int id_obj;
    float x, y, largura, posInit, posFinal;

    public:
    Objeto(int id_obj, float x, float y, float largura, float posInit);
};
#endif