#pragma once

#include "game_data.h"
#include "graphics.h"
#include "objectm.h"
#include "creaturem.h"

void startBattle(gameData *dt);

void processBattle(gameData *dt);

void createTurnQueue(gameData *dt);

void advanceTurnQueue(gameData *dt);

void createWeaponSelectorMenu(gameData *dt, ID playerChar);

void createTargetSelectorMenu(gameData *dt, ID character);