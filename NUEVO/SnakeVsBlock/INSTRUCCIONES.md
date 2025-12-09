# 🎮 INSTRUCCIONES DE USO - Snake vs Block C++

## ✅ Estado del Proyecto

**El juego está 100% funcional en C++** con todas las características implementadas:

- ✅ 3 tipos de bloques (Normal, Penalización, Mortal)
- ✅ 5 tipos de power-ups únicos
- ✅ Mapa dinámico que se expande
- ✅ Dificultad progresiva
- ✅ Efectos visuales avanzados
- ✅ Sistema completo de puntuación

---

## 🚀 CÓMO EJECUTAR

### **Opción 1: Ejecutar directamente (Ya está compilado)**
```bash
cd /workspaces/Proyecto-final-Juego/NUEVO/SnakeVsBlock
./SnakeVsBlock
```

### **Opción 2: Usar el script de compilación**
```bash
cd /workspaces/Proyecto-final-Juego/NUEVO/SnakeVsBlock
./compile.sh
```

### **Opción 3: Usar Makefile**
```bash
cd /workspaces/Proyecto-final-Juego/NUEVO/SnakeVsBlock
make
make run
```

### **Opción 4: Compilación manual**
```bash
cd /workspaces/Proyecto-final-Juego/NUEVO/SnakeVsBlock
g++ -std=c++17 -Wall -O2 -o SnakeVsBlock main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./SnakeVsBlock
```

---

## 🎯 CÓMO JUGAR

### Controles
| Tecla | Acción |
|-------|--------|
| ↑ o W | Mover Arriba |
| ↓ o S | Mover Abajo |
| ← o A | Mover Izquierda |
| → o D | Mover Derecha |
| ESPACIO | Pausar/Reanudar |
| R | Reiniciar (tras Game Over) |
| ESC | Salir del juego |

### Tipos de Bloques
- 🔴 **Rojo (Normal)**: +10 puntos (o +20 con Double Points activo)
- ⚫ **Gris (Penalización)**: -20 puntos
- 🟣 **Púrpura (Mortal)**: ¡Game Over instantáneo! ☠️

### Power-ups
- 🚀 **W (Wall Pass)**: Atraviesa paredes por 5 segundos
- 💎 **2x (Double Points)**: Puntos dobles por 8 segundos
- 🧲 **M (Magneto)**: Los bloques se atraen hacia ti por 6 segundos
- 👻 **G (Ghost Mode)**: Atraviesa TODO por 4 segundos
- ✂️ **S (Shrink)**: Te vuelves más pequeño por 6 segundos

---

## 📦 CÓMO COMPARTIR CON OTROS

### **Opción 1: Compartir el ejecutable compilado**
El archivo `SnakeVsBlock` (sin extensión) es el ejecutable. Puedes compartirlo directamente:

```bash
# Copiar a una ubicación compartida
cp SnakeVsBlock ~/juegos/
```

**Requisitos para otros usuarios:**
- Sistema Linux con Raylib instalado
- O proporcionar Raylib estáticamente (ver Opción 2)

### **Opción 2: Crear ejecutable portable**
Para que otros NO necesiten instalar Raylib:

```bash
# Compilar estáticamente
g++ -std=c++17 -Wall -O2 -o SnakeVsBlock main.cpp \
    /usr/local/lib/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11

# El archivo SnakeVsBlock ahora incluye Raylib
```

### **Opción 3: Compartir código fuente en GitHub**
```bash
cd /workspaces/Proyecto-final-Juego
git add NUEVO/SnakeVsBlock/
git commit -m "Agregar Snake vs Block en C++"
git push origin main
```

Otros podrán clonar y compilar:
```bash
git clone https://github.com/TituseonCETI/Proyecto-final-Juego.git
cd Proyecto-final-Juego/NUEVO/SnakeVsBlock
./compile.sh
```

### **Opción 4: Crear paquete distribuible**
```bash
cd /workspaces/Proyecto-final-Juego/NUEVO/SnakeVsBlock

# Crear archivo tar.gz con todo lo necesario
tar -czf SnakeVsBlock-v1.0.tar.gz \
    SnakeVsBlock \
    main.cpp \
    Makefile \
    compile.sh \
    README.md \
    INSTRUCCIONES.md

# Compartir SnakeVsBlock-v1.0.tar.gz
```

