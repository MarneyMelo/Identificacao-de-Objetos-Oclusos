#!/bin/bash

# --- CONFIGURAÇÃO ---
# O nome do arquivo final que conterá todos os resultados
RESULT_FILE="resultados_finais.csv"

# A lista completa de todos os arquivos de teste que você gerou
ARQUIVOS_DE_TESTE=(
    "testes/exp1_N1000_M50000_C500.txt"
    "testes/exp2_N1000_M5000_C500_freq_baixa.txt"
    "testes/exp3_N100_M5000_C100_freq_media.txt"
    "testes/exp3_N500_M5000_C100_freq_media.txt"
    "testes/exp3_N1000_M5000_C100_freq_media.txt"
    "testes/exp3_N5000_M5000_C100_freq_media.txt"
)
# --- FIM DA CONFIGURAÇÃO ---


# Limpa o arquivo de resultados na primeira execução do dia, mas permite adicionar mais dados depois
if [ ! -f "$RESULT_FILE" ]; then
    echo "Arquivo,Estrategia,TempoTotal(s),TempoOrdenacao(ns)" > "$RESULT_FILE"
fi

# Pega o nome da estratégia (ex: "InsertionSort") que foi passada como argumento
ESTRATEGIA=$1
if [ -z "$ESTRATEGIA" ]; then
    echo "Erro: Você precisa especificar uma estratégia. Ex: ./executar_todos_testes.sh InsertionSort"
    exit 1
fi

# Define o limiar a ser usado com base na estratégia
LIMIAR_ARG=0
if [ "$ESTRATEGIA" == "InsertionSort" ]; then
    LIMIAR_ARG=1
fi

echo "============================================================"
echo "Executando testes para a Estratégia: $ESTRATEGIA"
echo "============================================================"

# Loop principal que executa o programa para cada arquivo de teste
for arquivo in "${ARQUIVOS_DE_TESTE[@]}"; do
    if [ ! -f "$arquivo" ]; then
        echo "AVISO: Arquivo $arquivo não encontrado. Pulando."
        continue
    fi

    echo "Processando $arquivo..."
    
    # Executa o programa e captura as saídas de tempo
    OUTPUT_ERRO=$( { /usr/bin/time -f "%e" ./bin/tp1.out $LIMIAR_ARG < "$arquivo" > /dev/null; } 2>&1 )
    
    TEMPO_TOTAL=$(echo "$OUTPUT_ERRO" | head -n 1)
    TEMPO_ORDENACAO=$(echo "$OUTPUT_ERRO" | grep "TEMPO_ORDENACAO_NS:" | cut -d':' -f2)
    
    TEMPO_TOTAL=${TEMPO_TOTAL:-"ERRO"}
    TEMPO_ORDENACAO=${TEMPO_ORDENACAO:-"ERRO"}
    
    # Salva os resultados no arquivo CSV final
    echo "$arquivo,$ESTRATEGIA,$TEMPO_TOTAL,$TEMPO_ORDENACAO" >> "$RESULT_FILE"
done

echo "----------------------------------------------------"
echo "Testes para a estratégia $ESTRATEGIA finalizados!"
echo "Resultados adicionados em $RESULT_FILE"
echo "----------------------------------------------------"