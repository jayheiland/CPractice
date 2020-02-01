#ifndef MESSAGE_H
#define MESSAGE_H

#include <string.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "world.h"

typedef struct{
    int quitGame;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int windowWidth, windowHeight;
    int pauseGame, pauseWorld;
} engineData;

typedef struct{
    
} worldData;

void send(char msg[]);

#endif