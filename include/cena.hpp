// cena.hpp
/*Cena: A linha do tipo cena se inicia com C e contem apenas uma marca de tempo.
O seu formato é C <tempo>

O TAD cena armazena os objetos ou partes deles que vão aparecer numa cena
gerada no momento indicado. Lembre-se que você tem que criar funções que colocam
objetos (ou parte deles) numa cena e gravar a cena (colocar num arquivo de saída).
*/

#ifndef CENA_HPP
#define CENA_HPP


const int MAX_SEGMENTOS = 1000; // segmentos visiveis

//struct para representar uma parte visivel do obj
struct SegmentoVisivel {
    int id_obj;
    double inicio;
    double fim;
};

class Cena {
private:
    SegmentoVisivel array_de_segmentos[MAX_SEGMENTOS];
    int num_segmentos_atual;

public:
    Cena();

    // clean cena
    void Limpar();

    bool AdicionarSegmento(int id, double inicio, double fim);

    void Imprimir(int tempo) const;
};

#endif