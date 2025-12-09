#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// ==================== CONSTANTES ====================
const int BASE_GRID_WIDTH = 40;
const int BASE_GRID_HEIGHT = 20;
const int INITIAL_SPEED = 150; // milisegundos
const int MIN_SPEED = 50;

// ==================== ENUMERACIONES ====================
enum class BlockType {
    NORMAL,    // suma puntos
    PENALTY,   // quita puntos
    DEADLY     // mata
};

enum class PowerUpType {
    WALL_PASS,      // Atravesar paredes
    DOUBLE_POINTS,  // Doble puntos
    MAGNETO,        // Los bloques se atraen
    GHOST_MODE,     // Atravesar todo
    SHRINK          // Encogerse
};

// ==================== ESTRUCTURAS ====================
struct Segment {
    int x, y;
};

struct Block {
    int x, y;
    BlockType type;
};

struct PowerUp {
    int x, y;
    PowerUpType type;
};

// ==================== VARIABLES GLOBALES ====================
std::vector<Segment> snake;
std::vector<Block> blocks;
std::vector<PowerUp> powerUps;
int directionX = 1, directionY = 0;
int nextDirectionX = 1, nextDirectionY = 0;
int score = 0;
int blocksEaten = 0;
int gameSpeed = INITIAL_SPEED;
bool gameOver = false;
bool gamePaused = false;

int gridWidth = BASE_GRID_WIDTH;
int gridHeight = BASE_GRID_HEIGHT;

// Power-ups activos
bool wallPassActive = false;
int wallPassTimer = 0;
bool doublePointsActive = false;
int doublePointsTimer = 0;
bool magnetoActive = false;
int magnetoTimer = 0;
bool ghostModeActive = false;
int ghostModeTimer = 0;
bool shrinkActive = false;
int shrinkTimer = 0;

// Variables para input no bloqueante
struct termios orig_termios;

// ==================== FUNCIONES DE TERMINAL ====================
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void clearScreen() {
    std::cout << "\033[2J\033[H";
}

void hideCursor() {
    std::cout << "\033[?25l";
}

void showCursor() {
    std::cout << "\033[?25h";
}

// Colores ANSI
std::string color(int code) {
    return "\033[" + std::to_string(code) + "m";
}

const std::string RESET = "\033[0m";
const std::string RED = "\033[91m";
const std::string GREEN = "\033[92m";
const std::string YELLOW = "\033[93m";
const std::string BLUE = "\033[94m";
const std::string MAGENTA = "\033[95m";
const std::string CYAN = "\033[96m";
const std::string WHITE = "\033[97m";
const std::string GRAY = "\033[90m";
const std::string BG_BLACK = "\033[40m";
const std::string BRIGHT_GREEN = "\033[92;1m";
const std::string ORANGE = "\033[38;5;208m";
const std::string PURPLE = "\033[38;5;129m";
const std::string DARK_GRAY = "\033[38;5;240m";

// ==================== FUNCIONES DEL JUEGO ====================
void spawnBlock() {
    Block newBlock;
    newBlock.x = rand() % gridWidth;
    newBlock.y = rand() % gridHeight;
    
    newBlock.type = BlockType::NORMAL;
    if (blocksEaten >= 20 && (rand() % 100) < 20) {
        newBlock.type = BlockType::PENALTY;
    }
    if (blocksEaten >= 40 && (rand() % 100) < 10) {
        newBlock.type = BlockType::DEADLY;
    }
    
    blocks.push_back(newBlock);
}

void spawnPowerUp() {
    PowerUp newPowerUp;
    newPowerUp.x = rand() % gridWidth;
    newPowerUp.y = rand() % gridHeight;
    
    int typeRand = rand() % 5;
    switch (typeRand) {
        case 0: newPowerUp.type = PowerUpType::WALL_PASS; break;
        case 1: newPowerUp.type = PowerUpType::DOUBLE_POINTS; break;
        case 2: newPowerUp.type = PowerUpType::MAGNETO; break;
        case 3: newPowerUp.type = PowerUpType::GHOST_MODE; break;
        case 4: newPowerUp.type = PowerUpType::SHRINK; break;
    }
    
    powerUps.push_back(newPowerUp);
}

void expandMap() {
    gridWidth += 2;
    gridHeight += 2;
}

