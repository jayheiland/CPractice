#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "world.h"
#include "general.h"
#include "user_input.h"
#include "graphics.h"
#include "creature.h"
#include "object_group.h"
#include "material_group.h"

//engine settings; hardcoded for now, to be loaded from a file later
engineData ENGINE_DATA;
ID masterIDCounter;

//game data
std::unordered_map<ID, Object> objGroup;
std::unordered_map<ID, Creature> crtGroup;
std::unordered_map<creatureCode, CreatureRule> crtRules;
std::unordered_map<std::string, Material> matGroup;

std::unordered_map<objectCode, MultiObjectRule> multiObjRules;
std::unordered_map<objectCode, ElementalObjectRule> elemObjRules;

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

void testCreatureGroup(){

}

void gameSetup(){
    masterIDCounter = 1;
    ENGINE_DATA.quitGame = 0;
    setupGraphics(&ENGINE_DATA);
}

void gameLoop(){
    //setup GUI

    //test
    loadMaterials("/Users/jayheiland/Projects/CPractice/data/mats.txt");
    printMaterials();

    loadObjectRules(&objGroup, "/Users/jayheiland/Projects/CPractice/data/multiObjectRules.txt", "/Users/jayheiland/Projects/CPractice/data/elementalObjectRules.txt");
    createObject(&objGroup, 475603);
    printObjects(&objGroup);

    loadCreatureRules("/Users/jayheiland/Projects/CPractice/data/creatureRules.txt");
    addCreature(&crtGroup, &objGroup, 100000, "Luneth");
    printObjects(&objGroup);

    //game loop
    while(!ENGINE_DATA.quitGame){
        processUserInputs();
        drawGraphics(&ENGINE_DATA);
    }
}

void gameShutdown(){
    shutdownGraphics(&ENGINE_DATA);
}

int main(int argc, char** args) {
    gameSetup();

    testCreatureGroup();

    gameLoop();
    gameShutdown();

    return 0;
}
