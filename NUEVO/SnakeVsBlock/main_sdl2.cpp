#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// ==================== CONSTANTES ====================
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int TILE_SIZE = 20;
const int GRID_WIDTH = WINDOW_WIDTH / TILE_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / TILE_SIZE;
const Uint32 FPS = 60;

// ==================== ESTRUCTURAS ====================
struct Color {
    Uint8 r, g, b, a;
};

struct Segment {
    int x, y;
};

enum class BlockType { NORMAL, PENALTY, DEADLY };

struct Block {
    int x, y;
    BlockType type;
};

enum class PowerUpType { WALL_PASS, DOUBLE_POINTS, MAGNETO, GHOST_MODE, SHRINK };

struct PowerUp {
    int x, y;
    PowerUpType type;
};

// ==================== COLORES ====================
const Color COLOR_BLACK = {0, 0, 0, 255};
const Color COLOR_WHITE = {255, 255, 255, 255};
const Color COLOR_GREEN = {50, 200, 50, 255};
const Color COLOR_RED = {200, 50, 50, 255};
const Color COLOR_BLUE = {50, 150, 255, 255};
const Color COLOR_YELLOW = {255, 255, 50, 255};
const Color COLOR_ORANGE = {255, 165, 0, 255};
const Color COLOR_PURPLE = {200, 100, 255, 255};
const Color COLOR_CYAN = {0, 255, 255, 255};
const Color COLOR_DARK_BLUE = {0, 100, 200, 255};

// ==================== CLASE DEL JUEGO ====================
class SnakeGame {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    
    std::vector<Segment> snake;
    std::vector<Block> blocks;
    std::vector<PowerUp> powerUps;
    
    int score;
    int level;
    int blocksEaten;
    int gameSpeed;
    int updateCounter;
    
    // Power-ups activos
    bool wallPass;
    bool doublePoints;
    bool magnetoMode;
    bool ghostMode;
    bool shrinkMode;
    
    int wallPassTimer;
    int doublePointsTimer;
    int magnetoTimer;
    int ghostModeTimer;
    int shrinkTimer;
    
    int direction;
    int nextDirection;
    
public:
    SnakeGame() : window(nullptr), renderer(nullptr), running(true),
                  score(0), level(1), blocksEaten(0), gameSpeed(5),
                  updateCounter(0),
                  wallPass(false), doublePoints(false), magnetoMode(false),
                  ghostMode(false), shrinkMode(false),
                  wallPassTimer(0), doublePointsTimer(0), magnetoTimer(0),
                  ghostModeTimer(0), shrinkTimer(0),
                  direction(2), nextDirection(2) {
        srand(time(nullptr));
    }
    
    ~SnakeGame() { cleanup(); }
    
