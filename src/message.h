#ifndef MESSAGE_H
#define MESSAGE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include <string>

#include <SDL2/SDL.h>

#include "world.h"
#include "creature.h"

#define TOK_MAX 4

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
    creatureGroup playerCrts;
    creatureGroup otherCrts;
} worldData;

void send(const char msg[]);

#endif