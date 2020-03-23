#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <unordered_map>
#include <string>

#include <SDL2/SDL.h>

#include "world.h"
#include "general.h"
#include "message.h"
#include "user_input.h"
#include "graphics.h"
#include "creature.h"
#include "object_group.h"
#include "material_group.h"
#include "gui.h"

//engine settings; hardcoded for now, to be loaded from a file later
engineData ENGINE_DATA;
ID masterIDCounter;

//global pointers to game data; only the "send" function is allowed to use this
worldData WORLD_DATA;

//global pointers to all GUI elements
guiData GUI_DATA;

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

    //setup material handler
    MaterialHandler matHandler_main;
    WORLD_DATA.matHandler = &matHandler_main;
    //setup object handler
    ObjectHandler objHandler_main;
    WORLD_DATA.objHandler = &objHandler_main;
    //setup creature handler

    //test
    send("LOAD_MATERIALS /Users/jayheiland/Projects/CPractice/data/mats.txt");
    WORLD_DATA.matHandler->printMaterials();
    send("LOAD_OBJECT_RULES /Users/jayheiland/Projects/CPractice/data/multiObjectRules.txt /Users/jayheiland/Projects/CPractice/data/elementalObjectRules.txt");
    WORLD_DATA.objHandler->createObject(475603);
    WORLD_DATA.objHandler->elementalObjGroup.printObjects();
    WORLD_DATA.objHandler->multiObjGroup.printObjects();

    //game loop
    while(!ENGINE_DATA.quitGame){
        processUserInputs();
        drawGraphics(&ENGINE_DATA, &WORLD_DATA);
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
