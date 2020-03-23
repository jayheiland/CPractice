#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string.h>

#include <SDL2/SDL.h>

#include "message.h"

void setupGraphics(engineData *engData);
void drawGraphics(engineData *engData, worldData *woData);
void shutdownGraphics(engineData *engData);
void refreshGraphicsSettings(engineData *engData);
void drawRect(double x, double y, double width, double height);
void drawText(std::string text, engineData *engData, double x, double y, int width, int height);

#endif