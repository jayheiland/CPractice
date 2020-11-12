#pragma once

#include "creature_group.h"
#include "golden_plains.h"

void graphicsSetup(GraphicsLayer *grph);

void graphicsDraw(GraphicsLayer *grph);

void onButtonLeftClick(uint buttonID);

GraphObjID getLeftClickedButtonID();

void resetLeftClickedButtonID();

int getKeyPress();

void resetKeyPress();