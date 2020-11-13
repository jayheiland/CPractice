#pragma once

#include "creature_group.h"
#include "golden_plains.h"

void graphicsSetup(GraphicsLayer *grph);

void graphicsDraw(GraphicsLayer *grph);

void onButtonLeftClick(uint buttonID);

GraphObjID getLeftClickedButtonID();

void resetLeftClickedButtonID();

void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

int getKeyPressed();

void resetKeyPressed();