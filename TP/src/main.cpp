//main
#include <iostream>
#include <string>
#include <fstream> // arquivos

#include "../include/gerenciador_objetos.hpp"
#include "../include/cena.hpp"

void geraCena(GerenciadorDeObjetos& gerenciador, Cena& cena);

int main(int argc, char *argv[]) {

    std::ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
        return 1;
    }

    GerenciadorDeObjetos gerenciador;
    Cena cena;

    char comando;
    // loop de leitura
    while (inputFile >> comando) {
        if (comando == 'O') {
            int id;
            double x, y, largura;
            inputFile >> id >> x >> y >> largura;
            gerenciador.AdicionarObjeto(id, x, y, largura);

        } else if (comando == 'M') {
            int tempo, id;
            double x, y;
            inputFile >> tempo >> id >> x >> y;
            gerenciador.MoverObjeto(id, x, y);
            
        } else if (comando == 'C') {
            int tempo;
            inputFile >> tempo;
            
            cena.Limpar();
            geraCena(gerenciador, cena);
            cena.Imprimir(tempo);
        }
    }

    inputFile.close(); 
    return 0;
}

void geraCena(GerenciadorDeObjetos& gerenciador, Cena& cena) {
    // ordenção e oclusão
    //TODO -> adicionar um iterador ao metodo de ordenação que incrementa a cada troca para gerenciar o nivel de desordenação

}