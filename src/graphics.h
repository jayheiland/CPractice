#pragma once

#include "game_data.h"

enum CameraPanDirection{PANUP, PANDOWN, PANLEFT, PANRIGHT};
enum CameraOrbitDirection{ORBITLEFT, ORBITRIGHT};

void graphicsSetup(gameData *dt);

void graphicsDraw(GraphicsLayer *grph);

void onButtonLeftClick(uint buttonID);

GraphObjID getLeftClickedButtonID();

void resetLeftClickedButtonID();

void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

int getKeyPressed();

void resetKeyPressed();

void panCamera(gameData *dt, CameraPanDirection direction);

void orbitCamera(gameData *dt, CameraOrbitDirection direction);