#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

// Constantes
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int GRID_SIZE = 20;
const int GRID_WIDTH = WINDOW_WIDTH / GRID_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / GRID_SIZE;

// Estructura para un segmento de la serpiente
struct Segment {
    int x, y;
};

// Estructura para un bloque
struct Block {
    int x, y;
    Color color;
};

// Variables globales
std::vector<Segment> snake;
std::vector<Block> blocks;
int directionX = 1, directionY = 0;
int nextDirectionX = 1, nextDirectionY = 0;
int score = 0;
int gameSpeed = 10;
int speedCounter = 0;
bool gameOver = false;
bool gamePaused = false;

// Inicializar el juego
void initGame() {
    snake.clear();
    blocks.clear();
    score = 0;
    gameSpeed = 10;
    gameOver = false;
    gamePaused = false;
    
    // Crear serpiente inicial (3 segmentos)
    snake.push_back({GRID_WIDTH / 2, GRID_HEIGHT / 2});
    snake.push_back({GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2});
    snake.push_back({GRID_WIDTH / 2 - 2, GRID_HEIGHT / 2});
    
    directionX = 1;
    directionY = 0;
    nextDirectionX = 1;
    nextDirectionY = 0;
    
    // Crear bloques iniciales
    for (int i = 0; i < 10; i++) {
        Block newBlock;
        newBlock.x = rand() % GRID_WIDTH;
        newBlock.y = rand() % GRID_HEIGHT;
        newBlock.color = RED;
        blocks.push_back(newBlock);
    }
}

// Generar un nuevo bloque
void spawnBlock() {
    Block newBlock;
    newBlock.x = rand() % GRID_WIDTH;
    newBlock.y = rand() % GRID_HEIGHT;
    newBlock.color = RED;
    blocks.push_back(newBlock);
}

// Actualizar lógica del juego
void updateGame() {
    if (gameOver || gamePaused) return;
    
    speedCounter++;
    if (speedCounter < gameSpeed) return;
    speedCounter = 0;
    
    // Aplicar dirección
    directionX = nextDirectionX;
    directionY = nextDirectionY;
    
    // Calcular nueva cabeza
    int newX = snake[0].x + directionX;
    int newY = snake[0].y + directionY;
    
    // Verificar colisión con paredes
    if (newX < 0 || newX >= GRID_WIDTH || newY < 0 || newY >= GRID_HEIGHT) {
        gameOver = true;
        return;
    }
    
    // Verificar colisión con el cuerpo
    for (auto& segment : snake) {
        if (segment.x == newX && segment.y == newY) {
            gameOver = true;
            return;
        }
    }
    
    // Agregar nueva cabeza
    snake.insert(snake.begin(), {newX, newY});
    
    // Verificar colisión con bloques
    bool ateBlock = false;
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i].x == newX && blocks[i].y == newY) {
            blocks.erase(blocks.begin() + i);
            score += 10;
            ateBlock = true;
            
            // Aumentar dificultad
            if (gameSpeed > 3) gameSpeed--;
            
            // Generar nuevo bloque
            spawnBlock();
            break;
        }
    }
    
    // Si no comió bloque, eliminar cola
    if (!ateBlock) {
        snake.pop_back();
    }
}

// Dibujar en pantalla
void render() {
    BeginDrawing();
    
    // Fondo negro
    ClearBackground(BLACK);
    
    // Dibujar bloques
    for (auto& block : blocks) {
        int x = block.x * GRID_SIZE;
        int y = block.y * GRID_SIZE;
        DrawRectangle(x + 2, y + 2, GRID_SIZE - 4, GRID_SIZE - 4, block.color);
        DrawRectangleLines(x, y, GRID_SIZE, GRID_SIZE, DARKRED);
    }
    
    // Dibujar serpiente
    for (int i = 0; i < snake.size(); i++) {
        int x = snake[i].x * GRID_SIZE;
        int y = snake[i].y * GRID_SIZE;
        
        if (i == 0) {
            // Cabeza en verde brillante
            DrawRectangle(x + 1, y + 1, GRID_SIZE - 2, GRID_SIZE - 2, LIME);
            DrawRectangleLines(x, y, GRID_SIZE, GRID_SIZE, GREEN);
        } else {
            // Cuerpo en verde oscuro
            DrawRectangle(x + 1, y + 1, GRID_SIZE - 2, GRID_SIZE - 2, GREEN);
        }
    }
    
    // Dibujar información
    DrawText("SNAKE VS BLOCK", 20, 10, 20, YELLOW);
    
    std::string scoreText = "Score: " + std::to_string(score);
    DrawText(scoreText.c_str(), 20, 40, 20, WHITE);
    
    if (gameOver) {
        DrawText("GAME OVER!", WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 50, 40, RED);
        std::string finalScoreText = "Final Score: " + std::to_string(score);
        DrawText(finalScoreText.c_str(), WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT / 2 + 20, 20, WHITE);
        DrawText("Press R to Restart", WINDOW_WIDTH / 2 - 140, WINDOW_HEIGHT / 2 + 80, 20, YELLOW);
    }
    
    if (gamePaused && !gameOver) {
        DrawText("PAUSED", WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 - 30, 40, YELLOW);
        DrawText("Press SPACE to Resume", WINDOW_WIDTH / 2 - 140, WINDOW_HEIGHT / 2 + 30, 20, WHITE);
    }
    
    // Controles
    DrawText("Controls: Arrow Keys / WASD | SPACE: Pause | R: Restart | ESC: Quit", 20, WINDOW_HEIGHT - 30, 14, GRAY);
    
    EndDrawing();
}

// Función principal
int main() {
    srand((unsigned)time(0));
    
    // Inicializar ventana
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Snake vs Block");
    SetTargetFPS(60);
    
    // Inicializar juego
    initGame();
    
    // Loop principal
    while (!WindowShouldClose()) {
        // Entrada
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            if (directionY == 0) {
                nextDirectionX = 0;
                nextDirectionY = -1;
            }
        }
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            if (directionY == 0) {
                nextDirectionX = 0;
                nextDirectionY = 1;
            }
        }
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            if (directionX == 0) {
                nextDirectionX = -1;
                nextDirectionY = 0;
            }
        }
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            if (directionX == 0) {
                nextDirectionX = 1;
                nextDirectionY = 0;
            }
        }
        if (IsKeyPressed(KEY_SPACE)) {
            gamePaused = !gamePaused;
        }
        if (IsKeyPressed(KEY_R) && gameOver) {
            initGame();
        }
        
        // Actualizar
        updateGame();
        
        // Dibujar
        render();
    }
    
    // Limpiar
    CloseWindow();
    
    return 0;
}
