#include <SDL.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include"main.h"
#include"fonction.h"
#include"son.h"
#include "ennemis.h"
#include "affichage.h"
#include "start.h"
#include <SDL_mixer.h>

static struct Var Variables()
{
    bool quit = false;
    SDL_Rect vaisseau = {
        300, 200,
        100, 100
    };
    int score = 0;
    int km = 0;
    int niveau = 0;
    int vie = 5;
    return (struct Var) { quit, vaisseau, score, km, niveau, vie };
}

void end(SDL_Renderer* renderer, SDL_Window* window, Projectile projectiles[], TTF_Font* font) {
    TTF_CloseFont(font);
    TTF_Quit();
    free(&projectiles);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    struct SDL valeurs = init();
    SDL_Window* window = valeurs.window;
    SDL_Renderer* renderer = valeurs.renderer;
    TTF_Font* font = TTF_OpenFont("C:/Users/sasha/Downloads/fast_99/fast99.ttf", 24);
    initSound();
    struct Var var = Variables();
    enum MenuOption option = showMainMenu(renderer, font);
    Projectile projectiles[MAX_PROJECTILES];
    int num_projectiles = 1;
    bool quit = false;
    initializeMonsterTexture(renderer);
    SDL_Rect squares[NUM_SQUARES];
    initializeSquares(squares);

    while (!quit) {
        switch (option) {
        case START_GAME:
            sonFond();
            while (!quit) {
                handleEvents(&var.vaisseau, &quit, projectiles, &num_projectiles);
                updateProjectiles(projectiles, &num_projectiles);
                render(renderer, &var.vaisseau, projectiles, num_projectiles, squares, &var);
                affichagePolice(renderer, font, &var);
                updateSquares(squares, squares, &var);
                handleCollisions(squares, num_projectiles, projectiles, &var);
                handleVaisseauCollisions(&var.vaisseau, squares, &var);
                if (var.vie == 0) break;
                SDL_RenderPresent(renderer);
                SDL_Delay(16); // Cap frame rate to ~60 FPS
            }
        case QUIT_GAME:
            quit = true;
        }
    }
    end(renderer, window, projectiles, font);
    return 0;
}