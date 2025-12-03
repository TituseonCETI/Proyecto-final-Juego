#!/usr/bin/env python3
"""
Snake vs Block - Juego en Python con Pygame
Con Power-ups y mapa dinámico
"""

import pygame
import random
import sys
from enum import Enum

# Inicializar Pygame
pygame.init()

# Constantes iniciales
BASE_WINDOW_WIDTH = 800
BASE_WINDOW_HEIGHT = 600
GRID_SIZE = 20
BASE_GRID_WIDTH = BASE_WINDOW_WIDTH // GRID_SIZE
BASE_GRID_HEIGHT = BASE_WINDOW_HEIGHT // GRID_SIZE

# Colores
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
DARK_RED = (200, 50, 50)
GREEN = (0, 180, 0)
LIME = (0, 255, 0)
YELLOW = (255, 255, 0)
GRAY = (128, 128, 128)
CYAN = (0, 255, 255)
MAGENTA = (255, 0, 255)
ORANGE = (255, 165, 0)
PURPLE = (128, 0, 128)
DARK_GRAY = (64, 64, 64)

# Velocidades
FPS = 60
INITIAL_SPEED = 10

class Direction(Enum):
    UP = (0, -1)
    DOWN = (0, 1)
    LEFT = (-1, 0)
    RIGHT = (1, 0)

class BlockType(Enum):
    """Tipos de bloques"""
    NORMAL = "normal"  # Rojo - suma puntos
    PENALTY = "penalty"  # Gris - quita puntos
    DEADLY = "deadly"  # Púrpura - mata

class PowerUpType(Enum):
    """Tipos de power-ups"""
    WALL_PASS = "wall_pass"  # Atravesar paredes por 5 segundos
    DOUBLE_POINTS = "double_points"  # Doble puntos por 8 segundos
    MAGNETO = "magneto"  # Los bloques se atraen por 6 segundos
    GHOST_MODE = "ghost_mode"  # Atravesar todo por 4 segundos
    SHRINK = "shrink"  # Encogerse por 6 segundos
    
class PowerUp:
    """Clase para los power-ups"""
    def __init__(self, x, y, power_type):
        self.x = x
        self.y = y
        self.power_type = power_type

class Block:
    """Clase para los bloques"""
    def __init__(self, x, y, block_type=BlockType.NORMAL):
        self.x = x
        self.y = y
        self.block_type = block_type

