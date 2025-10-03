#!/bin/bash

# Arquivo para salvar os resultados deste experimento específico
RESULT_FILE="resultados_limiares.csv"
echo "Arquivo,Estrategia,Limiar,TempoTotal(s),TempoOrdenacao(ns)" > "$RESULT_FILE"

# --- CONFIGURAÇÃO ---
ARQUIVOS_DE_TESTE=(
    "testes/exp1_N1000_M50000_C500.txt"
    "testes/exp2_N1000_M5000_C500_freq_baixa.txt"
    "testes/exp3_N100_M5000_C100_freq_media.txt"
    "testes/exp3_N500_M5000_C100_freq_media.txt"
    "testes/exp3_N1000_M5000_C100_freq_media.txt"
    "testes/exp3_N5000_M5000_C100_freq_media.txt"
)

# --- LISTA DE LIMIARES INTERMEDIÁRIOS PARA TESTAR ---
LIMIARES=(10 50 100 250 500 1000) 

# --- EXECUÇÃO AUTOMATIZADA ---

echo "Iniciando teste de limiares intermediários com QuickSort..."

for arquivo in "${ARQUIVOS_DE_TESTE[@]}"; do
    for limiar in "${LIMIARES[@]}"; do
        
        if [ ! -f "$arquivo" ]; then
            echo "AVISO: Arquivo $arquivo não encontrado. Pulando."
            continue
        fi

        echo "Processando $arquivo com limiar $limiar..."
        
        OUTPUT_ERRO=$( { /usr/bin/time -f "%e" ./bin/tp1.out $limiar < "$arquivo" > /dev/null; } 2>&1 )
        
        TEMPO_TOTAL=$(echo "$OUTPUT_ERRO" | head -n 1)
        TEMPO_ORDENACAO=$(echo "$OUTPUT_ERRO" | grep "TEMPO_ORDENACAO_NS:" | cut -d':' -f2)
        
        TEMPO_TOTAL=${TEMPO_TOTAL:-"ERRO"}
        TEMPO_ORDENACAO=${TEMPO_ORDENACAO:-"ERRO"}
        
        # --- LINHA CORRIGIDA ---
        # O nome da estratégia agora inclui o algoritmo usado (QuickSort)
        ESTRATEGIA="MergeSort_Limiar_$limiar"
        
        echo "$arquivo,$ESTRATEGIA,$limiar,$TEMPO_TOTAL,$TEMPO_ORDENACAO" >> "$RESULT_FILE"
    done
done

echo "----------------------------------------------------"
echo "Teste de limiares finalizado!"
echo "Resultados salvos em $RESULT_FILE"
echo "----------------------------------------------------"