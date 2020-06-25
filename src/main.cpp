#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <unordered_map>
#include <iostream>

#include <SDL2/SDL.h>

#include "world.h"
#include "general.h"
#include "user_input.h"
#include "graphics.h"
#include "creature_group.h"
#include "object_group.h"
#include "material_group.h"

#define NULL_ID 0

//engine settings; hardcoded for now, to be loaded from a file later
engineData ENGINE_DATA;
ID masterIDCounter;

void testWorld(){
    Vec3 worldSize = {10,10,10};
    struct worldNode ***world = newWorld(&worldSize);
    Vec3 test = {0,0,0};
    Vec3 testDest = {worldSize.x-1,worldSize.y-1,worldSize.z-1};
    Vec3 *path;
    int pathLen;
    path = worldPath(world, &worldSize, &test, &testDest, &pathLen);
    printPath(path, pathLen);
    free(path);
    delWorld(world, &worldSize);
}

void gameSetup(){
    srand(88393401);
    masterIDCounter = 1;
    ENGINE_DATA.quitGame = 0;
    setupGraphics(&ENGINE_DATA);
}

void processModels(gameData *data){
    processCreatures(data);
}

void gameLoop(){
    gameData data;
    //setup GUI

    //test
    std::string filePath = "/Users/jayheiland/Projects/Cartwright/data/";
    loadMaterials(&data.matGroup, filePath + "materials.txt");
    printMaterials(&data.matGroup);
    loadObjectRules(&data.objRules, filePath + "multiObjectRules.txt");
    loadObjectRules(&data.objRules, filePath + "elementalObjectRules.txt");
    loadCreatureRules(&data.crtRules, filePath + "creatureRules.txt");
    loadFactions(&data.fctGroup, filePath + "factions.txt");

    ID testHuman1 = createCreature(&data, 100000, "Luneth", 100000);
    ID testHuman2 = createCreature(&data, 100000, "Ingus", 773941);
    printCreatures(&data.crtGroup);
    printObjects(&data.objGroup);
    ID testEquipment = createObject(&data, 735631);
    equipObject(&data, getBody(&data.crtGroup, testHuman1), testEquipment);
    printObjects(&data.objGroup);
    unequipObject(&data.objGroup, getBody(&data.crtGroup, testHuman1), testEquipment);
    printObjects(&data.objGroup);

    //game loop
    while(!ENGINE_DATA.quitGame){
        processUserInputs();
        processModels(&data);
        drawGraphics(&ENGINE_DATA);
    }
}

void gameShutdown(){
    shutdownGraphics(&ENGINE_DATA);
}

int main(int argc, char** args) {
    gameSetup();
    gameLoop();
    gameShutdown();
    return 0;
}
