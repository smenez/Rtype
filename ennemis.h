#include <SDL.h>
#include"son.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define NUM_SQUARES 10
#define SQUARE_SIZE 20
#define SQUARE_SPEED 2


void initializeMonsterTexture(SDL_Renderer* renderer);
void initializeSquares(SDL_Rect squares[NUM_SQUARES]);
void updateSquares(SDL_Rect squares[NUM_SQUARES], int* num_squares, struct Var* var);
void monster(SDL_Renderer* renderer, SDL_Rect* monstre);
void drawSquares(SDL_Renderer* renderer, SDL_Rect squares[NUM_SQUARES]);
