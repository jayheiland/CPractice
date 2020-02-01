#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string.h>

#include <SDL2/SDL.h>

#include "message.h"

void setupGraphics(engineData *engData);
void drawGraphics(engineData *engData);
void shutdownGraphics(engineData *engData);

#endif