# Sistema de Occlusion Culling em C++

## Sobre o Projeto

Este repositório contém a minha implementação para um trabalho prático da disciplina de Estruturas de Dados. O desafio era criar, do zero e em C++, um sistema de *Occlusion Culling* para um cenário unidimensional.

O objetivo é processar uma cena com vários objetos e determinar exatamente quais partes deles estão visíveis, considerando que objetos mais próximos podem esconder os que estão mais distantes. A principal restrição do projeto era não utilizar nenhuma estrutura de dados pronta da biblioteca padrão (STL), como `std::vector`, o que exigiu a implementação de todos os algoritmos e gerenciadores de coleções na mão.

## Análise Experimental

Uma parte significativa do escopo original do trabalho era a condução de uma análise experimental para comparar o desempenho de diferentes estratégias de ordenação (`Insertion Sort` vs. `Quick Sort` e `Merge Sort`). Embora essa análise tenha sido projetada, os scripts de automação e o código específico para a coleta de métricas não estão incluídos neste repositório, que foca na implementação limpa do algoritmo principal de oclusão.

## Tecnologias Utilizadas

* **C++ (padrão C++11)**
* **Makefile** para automação da compilação
* **G++**

## Estrutura do Projeto

```
.
├── bin/                      # Contém o executável final (tp1.out)
├── docs/                     # Contém a documentação formal do projeto
│   └── Documentacao-Occlusion-Culling.pdf
├── include/                  # Arquivos de cabeçalho (.hpp)
├── obj/                      # Arquivos de objeto intermediários (.o)
├── src/                      # Arquivos de implementação (.cpp)
├── testes/                   # Contém arquivos de entrada e saída para teste
│   ├── inputs1.txt
│   ├── inputs2.txt
│   ├── outputs1.txt
│   └── outputs2.txt
├── .gitignore                # Especifica arquivos a serem ignorados pelo Git
├── Makefile                  # Arquivo de compilação
└── README.md                 # Documentação principal (este arquivo)
```

## Como Compilar e Executar

### Pré-requisitos

* `g++` (compilador C++)
* `make`

### Compilação

Na pasta raiz do projeto, execute o comando:
```bash
make all
```
O executável `tp1.out` será criado na pasta `bin/`.

### Execução

O programa lê os dados via arquivos ou entrada padrão caso seja feita modificação. Para executar com um arquivo de teste, use:
```bash
./bin/tp1.out caminho/para/seu_arquivo_de_teste.txt (por exemplo testes/inputs1.txt que ja está na raiz do projeto)
```

## Autor

**Marney Santos de Melo**

## Licença

Este projeto está sob a licença MIT.