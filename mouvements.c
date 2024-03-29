#include <SDL.h>
#include <stdlib.h>

void handleMovement(int* x, int* y) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_UP] && *y > 0) {
        *y -= 5;
    }
    if (keystate[SDL_SCANCODE_DOWN] && *y < 600) {
        *y += 5;
    }
    if (keystate[SDL_SCANCODE_LEFT] && *x > 0) {
        *x -= 5;
    }
    if (keystate[SDL_SCANCODE_RIGHT] && *x < 800) {
        *x += 5;
    }
}