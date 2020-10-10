#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <unordered_map>
#include <iostream>

#include "world.h"
#include "general.h"
#include "creature_group.h"
#include "object_group.h"
#include "material_group.h"

#include "golden_plains.h"

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
}

void processModels(gameData *data){
    processCreatures(data);
}

void gameLoop(){
    gameData data;
    //setup GUI
    GraphicsLayer grph("./shaders/vert.spv", "./shaders/frag.spv");

    //test
    std::string filePath = "./data/";
    loadMaterials_Json(&data.matGroup, filePath + "materials.json");
    printMaterials(&data.matGroup);

    loadObjectRules_Json(&data.objRules, filePath + "elementalObjectRules.json");
    loadObjectRules_Json(&data.objRules, filePath + "humanBody_objectRules.json");
    loadComponentMaps(&data.componentMaps, filePath + "componentMaps.json");

    loadCreatureRules_Json(&data.crtRules, filePath + "creatureRules.json");
    loadFactions_Json(&data.fctGroup, filePath + "factions.json");

    ID testHuman1 = createCreature(&data, 100000, "Luneth", 228986);
    ID testHuman2 = createCreature(&data, 100000, "Ingus", 773941);
    printCreatures(&data.crtGroup);
    //printObjects(&data.objGroup);
    ID testEquipment = createObject(&data, 735631);
    linkObjects(&data, getBody(&data.crtGroup, testHuman1), _ADJOINS, testEquipment, false, 100);
    //printObjects(&data.objGroup);
    unlinkObjects(&data, getBody(&data.crtGroup, testHuman1), testEquipment);
    //printObjects(&data.objGroup);

    //equip weapon
    ID testWeapon = createObject(&data, 472680);
    std::vector<ID> grippers = getLinkedObjs(&data, data.crtGroup.at(testHuman2).body, _ANY, true, "gripper");
    linkObjects(&data, grippers[0], _ADJOINS, testWeapon, false, 100);

    setBattleTarget(&data.crtGroup, testHuman2, testHuman1);
    setBattleTarget(&data.crtGroup, testHuman1, testHuman2);

    //printObjsWithCode(&data, 325879);

    //game loop
    while(!grph.windowShouldClose()){
        processModels(&data);
        grph.draw();
    }

    grph.cleanup();
}

int main(int argc, char** args) {
    gameSetup();
    gameLoop();
    return 0;
}
