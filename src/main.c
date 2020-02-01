#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <SDL2/SDL.h>

#include "world.h"
#include "general.h"
#include "message.h"

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

void gameSetup(){
    ENGINE_DATA.quitGame = 0;
    setupGraphics(&ENGINE_DATA);
}

void gameLoop(){
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
    gameLoop();
    gameShutdown();

    return 0;
}
