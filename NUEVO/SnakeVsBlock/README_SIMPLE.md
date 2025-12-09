# 🐍 Snake vs Block - C++ Edition

**Juego completo en C++ con CERO dependencias externas**

## ✨ Características

- ✅ **100% C++ puro** - No requiere bibliotecas externas
- ✅ **Multiplataforma** - Funciona en cualquier Linux/Unix
- ✅ **Compilación en 1 línea** - Súper fácil de compilar
- ✅ **Ejecutable pequeño** - Solo ~100KB
- ✅ **Fácil de compartir** - Solo 1 archivo .cpp
- ✅ **Funciona en terminal** - No necesita GUI

## 🚀 COMPILACIÓN ULTRA RÁPIDA

### Método 1: Una sola línea
```bash
g++ -std=c++17 -O2 -o SnakeVsBlock_terminal main_terminal.cpp -lpthread && ./SnakeVsBlock_terminal
```

### Método 2: Script automático
```bash
./build_and_run.sh
```

### Método 3: Con Make
```bash
make run
```

### Método 4: Compilar manualmente
```bash
g++ -std=c++17 -O2 -o SnakeVsBlock_terminal main_terminal.cpp -lpthread
./SnakeVsBlock_terminal
```

## 🎮 Cómo Jugar

### Controles
| Tecla | Acción |
|-------|--------|
| W/↑ | Mover Arriba |
| S/↓ | Mover Abajo |
| A/← | Mover Izquierda |
| D/→ | Mover Derecha |
| P | Pausar/Reanudar |
| R | Reiniciar |
| Q/ESC | Salir |

### Elementos del Juego
- **O** = Cabeza de la serpiente
- **o** = Cuerpo de la serpiente
- **#** = Bloque normal (rojo) - +10 puntos
- **%** = Bloque penalización (gris) - -20 puntos
- **X** = Bloque mortal (púrpura) - Game Over
- **W** = Power-up Wall Pass (atraviesa paredes)
- **2** = Power-up Double Points (doble puntos)
- **M** = Power-up Magneto (atrae bloques)
- **G** = Power-up Ghost Mode (atraviesa todo)
- **S** = Power-up Shrink (te hace más pequeño)

### Mecánicas
1. **Come bloques rojos (#)** para ganar puntos
2. **Evita bloques grises (%)** que quitan puntos
3. **¡HUYE de bloques púrpura (X)!** Son mortales
4. **Recoge power-ups** para habilidades especiales
5. **El mapa crece** cada 10 bloques comidos
6. **La velocidad aumenta** conforme avanzas

## 📦 COMPARTIR CON OTROS

### Opción 1: Solo el código fuente
```bash
# Solo necesitan este archivo
cp main_terminal.cpp /donde/quieras/

# Compilar (cualquier Linux con g++):
g++ -std=c++17 -O2 -o juego main_terminal.cpp -lpthread
```

### Opción 2: Paquete completo
```bash
# Crear paquete distribuible
tar -czf SnakeVsBlock.tar.gz main_terminal.cpp build_and_run.sh README_SIMPLE.md

# Otros usuarios:
tar -xzf SnakeVsBlock.tar.gz
cd SnakeVsBlock
./build_and_run.sh
```

### Opción 3: Compartir ejecutable
```bash
# Copiar ejecutable compilado
cp SnakeVsBlock_terminal /donde/quieras/

# Otros usuarios solo ejecutan:
./SnakeVsBlock_terminal
```

### Opción 4: GitHub
```bash
git add main_terminal.cpp
git commit -m "Snake vs Block - versión terminal C++"
git push
```

## 🎯 REQUISITOS

### Para compilar:
- ✅ **g++** con soporte C++17 (ya viene en la mayoría de Linux)
- ✅ **pthread** (ya viene en todos los Linux)
- ❌ NO requiere Raylib
- ❌ NO requiere SDL
- ❌ NO requiere ncurses
- ❌ NO requiere NADA más

### Para ejecutar:
- ✅ Terminal/consola Linux/Unix
- ✅ Soporte ANSI colors (99% de terminales modernas)
- ❌ NO requiere entorno gráfico
- ❌ NO requiere servidor X11

## 📊 VERSIONES DISPONIBLES

Este proyecto tiene **2 versiones**:

| Versión | Archivo | Dependencias | Tamaño | Uso |
|---------|---------|--------------|--------|-----|
| **Terminal** | `main_terminal.cpp` | Ninguna | ~100KB | Recomendada |
| **Gráfica** | `main.cpp` | Raylib | ~1MB | Opcional |

**Recomendación:** Usa la versión **Terminal** para máxima compatibilidad y facilidad de distribución.

## 🛠️ Comandos Útiles

```bash
# Ver ayuda del Makefile
make info

# Compilar versión terminal
make terminal
# o simplemente
make

# Compilar versión gráfica (requiere Raylib)
make graphics

# Compilar ambas
make both

# Ejecutar versión terminal
make run

# Limpiar archivos compilados
make clean
```

## 🐛 Solución de Problemas

### Error: "g++: command not found"
```bash
sudo apt install build-essential
```

### Error: "pthread not found"
```bash
# pthread viene con build-essential, instálalo:
sudo apt install build-essential
```

### El juego no se ve bien
Asegúrate de que tu terminal:
- Soporte colores ANSI (prácticamente todas)
- Tenga un tamaño mínimo de 80x30 caracteres
- Usa fuente monoespaciada

### El juego parpadea
Esto es normal en terminales lentas. El juego sigue siendo jugable.

## 📝 CARACTERÍSTICAS TÉCNICAS

- **Lenguaje:** C++17
- **Paradigma:** Procedural con estructuras
- **Entrada:** No bloqueante con termios
- **Salida:** ANSI escape codes
- **Multithreading:** std::thread para timing
- **Memoria:** Vectores STL para estructuras dinámicas
- **Portabilidad:** POSIX compliant
- **Tamaño fuente:** ~600 líneas
- **Tamaño ejecutable:** ~100KB

## 🎨 PERSONALIZACIÓN

Puedes modificar fácilmente:

```cpp
// En main_terminal.cpp

const int BASE_GRID_WIDTH = 40;    // Ancho del mapa
const int BASE_GRID_HEIGHT = 20;   // Alto del mapa
const int INITIAL_SPEED = 150;     // Velocidad inicial (ms)
const int MIN_SPEED = 50;          // Velocidad máxima

// Colores ANSI - cambia a tu gusto
const std::string RED = "\033[91m";
const std::string GREEN = "\033[92m";
// etc...
```

## 🏆 RÉCORDS

¿Puedes superar los **1000 puntos**?

## 🤝 CONTRIBUIR

Este es un proyecto educativo de código abierto. Siéntete libre de:
- Hacer fork
- Enviar pull requests
- Reportar bugs
- Sugerir mejoras
- Usar en tus proyectos

## 📜 LICENCIA

Código libre para uso educativo y personal.

## 👨‍💻 AUTOR

- **Proyecto:** Snake vs Block C++ Edition
- **Año:** 2025
- **Versión:** 1.0

## 🙏 AGRADECIMIENTOS

- Inspirado en el juego clásico Snake
- Mecánicas de "vs Block" añaden complejidad
- Power-ups para gameplay dinámico

---

## 📞 SOPORTE

Para dudas o problemas:
- Abre un issue en GitHub
- Lee este README completamente
- Verifica que g++ esté instalado

---

# 🎮 ¡A JUGAR!

```bash
make run
```

**¡Que consigas la puntuación más alta!** 🏆🐍
