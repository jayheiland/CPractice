#pragma once

#include "game_data.h"
#include "creature_group.h"
#include "graphics.h"

void startBattle(gameData *dt);

void processBattle(gameData *dt);

void createTurnQueue(gameData *dt);

void advanceTurnQueue(gameData *dt);

void createWeaponSelectorMenu(gameData *dt, ID playerChar);

void createTargetSelectorMenu(gameData *dt, ID character);