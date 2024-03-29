	#include <SDL_ttf.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define NUM_SQUARES 10
#define SQUARE_SIZE 20
#define SQUARE_SPEED 2

int affichagePolice(SDL_Renderer* renderer, TTF_Font* font, struct Var* var);
void CreateVaisseau(SDL_Renderer* renderer, SDL_Rect* vaisseau);
void handleCollisions(SDL_Rect squares[NUM_SQUARES], int num_projectiles, struct Projectile projectiles[], struct Var* var);
void handleVaisseauCollisions(SDL_Rect* vaisseau, SDL_Rect squares[NUM_SQUARES], struct Var* var);
