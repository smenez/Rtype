#include <SDL.h>
#include <stdlib.h>

void dessin_carre(int x, int y, int width, int height,
    SDL_Renderer* renderer, SDL_Texture* texture) {
    SDL_Rect rectangle = { x, y, width, height };
    SDL_RenderCopy(renderer, texture, NULL, &rectangle);
}