    bool init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
            return false;
        }
        
        window = SDL_CreateWindow(
            "Snake vs Block - SDL2 Edition",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN
        );
        
        if (!window) {
            std::cerr << "Error SDL_CreateWindow: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }
        
        renderer = SDL_CreateRenderer(
            window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );
        
        if (!renderer) {
            std::cerr << "Error SDL_CreateRenderer: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }
        
        initGame();
        return true;
    }
    
    void initGame() {
        snake.clear();
        blocks.clear();
        powerUps.clear();
        
        // Serpiente inicial
        snake.push_back({GRID_WIDTH / 2, GRID_HEIGHT / 2});
        
        // Bloques iniciales
        for (int i = 0; i < 10; i++) {
            spawnBlock();
        }
    }
    
    void spawnBlock() {
        int x = rand() % GRID_WIDTH;
        int y = rand() % GRID_HEIGHT;
        
        int typeRoll = rand() % 100;
        BlockType type;
        if (typeRoll < 60) type = BlockType::NORMAL;
        else if (typeRoll < 90) type = BlockType::PENALTY;
        else type = BlockType::DEADLY;
        
        blocks.push_back({x, y, type});
    }
    
    void spawnPowerUp() {
        if (rand() % 100 < 25) {
            int x = rand() % GRID_WIDTH;
            int y = rand() % GRID_HEIGHT;
            PowerUpType type = (PowerUpType)(rand() % 5);
            powerUps.push_back({x, y, type});
        }
    }
    
    void handleInput() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            if (direction != 2) nextDirection = 0;
                            break;
                        case SDLK_DOWN:
                            if (direction != 0) nextDirection = 2;
                            break;
                        case SDLK_LEFT:
                            if (direction != 1) nextDirection = 3;
                            break;
                        case SDLK_RIGHT:
                            if (direction != 3) nextDirection = 1;
                            break;
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                    }
                    break;
            }
        }
    }
    
    void update() {
        updateCounter++;
        if (updateCounter < (12 - gameSpeed)) return;
        updateCounter = 0;
        
        direction = nextDirection;
        
        // Actualizar timers
        if (wallPassTimer > 0) wallPassTimer--;
        else wallPass = false;
        if (doublePointsTimer > 0) doublePointsTimer--;
        else doublePoints = false;
        if (magnetoTimer > 0) magnetoTimer--;
        else magnetoMode = false;
        if (ghostModeTimer > 0) ghostModeTimer--;
        else ghostMode = false;
        if (shrinkTimer > 0) shrinkTimer--;
        else shrinkMode = false;
        
        // Mover cabeza
        Segment head = snake[0];
        switch (direction) {
            case 0: head.y--; break;
            case 1: head.x++; break;
            case 2: head.y++; break;
            case 3: head.x--; break;
        }
        
        // Envolver en bordes
        head.x = (head.x + GRID_WIDTH) % GRID_WIDTH;
        head.y = (head.y + GRID_HEIGHT) % GRID_HEIGHT;
        
        // Colisión consigo misma
        if (!ghostMode) {
            for (const auto& seg : snake) {
                if (head.x == seg.x && head.y == seg.y) {
                    running = false;
                    return;
                }
            }
        }
        
        snake.insert(snake.begin(), head);
        
        // Colisión con bloques
        for (auto& block : blocks) {
            if (head.x == block.x && head.y == block.y) {
                int points = 10;
                if (block.type == BlockType::PENALTY) points = -5;
                else if (block.type == BlockType::DEADLY) {
                    running = false;
                    return;
                }
                
                if (doublePoints) points *= 2;
                score += points;
                blocksEaten++;
                
                if (blocksEaten % 10 == 0) {
                    level++;
                    if (gameSpeed < 10) gameSpeed++;
                    for (int i = 0; i < 5; i++) spawnBlock();
                }
                
                block.x = -1; // Marcar como comido
                spawnPowerUp();
                spawnBlock();
            }
        }
        
        // Colisión con power-ups
        for (auto& pu : powerUps) {
            if (head.x == pu.x && head.y == pu.y) {
                switch (pu.type) {
                    case PowerUpType::WALL_PASS:
                        wallPass = true;
                        wallPassTimer = 300;
                        break;
                    case PowerUpType::DOUBLE_POINTS:
                        doublePoints = true;
                        doublePointsTimer = 300;
                        break;
                    case PowerUpType::MAGNETO:
                        magnetoMode = true;
                        magnetoTimer = 300;
                        break;
                    case PowerUpType::GHOST_MODE:
                        ghostMode = true;
                        ghostModeTimer = 300;
                        break;
                    case PowerUpType::SHRINK:
                        if (snake.size() > 1) snake.pop_back();
                        break;
                }
                pu.x = -1; // Marcar como tomado
            }
        }
        
        // Remover cola si no está en modo magneto
        if (snake.size() > 1 && !magnetoMode) {
            snake.pop_back();
        }
        
        // Limpiar bloques comidos
        blocks.erase(
            std::remove_if(blocks.begin(), blocks.end(),
                          [](const Block& b) { return b.x == -1; }),
            blocks.end()
        );
        
        // Limpiar power-ups tomados
        powerUps.erase(
            std::remove_if(powerUps.begin(), powerUps.end(),
                          [](const PowerUp& p) { return p.x == -1; }),
            powerUps.end()
        );
    }
    
    void drawRect(int x, int y, int w, int h, const Color& color) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_Rect rect = {x, y, w, h};
        SDL_RenderFillRect(renderer, &rect);
    }
    
    void drawBorder(int x, int y, int w, int h) {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_Rect rect = {x, y, w, h};
        SDL_RenderDrawRect(renderer, &rect);
    }
    
    void render() {
        // Fondo
        drawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_BLACK);
        
        // Bloques
        for (const auto& block : blocks) {
            Color color = COLOR_BLACK;
            switch (block.type) {
                case BlockType::NORMAL: color = COLOR_GREEN; break;
                case BlockType::PENALTY: color = COLOR_RED; break;
                case BlockType::DEADLY: color = COLOR_ORANGE; break;
            }
            
            int px = block.x * TILE_SIZE;
            int py = block.y * TILE_SIZE;
            drawRect(px, py, TILE_SIZE, TILE_SIZE, color);
            drawBorder(px, py, TILE_SIZE, TILE_SIZE);
        }
        
        // Power-ups
        for (const auto& pu : powerUps) {
            Color color = COLOR_BLACK;
            switch (pu.type) {
                case PowerUpType::WALL_PASS: color = COLOR_CYAN; break;
                case PowerUpType::DOUBLE_POINTS: color = COLOR_YELLOW; break;
                case PowerUpType::MAGNETO: color = COLOR_PURPLE; break;
                case PowerUpType::GHOST_MODE: color = COLOR_BLUE; break;
                case PowerUpType::SHRINK: color = COLOR_RED; break;
            }
            
            int px = pu.x * TILE_SIZE;
            int py = pu.y * TILE_SIZE;
            drawRect(px, py, TILE_SIZE, TILE_SIZE, color);
            drawBorder(px, py, TILE_SIZE, TILE_SIZE);
        }
        
        // Serpiente
        for (size_t i = 0; i < snake.size(); i++) {
            int px = snake[i].x * TILE_SIZE;
            int py = snake[i].y * TILE_SIZE;
            
            if (i == 0) {
                drawRect(px, py, TILE_SIZE, TILE_SIZE, COLOR_BLUE);
            } else {
                drawRect(px, py, TILE_SIZE, TILE_SIZE, COLOR_DARK_BLUE);
            }
            drawBorder(px, py, TILE_SIZE, TILE_SIZE);
        }
        
        // Información en texto simple
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_Rect infoBar = {0, WINDOW_HEIGHT - 30, WINDOW_WIDTH, 30};
        SDL_RenderFillRect(renderer, &infoBar);
        
        SDL_RenderPresent(renderer);
    }
    
    void run() {
        const Uint32 frameDelay = 1000 / FPS;
        Uint32 frameStart;
        int frameTime;
        
        while (running) {
            frameStart = SDL_GetTicks();
            
            handleInput();
            update();
            render();
            
            frameTime = SDL_GetTicks() - frameStart;
            if (frameDelay > (Uint32)frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }
    }
    
    void cleanup() {
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

// ==================== MAIN ====================
int main(int argc, char* argv[]) {
    SnakeGame game;
    
    if (!game.init()) {
        std::cerr << "No se pudo inicializar el juego" << std::endl;
        return 1;
    }
    
    game.run();
    
    std::cout << "¡Gracias por jugar Snake vs Block!" << std::endl;
    return 0;
}
