#include<SDL.h>
#include <stdbool.h>
#include <stdlib.h>


bool initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    // init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to load SDL\n");
        return false;
    }

    // create SDL window
    *window = SDL_CreateWindow("Red square moving",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Failed to create window\n");
        SDL_Quit();
        return false;
    }

    // create renderer 
    *renderer = SDL_CreateRenderer(*window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderer == NULL) {
        printf("Failed to create renderer\n");
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return false;
    }

    return true;
}