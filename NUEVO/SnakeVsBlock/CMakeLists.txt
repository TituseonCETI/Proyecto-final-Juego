cmake_minimum_required(VERSION 3.10)
project(SnakeVsBlock)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configurar rutas de Raylib
set(RAYLIB_PATH "$ENV{USERPROFILE}/Downloads/raylib")
set(raylib_INCLUDE_DIRS "${RAYLIB_PATH}/include")
set(raylib_LIBRARIES "${RAYLIB_PATH}/lib/raylib.lib")

include_directories(${raylib_INCLUDE_DIRS})

add_executable(SnakeVsBlock main.cpp)

target_link_libraries(SnakeVsBlock ${raylib_LIBRARIES} winmm opengl32)
