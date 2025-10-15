//main
#include <iostream>
#include <string>
#include <fstream>  arquivo

#include "../include/gerenciador_objetos.hpp"
#include "../include/cena.hpp"
#include "../include/algoritmos.hpp"

void geraCena(GerenciadorDeObjetos& gerenciador, Cena& cena); //prototipo


// leitura de dados via fstream
int main(int argc, char *argv[]) {

    std::ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
        return 1;
    }

    GerenciadorDeObjetos gerenciador;
    Cena cena;

    char comando;
    // loop com fstream
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
    /*
    int main() {
    GerenciadorDeObjetos gerenciador;
    Cena cena;

    char comando;
    // loop com cin
    while (std::cin >> comando) {
        if (comando == 'O') {
            int id;
            double x, y, largura;
            std::cin >> id >> x >> y >> largura;
            gerenciador.AdicionarObjeto(id, x, y, largura);

        } else if (comando == 'M') {
            int tempo, id;
            double x, y;
            std::cin >> tempo >> id >> x >> y;
            gerenciador.MoverObjeto(id, x, y);
            /*
            DESCOMENTAR AQ PARA ESTRATEGIA 1 (ORDENAR A CADA MOVIMENTAÇÃO)
            if (gerenciador.MoverObjeto(id, x, y)) {
                InsertionSort(gerenciador.GetArray(), gerenciador.GetNumObjetos());
            }
        } else if (comando == 'C') {
            int tempo;
            std::cin >> tempo;                
            cena.Limpar();
            geraCena(gerenciador, cena);
            cena.Imprimir(tempo);
        }
    }

    return 0;
}
*/



void geraCena(GerenciadorDeObjetos& gerenciador, Cena& cena) {
    Objeto* objetos = gerenciador.GetArray();
    int num_objetos = gerenciador.GetNumObjetos();

    if (num_objetos == 0) {
        return; // Nada a fazer
    }

    // ========= Fase 1. Ordenação =========
    
    // ordena em Y {quicksort e mergesort para estratégia 2 - ordernar ao fim}
    // descomentar apenas o algoritmo de ordeneção a ser utilizado para ser implementado
    //QuickSort(objetos, num_objetos); 
    MergeSort(objetos, num_objetos);



    // ========= Fase 2: calcula a oclusão =========
    
    // struct simples pra representar intervalo [ini fim]
    struct Intervalo {
        double inicio;
        double fim;
    };
    
    const int MAX_INTERVALOS = 1000; 
    
    // "horizonte" é um array que guarda os intervalos já cobertos por objetos mais proxims (menor y) (scanline)
    Intervalo horizonte[MAX_INTERVALOS];
    int num_intervalos_horizonte = 0;

    // --- Loop Principal: Percorre cada objeto do mais próximo ao mais distante ---
    for (int i = 0; i < num_objetos; i++) {
        Objeto& obj_atual = objetos[i];
        double obj_inicio = obj_atual.GetPosInit();
        double obj_fim = obj_atual.GetPosFinal();

        // ======= Bloco A: Descobrir quais partes do objeto atual sao visíveis =====
        
        // cursor marca o início do proximo segmento que pode estar visivel
        double cursor = obj_inicio;

        // Percorre os intervalos ja cobertos no horizonte para ver o que eles escondem
        for (int j = 0; j < num_intervalos_horizonte; j++) {
            Intervalo& h_intervalo = horizonte[j];

            // se o cursosr tiver passado do fim do nosso objeto, n tem mais nada para mostrar (so passa aqui depois de uma iteração)
            if (cursor >= obj_fim) {
                break;
            }

            // se o intervalo do horizonte esta totalmente antes do nosso cursor, nada muda (?!) remover??
            /*if (h_intervalo.fim <= cursor) {
                continue;
            }*/

            // se existe um espaço visível entre o cursor e o inicio do próximo bloqueio
            if (cursor < h_intervalo.inicio) {
                // O fim desse espaço visível é ou o fim do nosso objeto ou o começo do bloqueio
                double fim_visivel = (obj_fim < h_intervalo.inicio) ? obj_fim : h_intervalo.inicio; //std::min(obj_fim, h_intervalo.inicio)
                cena.AdicionarSegmento(obj_atual.GetId(), cursor, fim_visivel);
            }

            // O cursor avança para depois do bloqueio, pois a parte coberta não é visível.
            cursor = (cursor > h_intervalo.fim) ? cursor : h_intervalo.fim; //std::max(obj_fim, h_intervalo.inicio)
        }

        // se depois de passar por todos os bloqueios o cursor ainda não chegou ao fim do objeto,
        // entao o resto do objeto está visível
        if (cursor < obj_fim) {
            cena.AdicionarSegmento(obj_atual.GetId(), cursor, obj_fim);
        }

        // --- Parte B: Adicionar o objeto atual inteiro ao horizonte para bloquear os proximos ---
        
        Intervalo novo_intervalo = {obj_inicio, obj_fim};
        
        // Lógica de mesclagem para manter o horizonte como uma lista de intervalos disjuntos e ordenados.
        Intervalo temp_horizonte[MAX_INTERVALOS];
        int temp_count = 0;
        int k = 0;

        // 1. Copia intervalos que terminam antes do novo começar
        while (k < num_intervalos_horizonte && horizonte[k].fim < novo_intervalo.inicio) {
            temp_horizonte[temp_count++] = horizonte[k++];
        }

        // 2. Mescla o novo intervalo com todos os que se sobrepõem a ele
        // era possível apenas adicionar os intervalos disjuntos ao vetor, mas mesclar intervalos que se sobrepõe otimiza um pouco
        while (k < num_intervalos_horizonte && horizonte[k].inicio <= novo_intervalo.fim) {
            novo_intervalo.inicio = (novo_intervalo.inicio < horizonte[k].inicio) ? novo_intervalo.inicio : horizonte[k].inicio; //min(novo_intervalo.inicio,horizonte[k].inicio)
            novo_intervalo.fim = (novo_intervalo.fim > horizonte[k].fim) ? novo_intervalo.fim : horizonte[k].fim; //max(novo_intervalo.fim,horizonte[k].fim)
            k++;
        }
        temp_horizonte[temp_count++] = novo_intervalo;

        // 3. Copia o resto dos intervalos
        while (k < num_intervalos_horizonte) {
            temp_horizonte[temp_count++] = horizonte[k++];
        }

        // 4. Atualiza o horizonte principal
        num_intervalos_horizonte = temp_count;
        for (int m = 0; m < num_intervalos_horizonte; m++) {
            horizonte[m] = temp_horizonte[m];
        }
    }
}
