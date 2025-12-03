Snake vs Block - Juego en C++
================================

REQUISITOS:
-----------
1. CMake (https://cmake.org/download/)
2. Visual Studio 2019 o superior (con C++ tools)
3. SDL2 (https://www.libsdl.org/download-2.0.php)

INSTALACIÓN DE SDL2 EN WINDOWS:
--------------------------------

Opción 1: Usar vcpkg (RECOMENDADO)
```
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\vcpkg integrate install
.\vcpkg install sdl2:x64-windows
```

Opción 2: Descargar manualmente
- Descarga SDL2-devel-2.x.x-VC.zip desde https://www.libsdl.org/
- Extrae en C:\SDL2
- Agrega C:\SDL2\lib y C:\SDL2\include a las variables de entorno

COMPILACIÓN:
-----------
1. Abre PowerShell en la carpeta del proyecto
2. Ejecuta:
```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

3. Ejecuta el juego:
```
.\Release\SnakeVsBlock.exe
```

CONTROLES:
-----------
- FLECHAS o WASD: Mover la serpiente
- ESPACIO: Pausar/Reanudar
- R: Reiniciar cuando pierdes
- ESC: Salir

OBJETIVO DEL JUEGO:
-------------------
- Come los bloques rojos para crecer
- Cada bloque comido suma 10 puntos
- Evita chocar con las paredes y contigo mismo
- El juego se acelera conforme avanzas
