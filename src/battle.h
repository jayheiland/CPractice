#pragma once

#include "game_data.h"
#include "graphics.h"
#include "objectm.h"
#include "creaturem.h"

void startBattle(gamedata *dt);

void processBattle(gamedata *dt);

void createTurnQueue(gamedata *dt);

void advanceTurnQueue(gamedata *dt);

void createWeaponSelectorMenu(gamedata *dt, ID playerChar);

void createTargetSelectorMenu(gamedata *dt, ID character);