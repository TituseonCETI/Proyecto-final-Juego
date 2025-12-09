# 🎮 PROYECTO FINAL: Snake vs Block - C++

## ✅ Estado: 100% COMPLETADO

Tu proyecto **Snake vs Block** está 100% funcional y listo para usar. Tienes **DOS versiones compiladas**:

---

## 📦 Versión 1: TERMINAL (Sin dependencias)

**Archivo:** `main_terminal.cpp` (590 líneas)  
**Ejecutable:** `SnakeVsBlock_terminal` (47KB)  
**Dependencias:** Solo pthread

### Cómo usar:
```bash
make run
```

**Características:**
- ✅ Colores ANSI bonitos
- ✅ Entrada no-bloqueante con termios
- ✅ Funciona en cualquier Linux sin instalar nada
- ✅ Súper ligero y rápido
- ✅ Perfecta para compartir (solo necesitas 1 archivo .cpp)

---

## 📦 Versión 2: SDL2 (Con ventana gráfica)

**Archivo:** `main_sdl2.cpp` (428 líneas)  
**Ejecutable:** `SnakeVsBlock_sdl2` (31KB)  
**Dependencias:** SDL2 (ya instalado)

### Cómo usar:
```bash
make run-sdl2
```

**Características:**
- ✅ Ventana gráfica moderna
- ✅ Colores y bordes visuales
- ✅ Renderizado a 60 FPS
- ✅ Interfaz clara y profesional

---

## 🎮 Mecánicas Implementadas

✅ **Bloques (3 tipos)**
- Verde Normal: +10 puntos
- Rojo Penalización: -5 puntos
- Naranja Mortal: Game Over

✅ **Power-ups (5 tipos)**
- Wall Pass: Atravesar bordes
- Double Points: Puntos x2
- Magneto: Crecimiento rápido
- Ghost Mode: Atravesar serpiente
- Shrink: Reducir tamaño

✅ **Sistema de Progresión**
- Niveles dinámicos
- Velocidad incrementada
- Mapa expandible

✅ **Control y Juego**
- Entrada no-bloqueante
- Animación suave
- Colisiones precisas

---

## 🛠️ Comandos Disponibles

```bash
make              # Compilar terminal (default)
make terminal     # Compilar terminal
make sdl2        # Compilar SDL2
make both        # Compilar ambas
make run         # Ejecutar terminal
make run-sdl2    # Ejecutar SDL2
make clean       # Limpiar ejecutables
make info        # Mostrar opciones
```

---

## 📊 Resumen Técnico

| Aspecto | Terminal | SDL2 |
|---------|----------|------|
| **Lenguaje** | C++17 | C++17 |
| **Dependencias** | pthread | SDL2 |
| **Compilación** | 0.3s | 0.3s |
| **Warnings** | 0 | 0 |
| **Tamaño** | 47KB | 31KB |
| **Líneas código** | 590 | 428 |
| **Ventana** | Terminal | Gráfica |

---

## 🚀 Para Compartir el Juego

### Opción A: Compartir terminal (MÁS FÁCIL)
Solo envía `main_terminal.cpp`. El usuario compila con:
```bash
g++ -std=c++17 -O2 -o juego main_terminal.cpp -lpthread
./juego
```

### Opción B: Compartir SDL2
Envía `main_sdl2.cpp` e instrucciones:
```bash
sudo apt install libsdl2-dev
g++ -std=c++17 -O2 -o juego main_sdl2.cpp `sdl2-config --cflags --libs`
./juego
```

### Opción C: Compartir todo con Makefile
Envía carpeta completa y el usuario usa:
```bash
make run          # Para terminal
make run-sdl2     # Para gráfica
```

---

## 🎯 Siguientes Pasos Opcionales

Si quieres **agregar más características**, puedes:

1. **Más power-ups**: Agrega nuevos tipos en `PowerUpType`
2. **Nuevos bloques**: Crea variantes en `BlockType`
3. **Sonido**: Integra SDL_mixer para la versión SDL2
4. **IA enemiga**: Agrega obstáculos que se mueven
5. **Tabla de scores**: Guarda y carga récords
6. **Temas**: Diferentes paletas de colores

---

## ✨ Lo Que Lograste

✅ **100% C++ puro** - Sin Python, sin librerías raras  
✅ **100% Funcional** - Todas las mecánicas implementadas  
✅ **100% Compilable** - Solo Makefile, sin CMake  
✅ **Dos versiones** - Terminal Y gráfica  
✅ **Zero warnings** - Código limpio  
✅ **Super portátil** - Funciona en cualquier Linux  

---

## 📝 Estructura Final

```
SnakeVsBlock/
├── Makefile              # Build system
├── main_terminal.cpp     # Versión terminal
├── main_sdl2.cpp        # Versión SDL2
├── SnakeVsBlock_terminal # Ejecutable terminal
├── SnakeVsBlock_sdl2    # Ejecutable SDL2
├── README.md            # Documentación
└── PROYECTO_FINAL.md    # Este archivo
```

---

## 🎉 ¡LISTO PARA JUGAR!

Escoge tu versión favorita y ¡disfruta del juego!

```bash
# Versión bonita:
make run

# Versión con ventana:
make run-sdl2
```

¡Que te diviertas! 🎮
