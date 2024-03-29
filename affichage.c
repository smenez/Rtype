#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#include "affichage.h"
#include "fonction.h"
#include <SDL_mixer.h>


int affichagePolice(SDL_Renderer* renderer, TTF_Font* font, struct Var* var) {
    SDL_Surface* textSurface = NULL;
    SDL_Texture* textTexture = NULL;
    SDL_Surface* textSurface2 = NULL;
    SDL_Texture* textTexture2 = NULL;
    SDL_Color textColor = { 255, 255, 255, 255 }; // Blanc
    char scoreText[100];
    char scoreText2[100];
    snprintf(scoreText, sizeof(scoreText), "Score : %d          Km : %d", var->score, var->km);
    snprintf(scoreText2, sizeof(scoreText2), "Niveau : %d          Vie : %d", var->niveau, var->vie);

    textSurface = TTF_RenderText_Solid(font, scoreText, textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textSurface2 = TTF_RenderText_Solid(font, scoreText2, textColor);
    textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);

    SDL_Rect textRect = { 200, 30, textSurface->w, textSurface->h }; // Position et taille du texte
    SDL_Rect textRect2 = { 200, 70, textSurface2->w, textSurface2->h }; // Position et taille du texte
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface2);
    SDL_DestroyTexture(textTexture2);
    return 0;
}

void CreateVaisseau(SDL_Renderer* renderer, SDL_Rect* vaisseau)
{

    SDL_Surface* surface;
    SDL_Texture* texture;

    surface = SDL_LoadBMP("C:/Users/sasha/Documents/StarShip/Vaisseaux/vaisseau.BMP");
    if (surface == NULL) {
        printf("Erreur lors du chargement de l'image de l'épée : %s\n", SDL_GetError());
        return 1;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer, texture, NULL, vaisseau);
    SDL_DestroyTexture(texture);
}


void handleCollisions(SDL_Rect squares[NUM_SQUARES], int num_projectiles,
    Projectile projectiles[], struct Var* var) {
    var->km++;
    for (int i = 0; i < NUM_SQUARES; i++) {
        for (int j = 0; j < num_projectiles; j++) {
            if (projectiles[j].active) {
                SDL_bool collision = SDL_HasIntersection(&squares[i], &projectiles[j]);
                if (collision == SDL_TRUE) {

                    var->score += 10;

                    explo();
                    // Collision détectée entre le carré i et le projectile j
                    // Marquer le carré comme inactif
                    squares[i].x = SCREEN_WIDTH + rand() % (2 * SCREEN_WIDTH); // Déplacez le carré hors de l'écran pour le "supprimer"
                    squares[i].y = rand() % (SCREEN_HEIGHT - SQUARE_SIZE);

                    // Marquer le projectile comme inactif
                    projectiles[j].rect.x = -100; // Déplacez le projectile hors de l'écran pour le "supprimer"
                    projectiles[j].rect.y = -100;
                    projectiles[j].active = false;
                }
            }
        }
    }
}

void handleVaisseauCollisions(SDL_Rect* vaisseau, SDL_Rect squares[NUM_SQUARES], struct Var* var) {
    for (int i = 0; i < NUM_SQUARES; i++) {
        SDL_bool collision = SDL_HasIntersection(vaisseau, &squares[i]);
        if (collision == SDL_TRUE) {
            var->vie -= 1;
            printf("Collision detected between vaisseau and square %d\n", i);
            for (int j = 0; j < NUM_SQUARES; j++) {
                squares[j].x = SCREEN_WIDTH + rand() % (2 * SCREEN_WIDTH);
                squares[j].y = rand() % (SCREEN_HEIGHT - SQUARE_SIZE);
            }
            // Gérer la collision comme vous le souhaitez, par exemple, vous pouvez quitter le jeu
            vaisseau->x = (SCREEN_WIDTH - vaisseau->w) / 2;
            vaisseau->y = (SCREEN_HEIGHT - vaisseau->h) / 2;

            break; // Sortir de la boucle, car une collision a été détectée

        }
    }
}