#include "son.h"
#include <SDL_mixer.h>

void initSound() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
        SDL_Quit();
        return;
    }
}

// Chargement et lecture de l'effet sonore de tir
void tire() {
    Mix_Chunk* tireSound = Mix_LoadWAV("C:/Users/sasha/Documents/starShip/Vaisseaux/tire.wav");
    if (tireSound == NULL) {
        printf("Failed to load tire sound: %s\n", Mix_GetError());
        return;
    }
    Mix_PlayChannel(-1, tireSound, 0);
    Mix_FreeChunk(tireSound);
}

// Chargement et lecture de l'effet sonore d'explosion
void explo() {
    Mix_Chunk* exploSound = Mix_LoadWAV("C:/Users/sasha/Documents/starShip/Vaisseaux/explosions.wav");
    if (exploSound == NULL) {
        printf("Failed to load explosion sound: %s\n", Mix_GetError());
        return;
    }
    Mix_PlayChannel(-1, exploSound, 0);
    Mix_FreeChunk(exploSound);
}

// Chargement et lecture de la musique de fond
void sonFond() {
    Mix_Music* fondMusic = Mix_LoadMUS("C:/Users/sasha/Documents/starShip/Vaisseaux/sonFond.MP3");
    if (fondMusic == NULL) {
        printf("Failed to load background music: %s\n", Mix_GetError());
        return;
    }
    Mix_PlayMusic(fondMusic, -1);
    // Ne pas appeler Mix_FreeMusic(fondMusic) ici pour maintenir la musique en cours de lecture
}