class SnakeGame:
    def __init__(self):
        self.window_width = BASE_WINDOW_WIDTH
        self.window_height = BASE_WINDOW_HEIGHT
        self.grid_width = BASE_GRID_WIDTH
        self.grid_height = BASE_GRID_HEIGHT
        
        self.screen = pygame.display.set_mode((self.window_width, self.window_height))
        pygame.display.set_caption("Snake vs Block")
        self.clock = pygame.time.Clock()
        self.font = pygame.font.Font(None, 36)
        self.small_font = pygame.font.Font(None, 24)
        
        self.reset_game()
    
    def reset_game(self):
        """Inicializar/reiniciar el juego"""
        self.snake = [(self.grid_width // 2, self.grid_height // 2),
                      (self.grid_width // 2 - 1, self.grid_height // 2),
                      (self.grid_width // 2 - 2, self.grid_height // 2)]
        self.direction = Direction.RIGHT
        self.next_direction = Direction.RIGHT
        self.score = 0
        self.blocks_eaten = 0
        self.game_speed = INITIAL_SPEED
        self.speed_counter = 0
        self.game_over = False
        self.paused = False
        
        # Power-ups: duración y timers
        self.wall_pass_active = False
        self.wall_pass_timer = 0
        self.double_points_active = False
        self.double_points_timer = 0
        self.magneto_active = False
        self.magneto_timer = 0
        self.ghost_mode_active = False
        self.ghost_mode_timer = 0
        self.shrink_active = False
        self.shrink_timer = 0
        
        # Crear bloques
        self.blocks = []
        for _ in range(10):
            self.spawn_block()
        
        # Power-ups en el mapa
        self.power_ups = []
    
    def spawn_block(self):
        """Generar un nuevo bloque"""
        x = random.randint(0, self.grid_width - 1)
        y = random.randint(0, self.grid_height - 1)
        
        # Determinar tipo de bloque según progreso del juego
        block_type = BlockType.NORMAL
        if self.blocks_eaten >= 20:
            # A partir de 20 bloques comidos, 20% chance de penalty
            if random.random() < 0.2:
                block_type = BlockType.PENALTY
        if self.blocks_eaten >= 40:
            # A partir de 40 bloques comidos, 10% chance de deadly
            if random.random() < 0.1:
                block_type = BlockType.DEADLY
        
        self.blocks.append(Block(x, y, block_type))
    
    def spawn_power_up(self):
        """Generar un power-up aleatorio"""
        x = random.randint(0, self.grid_width - 1)
        y = random.randint(0, self.grid_height - 1)
        power_type = random.choice([PowerUpType.WALL_PASS, PowerUpType.DOUBLE_POINTS,
                                   PowerUpType.MAGNETO, PowerUpType.GHOST_MODE, 
                                   PowerUpType.SHRINK])
        self.power_ups.append(PowerUp(x, y, power_type))
    
    def expand_map(self):
        """Expandir el mapa dinámicamente"""
        self.grid_width += 2
        self.grid_height += 2
        self.window_width = self.grid_width * GRID_SIZE
        self.window_height = self.grid_height * GRID_SIZE
        self.screen = pygame.display.set_mode((self.window_width, self.window_height))
    
    def handle_input(self):
        """Procesar entrada del usuario"""
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return False
            
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP or event.key == pygame.K_w:
                    if self.direction != Direction.DOWN:
                        self.next_direction = Direction.UP
                elif event.key == pygame.K_DOWN or event.key == pygame.K_s:
                    if self.direction != Direction.UP:
                        self.next_direction = Direction.DOWN
                elif event.key == pygame.K_LEFT or event.key == pygame.K_a:
                    if self.direction != Direction.RIGHT:
                        self.next_direction = Direction.LEFT
                elif event.key == pygame.K_RIGHT or event.key == pygame.K_d:
                    if self.direction != Direction.LEFT:
                        self.next_direction = Direction.RIGHT
                elif event.key == pygame.K_SPACE:
                    self.paused = not self.paused
                elif event.key == pygame.K_r and self.game_over:
                    self.reset_game()
                elif event.key == pygame.K_ESCAPE:
                    return False
        
        return True
    
    def update(self):
        """Actualizar lógica del juego"""
        if self.game_over or self.paused:
            return
        
        # Actualizar timers de power-ups
        if self.wall_pass_active:
            self.wall_pass_timer -= 1
            if self.wall_pass_timer <= 0:
                self.wall_pass_active = False
        
        if self.double_points_active:
            self.double_points_timer -= 1
            if self.double_points_timer <= 0:
                self.double_points_active = False
        
        if self.magneto_active:
            self.magneto_timer -= 1
            if self.magneto_timer <= 0:
                self.magneto_active = False
        
        if self.ghost_mode_active:
            self.ghost_mode_timer -= 1
            if self.ghost_mode_timer <= 0:
                self.ghost_mode_active = False
        
        if self.shrink_active:
            self.shrink_timer -= 1
            if self.shrink_timer <= 0:
                self.shrink_active = False
        
        self.speed_counter += 1
        if self.speed_counter < self.game_speed:
            return
        
        self.speed_counter = 0
        self.direction = self.next_direction
        
        # Calcular nueva cabeza
        head_x, head_y = self.snake[0]
        dx, dy = self.direction.value
        new_x = head_x + dx
        new_y = head_y + dy
        
        # Verificar colisión con paredes
        if new_x < 0 or new_x >= self.grid_width or new_y < 0 or new_y >= self.grid_height:
            # Ghost Mode permite atravesar TODO
            if self.ghost_mode_active:
                new_x = new_x % self.grid_width
                new_y = new_y % self.grid_height
            # Wall Pass solo atraviesa paredes
            elif self.wall_pass_active:
                new_x = new_x % self.grid_width
                new_y = new_y % self.grid_height
            else:
                self.game_over = True
                return
        
        # Verificar colisión con el cuerpo
        if not self.ghost_mode_active and (new_x, new_y) in self.snake:
            self.game_over = True
            return
        
        # Agregar nueva cabeza
        self.snake.insert(0, (new_x, new_y))
        
        # Verificar colisión con power-ups
        for power_up in self.power_ups[:]:
            if (new_x, new_y) == (power_up.x, power_up.y):
                self.power_ups.remove(power_up)
                self.activate_power_up(power_up.power_type)
        
        # Magneto: mover bloques hacia la serpiente
        if self.magneto_active:
            self.move_blocks_to_snake()
        
        # Verificar colisión con bloques
        block_hit = None
        for block in self.blocks:
            if block.x == new_x and block.y == new_y:
                block_hit = block
                break
        
        if block_hit:
            self.blocks.remove(block_hit)
            
            # Manejar según tipo de bloque
            if block_hit.block_type == BlockType.NORMAL:
                # Bloque normal: suma puntos
                points = 20 if self.double_points_active else 10
                self.score += points
            elif block_hit.block_type == BlockType.PENALTY:
                # Bloque penalización: quita puntos
                self.score -= 20
                if self.score < 0:
                    self.score = 0
            elif block_hit.block_type == BlockType.DEADLY:
                # Bloque mortal: game over
                self.game_over = True
                return
            
            self.blocks_eaten += 1
            
            # Aumentar dificultad
            if self.game_speed > 3:
                self.game_speed -= 1
            
            # Generar nuevo bloque
            self.spawn_block()
            
            # Cada 10 bloques: spawn power-up y expandir mapa
            if self.blocks_eaten % 10 == 0:
                self.spawn_power_up()
                self.expand_map()
        else:
            # Si no comió bloque, eliminar cola
            self.snake.pop()
    
    def activate_power_up(self, power_type):
        """Activar un power-up"""
        if power_type == PowerUpType.WALL_PASS:
            self.wall_pass_active = True
            self.wall_pass_timer = 5 * FPS  # 5 segundos
        elif power_type == PowerUpType.DOUBLE_POINTS:
            self.double_points_active = True
            self.double_points_timer = 8 * FPS  # 8 segundos
        elif power_type == PowerUpType.MAGNETO:
            self.magneto_active = True
            self.magneto_timer = 6 * FPS  # 6 segundos
        elif power_type == PowerUpType.GHOST_MODE:
            self.ghost_mode_active = True
            self.ghost_mode_timer = 4 * FPS  # 4 segundos
        elif power_type == PowerUpType.SHRINK:
            self.shrink_active = True
            self.shrink_timer = 6 * FPS  # 6 segundos
    
    def move_blocks_to_snake(self):
        """Acercar bloques a la cabeza de la serpiente (Magneto)"""
        if not self.blocks:
            return
        
        head_x, head_y = self.snake[0]
        new_blocks = []
        
        for bx, by in self.blocks:
            # Mover bloque hacia la cabeza
            if bx < head_x:
                bx += 1
            elif bx > head_x:
                bx -= 1
            
            if by < head_y:
                by += 1
            elif by > head_y:
                by -= 1
            
            new_blocks.append((bx, by))
        
        self.blocks = new_blocks
    
    def move_blocks_to_snake(self):
        """Acercar bloques a la cabeza de la serpiente (Magneto)"""
        if not self.blocks:
            return
        
        head_x, head_y = self.snake[0]
        new_blocks = []
        
        for bx, by in self.blocks:
            # Mover bloque hacia la cabeza
            if bx < head_x:
                bx += 1
            elif bx > head_x:
                bx -= 1
            
            if by < head_y:
                by += 1
            elif by > head_y:
                by -= 1
            
            new_blocks.append((bx, by))
        
        self.blocks = new_blocks
    
    def draw(self):
        """Dibujar en la pantalla"""
        self.screen.fill(BLACK)
        
        # Dibujar bloques con colores según tipo
        for block in self.blocks:
            x, y = block.x, block.y
            
            if block.block_type == BlockType.NORMAL:
                # Rojo - bloque normal
                color = RED
                border_color = DARK_RED
            elif block.block_type == BlockType.PENALTY:
                # Gris - penalización
                color = DARK_GRAY
                border_color = GRAY
            else:  # DEADLY
                # Púrpura - mortal
                color = PURPLE
                border_color = (200, 0, 200)
            
            rect = pygame.Rect(x * GRID_SIZE + 2, y * GRID_SIZE + 2,
                              GRID_SIZE - 4, GRID_SIZE - 4)
            pygame.draw.rect(self.screen, color, rect)
            pygame.draw.rect(self.screen, border_color,
                           pygame.Rect(x * GRID_SIZE, y * GRID_SIZE,
                                      GRID_SIZE, GRID_SIZE), 2)
        
        # Dibujar power-ups con colores únicos
        for power_up in self.power_ups:
            x, y = power_up.x, power_up.y
            
            # Seleccionar color según tipo
            if power_up.power_type == PowerUpType.WALL_PASS:
                color = CYAN
                label = "W"
            elif power_up.power_type == PowerUpType.DOUBLE_POINTS:
                color = MAGENTA
                label = "2x"
            elif power_up.power_type == PowerUpType.MAGNETO:
                color = ORANGE
                label = "M"
            elif power_up.power_type == PowerUpType.GHOST_MODE:
                color = WHITE
                label = "G"
            else:  # SHRINK
                color = (255, 192, 203)  # Rosa
                label = "S"
            
            rect = pygame.Rect(x * GRID_SIZE + 3, y * GRID_SIZE + 3,
                              GRID_SIZE - 6, GRID_SIZE - 6)
            pygame.draw.rect(self.screen, color, rect)
            pygame.draw.rect(self.screen, WHITE,
                           pygame.Rect(x * GRID_SIZE, y * GRID_SIZE,
                                      GRID_SIZE, GRID_SIZE), 2)
        
        # Dibujar serpiente
        for i, (x, y) in enumerate(self.snake):
            rect = pygame.Rect(x * GRID_SIZE + 1, y * GRID_SIZE + 1,
                              GRID_SIZE - 2, GRID_SIZE - 2)
            
            # Si Ghost Mode está activo, dibujar serpiente semi-transparente
            if i == 0:
                # Cabeza
                color = LIME
                if self.ghost_mode_active:
                    # Crear superficie transparente
                    temp_surf = pygame.Surface((GRID_SIZE - 2, GRID_SIZE - 2))
                    temp_surf.set_alpha(128)
                    temp_surf.fill(color)
                    self.screen.blit(temp_surf, (x * GRID_SIZE + 1, y * GRID_SIZE + 1))
                elif self.shrink_active:
                    # Dibujar más pequeño
                    small_rect = pygame.Rect(x * GRID_SIZE + 5, y * GRID_SIZE + 5,
                                           GRID_SIZE - 10, GRID_SIZE - 10)
                    pygame.draw.rect(self.screen, color, small_rect)
                else:
                    pygame.draw.rect(self.screen, color, rect)
                pygame.draw.rect(self.screen, GREEN,
                               pygame.Rect(x * GRID_SIZE, y * GRID_SIZE,
                                          GRID_SIZE, GRID_SIZE), 2)
            else:
                # Cuerpo
                if self.ghost_mode_active:
                    temp_surf = pygame.Surface((GRID_SIZE - 2, GRID_SIZE - 2))
                    temp_surf.set_alpha(128)
                    temp_surf.fill(GREEN)
                    self.screen.blit(temp_surf, (x * GRID_SIZE + 1, y * GRID_SIZE + 1))
                elif self.shrink_active:
                    # Dibujar más pequeño
                    small_rect = pygame.Rect(x * GRID_SIZE + 5, y * GRID_SIZE + 5,
                                           GRID_SIZE - 10, GRID_SIZE - 10)
                    pygame.draw.rect(self.screen, GREEN, small_rect)
                else:
                    pygame.draw.rect(self.screen, GREEN, rect)
        
        # Dibujar información
        title = self.font.render("SNAKE VS BLOCK", True, YELLOW)
        self.screen.blit(title, (20, 10))
        
        score_text = self.font.render(f"Score: {self.score}", True, WHITE)
        self.screen.blit(score_text, (20, 50))
        
        # Mostrar estado de power-ups activos
        status_y = 90
        if self.wall_pass_active:
            wall_text = self.small_font.render(
                f"🚀 Wall Pass: {self.wall_pass_timer // FPS}s", True, CYAN)
            self.screen.blit(wall_text, (20, status_y))
            status_y += 25
        
        if self.double_points_active:
            double_text = self.small_font.render(
                f"2x Points: {self.double_points_timer // FPS}s", True, MAGENTA)
            self.screen.blit(double_text, (20, status_y))
            status_y += 25
        
        if self.magneto_active:
            magneto_text = self.small_font.render(
                f"🧲 Magneto: {self.magneto_timer // FPS}s", True, ORANGE)
            self.screen.blit(magneto_text, (20, status_y))
            status_y += 25
        
        if self.ghost_mode_active:
            ghost_text = self.small_font.render(
                f"👻 Ghost: {self.ghost_mode_timer // FPS}s", True, WHITE)
            self.screen.blit(ghost_text, (20, status_y))
            status_y += 25
        
        if self.shrink_active:
            shrink_text = self.small_font.render(
                f"✂️ Shrink: {self.shrink_timer // FPS}s", True, (255, 192, 203))
            self.screen.blit(shrink_text, (20, status_y))
            status_y += 25
        
        # Mostrar tamaño del mapa
        map_text = self.small_font.render(
            f"Map: {self.grid_width}x{self.grid_height} | Blocks: {self.blocks_eaten}", True, GRAY)
        self.screen.blit(map_text, (20, status_y))
        
        if self.game_over:
            game_over_text = self.font.render("GAME OVER!", True, RED)
            game_over_rect = game_over_text.get_rect(
                center=(self.window_width // 2, self.window_height // 2 - 50))
            self.screen.blit(game_over_text, game_over_rect)
            
            final_score = self.small_font.render(
                f"Final Score: {self.score}", True, WHITE)
            final_score_rect = final_score.get_rect(
                center=(self.window_width // 2, self.window_height // 2 + 20))
            self.screen.blit(final_score, final_score_rect)
            
            restart_text = self.small_font.render("Press R to Restart", True, YELLOW)
            restart_rect = restart_text.get_rect(
                center=(self.window_width // 2, self.window_height // 2 + 80))
            self.screen.blit(restart_text, restart_rect)
        
        if self.paused and not self.game_over:
            paused_text = self.font.render("PAUSED", True, YELLOW)
            paused_rect = paused_text.get_rect(
                center=(self.window_width // 2, self.window_height // 2 - 30))
            self.screen.blit(paused_text, paused_rect)
            
            resume_text = self.small_font.render("Press SPACE to Resume", True, WHITE)
            resume_rect = resume_text.get_rect(
                center=(self.window_width // 2, self.window_height // 2 + 30))
            self.screen.blit(resume_text, resume_rect)
        
        # Controles
        controls = self.small_font.render(
            "Arrow Keys/WASD: Move | SPACE: Pause | R: Restart | ESC: Quit",
            True, GRAY)
        self.screen.blit(controls, (20, self.window_height - 30))
        
        pygame.display.flip()
    
    def run(self):
        """Loop principal del juego"""
        running = True
        while running:
            running = self.handle_input()
            self.update()
            self.draw()
            self.clock.tick(FPS)
        
        pygame.quit()
        sys.exit()

if __name__ == "__main__":
    game = SnakeGame()
    game.run()
