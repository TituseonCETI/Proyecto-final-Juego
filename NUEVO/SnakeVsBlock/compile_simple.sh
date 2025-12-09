#!/bin/bash
# Script de compilación simple - Snake vs Block Terminal
# NO REQUIERE NINGUNA DEPENDENCIA EXTERNA

echo "╔═══════════════════════════════════════════════════════════╗"
echo "║          🐍 COMPILADOR SNAKE VS BLOCK C++ 🎮             ║"
echo "╚═══════════════════════════════════════════════════════════╝"
echo ""
echo "📦 Compilando versión TERMINAL (sin dependencias)..."
echo ""

# Compilar versión terminal
g++ -std=c++17 -Wall -O2 -o SnakeVsBlock_terminal main_terminal.cpp -lpthread

if [ $? -eq 0 ]; then
    echo "✅ ¡Compilación exitosa!"
    echo ""
    echo "📁 Ejecutable creado: SnakeVsBlock_terminal"
    echo "💾 Tamaño: $(du -h SnakeVsBlock_terminal | cut -f1)"
    echo ""
    echo "🎮 Para jugar, ejecuta:"
    echo "   ./SnakeVsBlock_terminal"
    echo ""
    
    read -p "¿Deseas jugar ahora? (s/n): " respuesta
    if [ "$respuesta" = "s" ] || [ "$respuesta" = "S" ]; then
        clear
        ./SnakeVsBlock_terminal
    fi
else
    echo "❌ Error en la compilación"
    exit 1
fi
