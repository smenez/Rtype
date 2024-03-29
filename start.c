#include "affichage.h"
#include "start.h"
#include "fonction.h"


void raccourcis(SDL_Renderer* renderer, TTF_Font* font) {
    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dessiner le menu
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect startButton = { 300, 200, 200, 50 };
    SDL_Rect quitButton = { 300, 300, 200, 50 };
    SDL_RenderDrawRect(renderer, &startButton);
    SDL_RenderDrawRect(renderer, &quitButton);
    // Ajouter du texte
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Start Game", textColor);
    if (!textSurface) {
        printf("Erreur lors du rendu du texte : %s\n", TTF_GetError());
        // Gérer l'erreur
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &startButton);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    textSurface = TTF_RenderText_Solid(font, "Quit Game", textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &quitButton);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Rafraîchir l'affichage
    SDL_RenderPresent(renderer);
}

enum MenuOption showMainMenu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Event event;
    int mouseX, mouseY;
    enum MenuOption option = QUIT_GAME; // Par défaut, quitter le jeu

    while (1) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                return QUIT_GAME;
            case SDL_MOUSEBUTTONDOWN:
                mouseX = event.button.x;
                mouseY = event.button.y;
                // Vérifier si le clic de la souris est sur une option
                if (mouseX >= 300 && mouseX <= 500) {
                    if (mouseY >= 200 && mouseY <= 250) {
                        return START_GAME;
                    }
                    else if (mouseY >= 300 && mouseY <= 350) {
                        return QUIT_GAME;
                    }
                }
                break;
            }
            raccourcis(renderer, font);
        }
    }
}