void activatePowerUp(PowerUpType type) {
    switch (type) {
        case PowerUpType::WALL_PASS:
            wallPassActive = true;
            wallPassTimer = 50;
            break;
        case PowerUpType::DOUBLE_POINTS:
            doublePointsActive = true;
            doublePointsTimer = 80;
            break;
        case PowerUpType::MAGNETO:
            magnetoActive = true;
            magnetoTimer = 60;
            break;
        case PowerUpType::GHOST_MODE:
            ghostModeActive = true;
            ghostModeTimer = 40;
            break;
        case PowerUpType::SHRINK:
            shrinkActive = true;
            shrinkTimer = 60;
            break;
    }
}

void moveBlocksToSnake() {
    if (blocks.empty()) return;
    
    int headX = snake[0].x;
    int headY = snake[0].y;
    
    for (auto& block : blocks) {
        if (block.x < headX) block.x++;
        else if (block.x > headX) block.x--;
        
        if (block.y < headY) block.y++;
        else if (block.y > headY) block.y--;
    }
}

void initGame() {
    snake.clear();
    blocks.clear();
    powerUps.clear();
    
    score = 0;
    blocksEaten = 0;
    gameSpeed = INITIAL_SPEED;
    gameOver = false;
    gamePaused = false;
    
    gridWidth = BASE_GRID_WIDTH;
    gridHeight = BASE_GRID_HEIGHT;
    
    wallPassActive = false;
    wallPassTimer = 0;
    doublePointsActive = false;
    doublePointsTimer = 0;
    magnetoActive = false;
    magnetoTimer = 0;
    ghostModeActive = false;
    ghostModeTimer = 0;
    shrinkActive = false;
    shrinkTimer = 0;
    
    snake.push_back({gridWidth / 2, gridHeight / 2});
    snake.push_back({gridWidth / 2 - 1, gridHeight / 2});
    snake.push_back({gridWidth / 2 - 2, gridHeight / 2});
    
    directionX = 1;
    directionY = 0;
    nextDirectionX = 1;
    nextDirectionY = 0;
    
    for (int i = 0; i < 10; i++) {
        spawnBlock();
    }
}

void updateTimers() {
    if (wallPassActive && --wallPassTimer <= 0) wallPassActive = false;
    if (doublePointsActive && --doublePointsTimer <= 0) doublePointsActive = false;
    if (magnetoActive && --magnetoTimer <= 0) magnetoActive = false;
    if (ghostModeActive && --ghostModeTimer <= 0) ghostModeActive = false;
    if (shrinkActive && --shrinkTimer <= 0) shrinkActive = false;
}

void updateGame() {
    if (gameOver || gamePaused) return;
    
    updateTimers();
    
    directionX = nextDirectionX;
    directionY = nextDirectionY;
    
    int newX = snake[0].x + directionX;
    int newY = snake[0].y + directionY;
    
    // Verificar colisión con paredes
    if (newX < 0 || newX >= gridWidth || newY < 0 || newY >= gridHeight) {
        if (ghostModeActive || wallPassActive) {
            newX = (newX + gridWidth) % gridWidth;
            newY = (newY + gridHeight) % gridHeight;
        } else {
            gameOver = true;
            return;
        }
    }
    
    // Verificar colisión con el cuerpo
    if (!ghostModeActive) {
        for (auto& segment : snake) {
            if (segment.x == newX && segment.y == newY) {
                gameOver = true;
                return;
            }
        }
    }
    
    snake.insert(snake.begin(), {newX, newY});
    
    // Verificar colisión con power-ups
    for (size_t i = 0; i < powerUps.size(); i++) {
        if (powerUps[i].x == newX && powerUps[i].y == newY) {
            activatePowerUp(powerUps[i].type);
            powerUps.erase(powerUps.begin() + i);
            break;
        }
    }
    
    // Magneto
    if (magnetoActive) {
        moveBlocksToSnake();
    }
    
    // Verificar colisión con bloques
    bool ateBlock = false;
    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i].x == newX && blocks[i].y == newY) {
            BlockType blockType = blocks[i].type;
            blocks.erase(blocks.begin() + i);
            
            if (blockType == BlockType::NORMAL) {
                int points = doublePointsActive ? 20 : 10;
                score += points;
                ateBlock = true;
                blocksEaten++;
            } else if (blockType == BlockType::PENALTY) {
                score -= 20;
                if (score < 0) score = 0;
            } else if (blockType == BlockType::DEADLY) {
                gameOver = true;
                return;
            }
            
            if (gameSpeed > MIN_SPEED) gameSpeed -= 2;
            
            spawnBlock();
            
            if (blocksEaten % 10 == 0) {
                spawnPowerUp();
                expandMap();
            }
            
            break;
        }
    }
    
    if (!ateBlock) {
        snake.pop_back();
    }
}

