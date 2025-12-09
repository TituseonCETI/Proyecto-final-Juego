# Makefile para Snake vs Block
# Soporta versión Terminal (sin dependencias) y versión SDL2 (con ventana gráfica)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
LDFLAGS_TERMINAL = -lpthread
LDFLAGS_SDL2 = `sdl2-config --cflags --libs`

# Targets
TARGET_TERMINAL = SnakeVsBlock_terminal
TARGET_SDL2 = SnakeVsBlock_sdl2
SRC_TERMINAL = main_terminal.cpp
SRC_SDL2 = main_sdl2.cpp

# Default: compilar versión terminal (sin dependencias)
all: terminal

# Versión Terminal (recomendada - sin dependencias externas)
terminal: $(SRC_TERMINAL)
	@echo "🔨 Compilando versión TERMINAL (sin dependencias)..."
	$(CXX) $(CXXFLAGS) -o $(TARGET_TERMINAL) $(SRC_TERMINAL) $(LDFLAGS_TERMINAL)
	@echo "✅ Compilación exitosa: $(TARGET_TERMINAL)"
	@echo "   Ejecuta: ./$(TARGET_TERMINAL)"

# Versión SDL2 (requiere SDL2 instalado)
sdl2: $(SRC_SDL2)
	@echo "🔨 Compilando versión SDL2 (con ventana gráfica)..."
	@command -v sdl2-config >/dev/null 2>&1 || { echo "❌ SDL2 no instalado. Instala con: sudo apt install libsdl2-dev"; exit 1; }
	$(CXX) $(CXXFLAGS) -o $(TARGET_SDL2) $(SRC_SDL2) $(LDFLAGS_SDL2)
	@echo "✅ Compilación exitosa: $(TARGET_SDL2)"
	@echo "   Ejecuta: ./$(TARGET_SDL2)"

# Compilar ambas versiones
both: terminal sdl2
	@echo "✅ Ambas versiones compiladas!"

# Ejecutar versión terminal
run: terminal
	@clear
	./$(TARGET_TERMINAL)

# Ejecutar versión SDL2
run-sdl2: sdl2
	./$(TARGET_SDL2)

# Limpiar archivos compilados
clean:
	@echo "🧹 Limpiando archivos compilados..."
	rm -f $(TARGET_TERMINAL) $(TARGET_SDL2)
	@echo "✅ Limpieza completa"

# Instalar dependencias para versión SDL2
install-sdl2:
	@echo "📦 Instalando SDL2..."
	sudo apt update
	sudo apt install -y libsdl2-dev

# Información sobre el proyecto
info:
	@echo "╔═══════════════════════════════════════════════════════════╗"
	@echo "║          🐍 SNAKE VS BLOCK - C++ EDITION 🎮              ║"
	@echo "╚═══════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "📋 OPCIONES DE COMPILACIÓN:"
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "  make              - Compilar versión TERMINAL (recomendada)"
	@echo "  make terminal     - Compilar versión TERMINAL"
	@echo "  make sdl2         - Compilar versión SDL2 (ventana gráfica)"
	@echo "  make both         - Compilar ambas versiones"
	@echo "  make run          - Compilar y ejecutar versión terminal"
	@echo "  make run-sdl2     - Compilar y ejecutar versión SDL2"
	@echo "  make clean        - Limpiar archivos compilados"
	@echo "  make install-sdl2 - Instalar SDL2 (solo para versión gráfica)"
	@echo ""
	@echo "✨ VERSIÓN TERMINAL:"
	@echo "   • Sin dependencias externas"
	@echo "   • Funciona en cualquier Linux"
	@echo "   • Fácil de compartir (solo 1 archivo .cpp)"
	@echo "   • Ejecutable pequeño (~47KB)"
	@echo ""
	@echo "✨ VERSIÓN SDL2:"
	@echo "   • Ventana gráfica bonita"
	@echo "   • Requiere: sudo apt install libsdl2-dev"
	@echo "   • Mejor experiencia visual"
	@echo "   • Ejecutable más grande (~200KB)"
	@echo ""
	@echo "🎮 Para jugar:"
	@echo "   make run          (terminal)"
	@echo "   make run-sdl2     (ventana gráfica)"
	@echo ""

.PHONY: all terminal sdl2 both run run-sdl2 clean install-sdl2 info
