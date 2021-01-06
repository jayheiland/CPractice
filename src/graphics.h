#pragma once

#include "game_data.h"

void graphicsSetup(GraphicsLayer *grph);

void graphicsDraw(GraphicsLayer *grph);

void onButtonLeftClick(uint buttonID);

GraphObjID getLeftClickedButtonID();

void resetLeftClickedButtonID();

void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

int getKeyPressed();

void resetKeyPressed();