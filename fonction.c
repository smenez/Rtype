#include "fonction.h"
#include "main.h"
#include"ennemis.h"
#include"son.h"
#include "affichage.h"
#include <SDL_mixer.h>


struct SDL init()
{
    // init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to load SDL\n");
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() == -1) {
        printf("Erreur d'initialisation de SDL_ttf : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // create SDL window
    SDL_Window* window = SDL_CreateWindow("Red square moving",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Failed to create window\n");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // create render 
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Failed to create renderer\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    return (struct SDL) { window, renderer };
}
void fondre(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_Surface* surface;
    SDL_Texture* texture;

    surface = SDL_LoadBMP("C:/Users/sasha/Documents/StarShip/Vaisseaux/fond.BMP");
    if (surface == NULL) {
        printf("Erreur lors du chargement de l'image de l'épée : %s\n", SDL_GetError());
        return 1;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);
}
void handleEvents(SDL_Rect* vaisseau, bool* quit, Projectile projectiles[], int* num_projectiles) {
    SDL_Event event;
    SDL_PumpEvents(); // Met à jour l'état du clavier

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP] && vaisseau->y > 0) vaisseau->y -= 5;
    if (state[SDL_SCANCODE_DOWN] && vaisseau->y < WINDOW_HEIGHT - vaisseau->h) vaisseau->y += 5;
    if (state[SDL_SCANCODE_LEFT] && vaisseau->x > 0) vaisseau->x -= 5;
    if (state[SDL_SCANCODE_RIGHT] && vaisseau->x < WINDOW_WIDTH - vaisseau->w) vaisseau->x += 5;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) *quit = true;
        else if (event.type == SDL_KEYDOWN) {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_SPACE) {
                tire();
                if (*num_projectiles < MAX_PROJECTILES) {
                    projectiles[*num_projectiles].rect.x = vaisseau->x + vaisseau->w;
                    projectiles[*num_projectiles].rect.y = vaisseau->y + vaisseau->h / 2 - PROJECTILE_SIZE / 2;
                    projectiles[*num_projectiles].rect.w = 50;
                    projectiles[*num_projectiles].rect.h = 20;
                    projectiles[*num_projectiles].active = true;
                    (*num_projectiles)++;
                }
                else {
                    // Réinitialiser le nombre de balles à zéro pour réutiliser le tableau
                    *num_projectiles = 0;
                }
            }
        }
    }
}
void updateProjectiles(Projectile projectiles[], int* num_projectiles) {
    for (int i = 0; i < *num_projectiles; i++) {
        if (projectiles[i].active) {
            projectiles[i].rect.x += PROJECTILE_SPEED;
            if (projectiles[i].rect.x > WINDOW_WIDTH) {
                projectiles[i].active = false;
            }
        }

    }
}
void render(SDL_Renderer* renderer, SDL_Rect* vaisseau, Projectile projectiles[], 
    int num_projectiles, SDL_Rect squares[NUM_SQUARES]) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    fondre(renderer);
    // Render player
    CreateVaisseau(renderer, vaisseau);

    // Render projectiles
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Surface* surface;
    SDL_Texture* texture;

    surface = SDL_LoadBMP("C:/Users/sasha/Documents/StarShip/Vaisseaux/laser.BMP");
    if (surface == NULL) {
        printf("Erreur lors du chargement de l'image de l'épée : %s\n", SDL_GetError());
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    for (int i = 0; i < num_projectiles; i++) {
        if (projectiles[i].active) {
            SDL_Rect projectileRect = { projectiles[i].rect.x, projectiles[i].rect.y,
                projectiles[i].rect.w, projectiles[i].rect.h };
            SDL_RenderCopy(renderer, texture, NULL, &projectileRect); // Rendre le projectile avec les dimensions spécifiées
        }
    }
    SDL_DestroyTexture(texture);
    drawSquares(renderer, squares);
}