#pragma once
#include <stdbool.h>

enum MenuOption {
    START_GAME,
    QUIT_GAME,
    OTHER_OPTION,
};

enum MenuOption showMainMenu(SDL_Renderer* renderer, TTF_Font* font);