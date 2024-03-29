#include <stdbool.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdio.h>
#include "fonction.h"
#include "main.h"
#include "ennemis.h"
#include <time.h>
#include <SDL_mixer.h>


#define NUM_SQUARES 20
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SQUARE_SIZE 20
#define SQUARE_SPEED 5

SDL_Texture* monsterTexture = NULL;
void initializeMonsterTexture(SDL_Renderer* renderer) {
    SDL_Surface* surface = SDL_LoadBMP("C:/Users/sasha/Documents/starShip/Vaisseaux/monstr.BMP");
    if (surface == NULL) {
        printf("Erreur lors du chargement de l'image du monstre : %s\n", SDL_GetError());
        return;
    }
    monsterTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}


void initializeSquares(SDL_Rect squares[NUM_SQUARES]) {
    srand(time(NULL));
    for (int i = 0; i < NUM_SQUARES; i++) {
        squares[i].x = SCREEN_WIDTH + rand() % (2 * SCREEN_WIDTH);
        squares[i].y = rand() % (SCREEN_HEIGHT - SQUARE_SIZE);
        squares[i].w = SQUARE_SIZE;
        squares[i].h = SQUARE_SIZE;
    }
}
void monster(SDL_Renderer* renderer, SDL_Rect* monstre)
{

    SDL_Surface* surface;
    SDL_Texture* texture;

    surface = SDL_LoadBMP("C:/Users/rvaxelaire/Documents/t rex/monstr.BMP");
    if (surface == NULL) {
        printf("Erreur lors du chargement de l'image de l'épée : %s\n", SDL_GetError());
        return 1;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer, texture, NULL, monstre);
    SDL_DestroyTexture(texture);
}
void drawMonster(SDL_Renderer* renderer, SDL_Rect* monsterRect) {
    if (monsterTexture != NULL) {
        SDL_RenderCopy(renderer, monsterTexture, NULL, monsterRect);
    }
}
void drawSquares(SDL_Renderer* renderer, SDL_Rect squares[NUM_SQUARES]) {
    for (int i = 0; i < NUM_SQUARES; i++) {
        drawMonster(renderer, &squares[i]);
    }
}



void updateSquares(SDL_Rect squares[NUM_SQUARES], int* num_squares, struct Var* var) {
    for (int i = 0; i < NUM_SQUARES; i++) {
        if (var->km <= 500) {
            squares[i].x -= SQUARE_SPEED;
            var->niveau = 1;
        }
        else if (500<var->km && var->km<=1500) {
            squares[i].x -= 1.3 * SQUARE_SPEED;
            var->niveau = 2;
        }
        else{
            squares[i].x -= 1.9 * SQUARE_SPEED;
            var->niveau = 3;
        }
        if (squares[i].x + SQUARE_SIZE < 0) {   
            // Réinitialiser la position des carrés à une position aléatoire en dehors de l'écran
            squares[i].x = SCREEN_WIDTH + rand() % (2 * SCREEN_WIDTH);
            squares[i].y = rand() % (SCREEN_HEIGHT - SQUARE_SIZE);
        }
    }
}
