#ifndef MESSAGE_H
#define MESSAGE_H

#include <string.h>
#include <stdio.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "world.h"
#include "creature.h"

typedef struct{
    unsigned int randomSeed;
    int quitGame;
    char debugConsoleStr[100];
    SDL_Window *window;
    SDL_Renderer *renderer;
    int windowWidth, windowHeight;
    int debugMode, pauseWorld;
} engineData;

typedef struct{
    creatureGroup playerUnits;
    creatureGroup otherCreatures;
} worldData;

void send(char msg[]);

#endif