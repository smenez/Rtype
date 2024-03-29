#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdio.h>
#include"ennemis.h"

struct SDL init();
typedef struct {
    int x, y;
    int w, h;
} Rectangle;

typedef struct {
    Rectangle rect;
    bool active;
} Projectile;

struct Var {
    bool quit;
    SDL_Rect vaisseau;
    int score;
    int km;
    int niveau;
    int vie;
};

void handleEvents(SDL_Rect* vaisseau, bool* quit, Projectile projectiles[], int* num_projectiles);
void updateProjectiles(Projectile projectiles[], int* num_projectiles);
void render(SDL_Renderer* renderer, SDL_Rect* vaisseau,
    Projectile projectiles[], int num_projectiles, SDL_Rect squares[NUM_SQUARES]);