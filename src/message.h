#ifndef MESSAGE_H
#define MESSAGE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>

#include "world.h"
#include "creature.h"
#include "creature_group.h"
#include "object_group.h"
#include "general.h"
#include "material_group.h"

typedef struct{
    int quitGame;
    char debugConsoleStr[1024];
    SDL_Window *window;
    SDL_Renderer *renderer;
    int defaultGuiBkgColor[4];
    int windowWidth, windowHeight;
    int debugMode;
} engineData;

void send(std::string msg);

#endif