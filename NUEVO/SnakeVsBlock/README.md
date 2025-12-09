# 🐍 Snake vs Block - C++ Edition

Un juego clásico de serpiente con bloques, completamente implementado en **C++17** sin dependencias externas (versión terminal) o con SDL2 (versión gráfica).

## 📋 Características del Juego

### Mecánicas Base
- 🐍 **Serpiente creciente**: Come bloques para ganar puntos y crecer
- 🧱 **3 tipos de bloques**:
  - **Verde (Normal)**: +10 puntos
  - **Rojo (Penalización)**: -5 puntos
  - **Naranja (Mortal)**: Game Over
  
### 5 Power-ups Especiales
- ⭐ **Wall Pass**: Atraviesa bordes sin morir (12 segundos)
- 💰 **Double Points**: Puntos duplicados (12 segundos)
- 🧲 **Magneto**: La serpiente crece más rápido (12 segundos)
- 👻 **Ghost Mode**: Atraviesa tu propia serpiente (12 segundos)
- 📉 **Shrink**: Reduce tamaño de la serpiente

### Progresión
- 📈 **Niveles dinámicos**: Aumentan cada 10 bloques comidos
- ⚡ **Velocidad incrementada**: Más difícil con cada nivel
- 🗺️ **Mapa expandible**: Se agregan más bloques a medida que avanzas

## 🎮 Opciones de Compilación

### Opción 1: Versión TERMINAL (Recomendada)
**Características:**
- ✅ Sin dependencias externas (solo pthread)
- ✅ Ejecutable muy pequeño (~47KB)
- ✅ Funciona en cualquier Linux
- ✅ Fácil de compartir (solo 1 archivo .cpp)
- ✅ Interfaz con colores ANSI

**Compilación:**
```bash
make terminal
# o simplemente:
make
```

**Ejecución:**
```bash
./SnakeVsBlock_terminal
# o:
make run
```

**Controles:**
```
↑ ↓ ← →  : Mover serpiente
ESC      : Salir
```

---

### Opción 2: Versión SDL2 (Gráfica)
**Características:**
- 🎨 Ventana gráfica bonita con colores
- 📦 Requiere SDL2 instalado
- 💾 Ejecutable algo más grande (~31KB)
- 🖼️ Mejor experiencia visual

**Instalación de dependencias (primera vez):**
```bash
sudo apt install libsdl2-dev
# o usar:
make install-sdl2
```

**Compilación:**
```bash
make sdl2
```

**Ejecución:**
```bash
./SnakeVsBlock_sdl2
# o:
make run-sdl2
```

**Controles:**
```
↑ ↓ ← →  : Mover serpiente
ESC      : Salir
```

---

## 🚀 Compilación Rápida

```bash
# Compilar versión por defecto (terminal)
make

# Compilar solo terminal
make terminal

# Compilar solo SDL2
make sdl2

# Compilar ambas versiones
make both

# Ver todas las opciones
make info

# Ejecutar terminal
make run

# Ejecutar SDL2
make run-sdl2

# Limpiar ejecutables compilados
make clean
```

## 📊 Especificaciones Técnicas

| Aspecto | Terminal | SDL2 |
|---------|----------|------|
| Lenguaje | C++17 | C++17 |
| Dependencias | pthread | SDL2 |
| Tamaño ejecutable | 47KB | 31KB |
| Líneas de código | 590 | 428 |
| Compilación | ~0.3s | ~0.3s |
| Ventana gráfica | No | Sí |
| Portabilidad | Máxima | Alta |

## 🛠️ Estructura del Proyecto

```
SnakeVsBlock/
├── Makefile               # Sistema de compilación
├── main_terminal.cpp      # Versión terminal (590 líneas)
├── main_sdl2.cpp         # Versión SDL2 (428 líneas)
├── SnakeVsBlock_terminal # Ejecutable terminal (compilado)
├── SnakeVsBlock_sdl2     # Ejecutable SDL2 (compilado)
└── README.md             # Este archivo
```

## 🔧 Opciones del Makefile

```bash
make terminal        # Compilar versión terminal
make sdl2           # Compilar versión SDL2
make both           # Compilar ambas
make run            # Ejecutar versión terminal
make run-sdl2       # Ejecutar versión SDL2
make clean          # Limpiar ejecutables
make install-sdl2   # Instalar SDL2
make info           # Mostrar esta información
```

## 📝 Notas Importantes

### Para Compartir el Juego
- **Versión Terminal**: Solo necesitas compartir `main_terminal.cpp` y alguien puede compilarlo con `g++ -std=c++17 -O2 -o game main_terminal.cpp -lpthread`
- **Versión SDL2**: Asegúrate de que el usuario tenga SDL2 instalado (`sudo apt install libsdl2-dev`)

### Rendimiento
- Ambas versiones están optimizadas con `-O2`
- Compila sin warnings con `-Wall`
- La versión terminal usa entrada no-bloqueante con `termios`
- La versión SDL2 mantiene 60 FPS

### Compatibilidad
- ✅ Linux (Ubuntu, Debian, Fedora, etc.)
- ✅ Compilador GCC 9+
- ✅ C++17 o superior
- ⚠️ No probado en macOS/Windows (pero debería funcionar con ajustes mínimos)

## 🎯 Próximos Pasos

Si quieres agregar más características:
1. Ambas versiones comparten la misma lógica de juego
2. Puedes modificar `BlockType`, `PowerUpType` fácilmente
3. Aumentar `GRID_WIDTH` y `GRID_HEIGHT` hace el juego más grande
4. Ajustar `INITIAL_SPEED` para cambiar dificultad

## 📄 Licencia

Este proyecto es de código abierto y libre para usar y modificar.

---

**¿Necesitas ayuda?** Ejecuta `make info` para ver todas las opciones disponibles.
