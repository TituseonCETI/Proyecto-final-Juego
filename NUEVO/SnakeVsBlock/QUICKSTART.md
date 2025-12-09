# 🎮 GUÍA RÁPIDA - Snake vs Block C++

## ⚡ COMPILAR Y JUGAR (1 línea)

```bash
g++ -std=c++17 -O2 -o juego main_terminal.cpp -lpthread && ./juego
```

¡ESO ES TODO! 🎉

---

## 📋 OTRAS FORMAS

### Con script:
```bash
./build_and_run.sh
```

### Con Make:
```bash
make run
```

### Manual:
```bash
# Compilar
g++ -std=c++17 -O2 -o SnakeVsBlock_terminal main_terminal.cpp -lpthread

# Ejecutar
./SnakeVsBlock_terminal
```

---

## 🎮 CONTROLES

- **WASD** = Mover
- **P** = Pausa
- **R** = Reiniciar
- **Q** = Salir

---

## 🎯 OBJETIVO

1. Come bloques **rojos** (#) = +10 puntos
2. Evita bloques **grises** (%) = -20 puntos
3. ¡NO toques bloques **púrpura** (X)! = Game Over
4. Recoge power-ups (W, 2, M, G, S) = Habilidades especiales

---

## 📦 COMPARTIR

### Solo el código:
```bash
# Compartir solo main_terminal.cpp
# Otros compilan con:
g++ -std=c++17 -O2 -o juego main_terminal.cpp -lpthread
```

### Ejecutable:
```bash
# Compartir SnakeVsBlock_terminal
# Otros solo ejecutan:
./SnakeVsBlock_terminal
```

---

## ✅ REQUISITOS

- ✅ Linux/Unix con g++
- ✅ C++17 (ya viene en g++ moderno)
- ✅ pthread (ya viene con el sistema)
- ❌ NO requiere nada más

---

## 🐛 PROBLEMAS?

### No tengo g++:
```bash
sudo apt install build-essential
```

### No compila:
```bash
# Prueba sin optimización:
g++ -std=c++17 -o juego main_terminal.cpp -lpthread
```

---

## 📊 INFO

- **Tamaño ejecutable:** ~47KB
- **Líneas de código:** 590
- **Dependencias:** 0 (cero)
- **Plataformas:** Linux, macOS, WSL
- **Tiempo compilación:** <1 segundo

---

# 🚀 ¡A JUGAR!

```bash
make run
```

**¿Puedes superar 1000 puntos?** 🏆
