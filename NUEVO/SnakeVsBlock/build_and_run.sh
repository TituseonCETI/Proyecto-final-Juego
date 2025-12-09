#!/bin/bash
# Compilación directa en una sola línea
# Para distribuir fácilmente

clear
echo "🔨 Compilando Snake vs Block..."
g++ -std=c++17 -O2 -o SnakeVsBlock_terminal main_terminal.cpp -lpthread && \
echo "✅ ¡Listo!" && \
echo "   Ejecuta: ./SnakeVsBlock_terminal" && \
./SnakeVsBlock_terminal
