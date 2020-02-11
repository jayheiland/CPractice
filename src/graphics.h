#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string.h>

#include <SDL2/SDL.h>

#include "message.h"

void setupGraphics(engineData *engData);
void drawGraphics(engineData *engData, worldData *woData);
void shutdownGraphics(engineData *engData);
void refreshGraphicsSettings(engineData *engData);

#endif