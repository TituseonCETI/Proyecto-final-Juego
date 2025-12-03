@echo off
REM Script de compilación automática para Snake vs Block con Raylib
setlocal enabledelayedexpansion

set CMAKE_EXE=%USERPROFILE%\Downloads\cmake\bin\cmake.exe
set RAYLIB_PATH=%USERPROFILE%\Downloads\raylib
set PROJECT_DIR=%~dp0
set BUILD_DIR=%PROJECT_DIR%build

echo.
echo ====================================
echo  Snake vs Block - Compilador
echo ====================================
echo.

if not exist "%CMAKE_EXE%" (
    echo ERROR: CMake no encontrado en %CMAKE_EXE%
    pause
    exit /b 1
)

if not exist "%RAYLIB_PATH%" (
    echo ERROR: Raylib no encontrado en %RAYLIB_PATH%
    pause
    exit /b 1
)

echo Preparando directorio de compilacion...
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd /d "%BUILD_DIR%"

echo Ejecutando CMake...
"%CMAKE_EXE%" .. -G "Unix Makefiles"

if errorlevel 1 (
    echo ERROR en CMake
    pause
    exit /b 1
)

echo.
echo Compilando proyecto...
"%CMAKE_EXE%" --build . --config Release

if errorlevel 1 (
    echo ERROR en compilacion
    pause
    exit /b 1
)

echo.
echo ====================================
echo Compilacion completada exitosamente!
echo ====================================
echo.
echo Ejecuta: %BUILD_DIR%\SnakeVsBlock.exe
echo.
pause
