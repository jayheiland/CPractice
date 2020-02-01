#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "world.h"
#include "general.h"

void gameLoop(){
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

int main(int argc, char** args) {
    gameLoop();

    return 0;
}