void render() {
    clearScreen();
    
    // Crear buffer de pantalla
    std::vector<std::vector<char>> screen(gridHeight, std::vector<char>(gridWidth, ' '));
    std::vector<std::vector<std::string>> colors(gridHeight, std::vector<std::string>(gridWidth, ""));
    
    // Dibujar bloques
    for (auto& block : blocks) {
        if (block.x >= 0 && block.x < gridWidth && block.y >= 0 && block.y < gridHeight) {
            switch (block.type) {
                case BlockType::NORMAL:
                    screen[block.y][block.x] = '#';
                    colors[block.y][block.x] = RED;
                    break;
                case BlockType::PENALTY:
                    screen[block.y][block.x] = '%';
                    colors[block.y][block.x] = DARK_GRAY;
                    break;
                case BlockType::DEADLY:
                    screen[block.y][block.x] = 'X';
                    colors[block.y][block.x] = PURPLE;
                    break;
            }
        }
    }
    
    // Dibujar power-ups
    for (auto& powerUp : powerUps) {
        if (powerUp.x >= 0 && powerUp.x < gridWidth && powerUp.y >= 0 && powerUp.y < gridHeight) {
            char symbol = '?';
            std::string col = CYAN;
            
            switch (powerUp.type) {
                case PowerUpType::WALL_PASS:
                    symbol = 'W';
                    col = CYAN;
                    break;
                case PowerUpType::DOUBLE_POINTS:
                    symbol = '2';
                    col = MAGENTA;
                    break;
                case PowerUpType::MAGNETO:
                    symbol = 'M';
                    col = ORANGE;
                    break;
                case PowerUpType::GHOST_MODE:
                    symbol = 'G';
                    col = WHITE;
                    break;
                case PowerUpType::SHRINK:
                    symbol = 'S';
                    col = "\033[38;5;219m"; // Rosa
                    break;
            }
            
            screen[powerUp.y][powerUp.x] = symbol;
            colors[powerUp.y][powerUp.x] = col;
        }
    }
    
    // Dibujar serpiente
    for (size_t i = 0; i < snake.size(); i++) {
        if (snake[i].x >= 0 && snake[i].x < gridWidth && 
            snake[i].y >= 0 && snake[i].y < gridHeight) {
            if (i == 0) {
                screen[snake[i].y][snake[i].x] = ghostModeActive ? '@' : 'O';
                colors[snake[i].y][snake[i].x] = BRIGHT_GREEN;
            } else {
                screen[snake[i].y][snake[i].x] = shrinkActive ? '.' : 'o';
                colors[snake[i].y][snake[i].x] = GREEN;
            }
        }
    }
    
    // Título
    std::cout << YELLOW << "╔═══════════════════════════════════════════════════════════╗\n";
    std::cout << "║          🐍 SNAKE VS BLOCK - C++ EDITION 🎮              ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════════╝" << RESET << "\n\n";
    
    // Información
    std::cout << WHITE << "Score: " << YELLOW << score << RESET 
              << "  |  Bloques: " << blocksEaten 
              << "  |  Mapa: " << gridWidth << "x" << gridHeight << "\n";
    
    // Power-ups activos
    if (wallPassActive) {
        std::cout << CYAN << "⚡ Wall Pass (" << wallPassTimer << ") " << RESET;
    }
    if (doublePointsActive) {
        std::cout << MAGENTA << "💎 2x Points (" << doublePointsTimer << ") " << RESET;
    }
    if (magnetoActive) {
        std::cout << ORANGE << "🧲 Magneto (" << magnetoTimer << ") " << RESET;
    }
    if (ghostModeActive) {
        std::cout << WHITE << "👻 Ghost (" << ghostModeTimer << ") " << RESET;
    }
    if (shrinkActive) {
        std::cout << "\033[38;5;219m✂️ Shrink (" << shrinkTimer << ") " << RESET;
    }
    
    std::cout << "\n\n";
    
    // Bordes superior
    std::cout << GRAY << "┌";
    for (int i = 0; i < gridWidth; i++) std::cout << "─";
    std::cout << "┐\n" << RESET;
    
    // Dibujar pantalla
    for (int y = 0; y < gridHeight; y++) {
        std::cout << GRAY << "│" << RESET;
        for (int x = 0; x < gridWidth; x++) {
            std::cout << colors[y][x] << screen[y][x] << RESET;
        }
        std::cout << GRAY << "│\n" << RESET;
    }
    
    // Bordes inferior
    std::cout << GRAY << "└";
    for (int i = 0; i < gridWidth; i++) std::cout << "─";
    std::cout << "┘\n" << RESET;
    
    // Leyenda
    std::cout << "\n" << GRAY << "Leyenda: " << RESET;
    std::cout << BRIGHT_GREEN << "O" << RESET << "=Cabeza " 
              << GREEN << "o" << RESET << "=Cuerpo " 
              << RED << "#" << RESET << "=Bloque(+10) "
              << DARK_GRAY << "%" << RESET << "=Penalización(-20) "
              << PURPLE << "X" << RESET << "=Mortal\n";
    
    // Controles
    std::cout << GRAY << "Controles: " << RESET 
              << "WASD/Flechas=Mover | P=Pausa | R=Reiniciar | Q=Salir\n";
    
    if (gameOver) {
        std::cout << "\n" << RED << "╔═══════════════════════════════════════╗\n";
        std::cout << "║          ☠️  GAME OVER! ☠️             ║\n";
        std::cout << "║     Score Final: " << score << "               ║\n";
        std::cout << "║     Presiona R para reiniciar         ║\n";
        std::cout << "╚═══════════════════════════════════════╝" << RESET << "\n";
    }
    
    if (gamePaused && !gameOver) {
        std::cout << "\n" << YELLOW << "⏸️  PAUSADO - Presiona P para continuar" << RESET << "\n";
    }
    
    std::cout << std::flush;
}

