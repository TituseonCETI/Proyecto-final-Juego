#!/bin/bash
# Script de información del proyecto Snake vs Block

clear
echo "╔═══════════════════════════════════════════════════════════╗"
echo "║                                                           ║"
echo "║          🐍 SNAKE VS BLOCK - C++ EDITION 🎮              ║"
echo "║                                                           ║"
echo "╚═══════════════════════════════════════════════════════════╝"
echo ""
echo "📋 INFORMACIÓN DEL PROYECTO"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "✅ Estado: 100% COMPLETADO EN C++"
echo "🔧 Lenguaje: C++17"
echo "📚 Versión: Terminal (sin dependencias)"
if [ -f "SnakeVsBlock_terminal" ]; then
    echo "💾 Tamaño ejecutable: $(du -h SnakeVsBlock_terminal | cut -f1)"
fi
echo "📁 Ubicación: $(pwd)"
echo ""

echo "📦 ARCHIVOS DISPONIBLES"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
ls -lh *.cpp *.sh Makefile SnakeVsBlock_terminal 2>/dev/null | grep -v total
echo ""

echo "🎮 CARACTERÍSTICAS IMPLEMENTADAS"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "  ✅ 3 tipos de bloques (Normal, Penalización, Mortal)"
echo "  ✅ 5 power-ups únicos (Wall Pass, Double Points, Magneto, Ghost, Shrink)"
echo "  ✅ Mapa dinámico que se expande cada 10 bloques"
echo "  ✅ Sistema de dificultad progresiva"
echo "  ✅ Efectos visuales avanzados (transparencias, shrink)"
echo "  ✅ Sistema completo de puntuación"
echo "  ✅ Controles con teclado (Flechas/WASD)"
echo "  ✅ Pausa y reinicio del juego"
echo ""

echo "🚀 OPCIONES DE EJECUCIÓN"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "  1) ./SnakeVsBlock_terminal     - Ejecutar versión terminal"
echo "  2) ./build_and_run.sh          - Compilar y ejecutar"
echo "  3) make run                    - Usar Makefile"
echo "  4) Leer README_SIMPLE.md       - Guía rápida"
echo "  5) Leer README.md              - Documentación completa"
echo ""

echo "🎯 CONTROLES DEL JUEGO"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "  ↑/W: Arriba    |  ↓/S: Abajo"
echo "  ←/A: Izquierda |  →/D: Derecha"
echo "  ESPACIO: Pausa |  R: Reiniciar  |  ESC: Salir"
echo ""

if [ -x "SnakeVsBlock_terminal" ]; then
    echo "✅ El juego está compilado y listo para jugar!"
    echo ""
    read -p "¿Deseas jugar ahora? (s/n): " respuesta
    if [ "$respuesta" = "s" ] || [ "$respuesta" = "S" ]; then
        echo ""
        echo "🚀 Iniciando Snake vs Block..."
        sleep 1
        ./SnakeVsBlock_terminal
    else
        echo ""
        echo "👋 ¡Hasta luego! Ejecuta './SnakeVsBlock_terminal' cuando quieras jugar."
    fi
else
    echo "⚠️  El juego no está compilado."
    echo ""
    read -p "¿Deseas compilarlo ahora? (s/n): " respuesta
    if [ "$respuesta" = "s" ] || [ "$respuesta" = "S" ]; then
        ./compile_simple.sh
    else
        echo ""
        echo "Para compilar manualmente ejecuta: make terminal"
    fi
fi

echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "  Proyecto: Juego Final - Snake vs Block"
echo "  Autor: TituseonCETI"
echo "  Fecha: Diciembre 2025"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo ""
