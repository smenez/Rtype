#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600
#define PLAYER_SIZE 50
#define PROJECTILE_SIZE 10
#define PROJECTILE_SPEED 10
#define MAX_PROJECTILES 100


struct SDL {
    SDL_Window* window;
    SDL_Renderer* renderer;
};