char getInput() {
    char c = 0;
    ssize_t result = read(STDIN_FILENO, &c, 1);
    (void)result; // Suprimir warning de unused
    return c;
}

void handleInput(char c) {
    if (gameOver) {
        if (c == 'r' || c == 'R') {
            initGame();
        }
        return;
    }
    
    switch (c) {
        case 'w': case 'W':
            if (directionY == 0) {
                nextDirectionX = 0;
                nextDirectionY = -1;
            }
            break;
        case 's': case 'S':
            if (directionY == 0) {
                nextDirectionX = 0;
                nextDirectionY = 1;
            }
            break;
        case 'a': case 'A':
            if (directionX == 0) {
                nextDirectionX = -1;
                nextDirectionY = 0;
            }
            break;
        case 'd': case 'D':
            if (directionX == 0) {
                nextDirectionX = 1;
                nextDirectionY = 0;
            }
            break;
        case 'p': case 'P':
            gamePaused = !gamePaused;
            break;
        case 'r': case 'R':
            initGame();
            break;
        case 'q': case 'Q':
        case 27: // ESC
            gameOver = true;
            showCursor();
            disableRawMode();
            clearScreen();
            std::cout << YELLOW << "¡Gracias por jugar Snake vs Block!\n" << RESET;
            std::cout << "Score final: " << score << "\n";
            exit(0);
            break;
    }
}

// ==================== FUNCIÓN PRINCIPAL ====================
int main() {
    srand(time(0));
    
    enableRawMode();
    hideCursor();
    clearScreen();
    
    initGame();
    
    std::cout << YELLOW << "╔═══════════════════════════════════════════════════════════╗\n";
    std::cout << "║          🐍 SNAKE VS BLOCK - C++ EDITION 🎮              ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════════╝" << RESET << "\n\n";
    std::cout << "Iniciando juego en 3 segundos...\n";
    std::cout << "Usa WASD para moverte, P para pausa, Q para salir\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    auto lastUpdate = std::chrono::steady_clock::now();
    
    while (true) {
        char c = getInput();
        if (c != 0) {
            handleInput(c);
        }
        
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count();
        
        if (elapsed >= gameSpeed) {
            updateGame();
            render();
            lastUpdate = now;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    showCursor();
    disableRawMode();
    
    return 0;
}