Los usuarios pueden descomprimir y jugar:
```bash
tar -xzf SnakeVsBlock-v1.0.tar.gz
cd SnakeVsBlock
./SnakeVsBlock
```

### **Opción 5: Subir a itch.io (Recomendado para distribución pública)**

1. **Preparar el paquete:**
```bash
mkdir -p SnakeVsBlock-Linux
cp SnakeVsBlock SnakeVsBlock-Linux/
cp README.md SnakeVsBlock-Linux/
zip -r SnakeVsBlock-Linux.zip SnakeVsBlock-Linux/
```

2. **Subir a itch.io:**
   - Ve a https://itch.io
   - Crea cuenta y nuevo proyecto
   - Sube `SnakeVsBlock-Linux.zip`
   - Marca como "Linux executable"
   - ¡Comparte el enlace!

---

## 🔧 DEPENDENCIAS NECESARIAS

### Para compilar (desarrolladores):
```bash
sudo apt install -y build-essential \
    libasound2-dev libx11-dev libxrandr-dev \
    libxi-dev libgl1-mesa-dev libglu1-mesa-dev \
    libxcursor-dev libxinerama-dev
```

### Para ejecutar (usuarios finales):
```bash
# Si usas ejecutable dinámico (requiere Raylib instalado)
sudo apt install -y libraylib4

# Si usas ejecutable estático (no requiere nada extra)
# Solo ejecutar: ./SnakeVsBlock
```

---

## 📊 COMPARACIÓN DE MÉTODOS DE DISTRIBUCIÓN

| Método | Ventaja | Desventaja |
|--------|---------|------------|
| **Ejecutable directo** | Simple, rápido | Requiere Raylib instalado |
| **Ejecutable estático** | No requiere deps | Archivo más grande (~2MB) |
| **Código fuente** | Máxima flexibilidad | Usuario debe compilar |
| **Paquete TAR.GZ** | Todo incluido | Tamaño mediano |
| **itch.io** | Mejor distribución | Requiere cuenta |

---

## 🎯 ESTRATEGIAS DE JUEGO

1. **Prioriza Ghost Mode**: Es el power-up más poderoso
2. **Evita bloques púrpura**: Son mortales
3. **Usa Magneto con Double Points**: Combinación explosiva
4. **El mapa crece cada 10 bloques**: Más espacio, más desafío
5. **La velocidad aumenta**: Planifica con anticipación

---

## 🐛 SOLUCIÓN DE PROBLEMAS

### Error: "Display not found"
```bash
# En contenedores Docker/Dev Container, necesitas X11 forwarding
export DISPLAY=:0
```

### Error: "libraylib.so not found"
```bash
# Compilar estáticamente
g++ -std=c++17 -o SnakeVsBlock main.cpp /usr/local/lib/libraylib.a \
    -lGL -lm -lpthread -ldl -lrt -lX11
```

### El juego no se ve en el contenedor
Los contenedores sin GUI no pueden mostrar ventanas. Opciones:
1. Ejecutar en máquina host
2. Configurar X11 forwarding
3. Usar VNC/noVNC para GUI remota

---

## 📝 ARCHIVOS DEL PROYECTO

```
SnakeVsBlock/
├── main.cpp          # Código fuente completo en C++
├── SnakeVsBlock      # Ejecutable compilado
├── Makefile          # Para compilar con Make
├── compile.sh        # Script automático de compilación
├── CMakeLists.txt    # Para compilar con CMake
├── README.md         # Documentación principal
└── INSTRUCCIONES.md  # Este archivo
```

---

## 🏆 RÉCORD ACTUAL

¿Puedes superar los **1000 puntos**?

---

## 👨‍💻 INFORMACIÓN TÉCNICA

- **Lenguaje**: C++17
- **Biblioteca Gráfica**: Raylib 5.5+
- **Plataforma**: Linux (portable a Windows/Mac)
- **Tamaño ejecutable**: ~2MB (estático)
- **FPS**: 60 (configurable)
- **Resolución inicial**: 800x600 (crece dinámicamente)

---

## 📞 CONTACTO Y SOPORTE

Para preguntas o problemas:
- GitHub Issues: https://github.com/TituseonCETI/Proyecto-final-Juego
- Email: [tu_email@ejemplo.com]

---

## 🎉 ¡DISFRUTA EL JUEGO!

**Snake vs Block - C++ Edition**
*Un proyecto de juego completo e interactivo*

🐍 ¡Buena suerte superando bloques! 🎮
