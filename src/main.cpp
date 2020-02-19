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

//engine settings; hardcoded for now, to be loaded from a file later
engineData ENGINE_DATA;

//global pointers to game data; only the "send" function is allowed to use this
worldData WORLD_DATA;

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
    srand((unsigned int)time(NULL));
    ENGINE_DATA.quitGame = 0;
    setupGraphics(&ENGINE_DATA);
}

void gameLoop(){
    //setup creature groups
    creatureGroup pCrts;
    creatureGroup oCrts;
    WORLD_DATA.playerCrts = &pCrts;
    WORLD_DATA.otherCrts = &oCrts;
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
