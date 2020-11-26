#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <unordered_map>
#include <iostream>

#include "general.h"
#include "creature_group.h"
#include "object_group.h"
#include "material_group.h"
#include "battle_handler.h"
#include "graphics.h"

//engine settings; hardcoded for now, to be loaded from a file later
engineData ENGINE_DATA;
ID masterIDCounter;

void createWorld(gameData *dt){
    dt->loadedChunk.size = {10,10,1};
    dt->loadedChunk.nodes = newWorld(&dt->loadedChunk.size, dt->grph);
    // Vec3 test = {0,0,0};
    // Vec3 testDest = {worldSize.x-1,worldSize.y-1,worldSize.z-1};
    // Vec3 *path;
    // int pathLen;
    // path = worldPath(world, &worldSize, &test, &testDest, &pathLen);
    // printPath(path, pathLen);
    // free(path);
    
}

void gameSetup(){
    srand(88393401);
    masterIDCounter = 1;
}

void processModels(gameData *dt){
    processBattle(dt);
}

void gameLoop(){
    gameData data;

    //setup GUI
    GraphicsLayer grph("./shaders/vert.spv", "./shaders/frag.spv");
    graphicsSetup(&grph);
    data.grph = &grph;

    //test creature interaction
    
    std::string filePath = "./data/";
    loadMaterials_Json(&data.matGroup, filePath + "materials.json");
    printMaterials(&data.matGroup);

    loadObjectRules_Json(&data.objRules, filePath + "elementalObjectRules.json");
    loadObjectRules_Json(&data.objRules, filePath + "humanBody_objectRules.json");
    loadComponentMaps(&data.componentMaps, filePath + "componentMaps.json");

    loadCreatureRules_Json(&data.crtRules, filePath + "creatureRules.json");
    loadFactions_Json(&data.fctGroup, filePath + "factions.json");

    ID testHuman1 = createCreature(&data, 100000, true, "Luneth", 916422);
    data.selectedPC = testHuman1;
    Creature selectedPC = data.crtGroup.at(data.selectedPC);
    //data.grph->createTextBox(selectedPC.name, 0, 0, 0, 0);

    ID testHuman2 = createCreature(&data, 100000, false, "Ingus", 773941);
    data.selectedNPC = testHuman2;
    printCreatures(&data.crtGroup);
    //printObjects(&data.objGroup);
    ID testEquipment = createObject(&data, 735631);
    linkObjects(&data, getBody(&data.crtGroup, testHuman1), _ADJOINS, testEquipment, false, 100);
    //printObjects(&data.objGroup);
    unlinkObjects(&data, getBody(&data.crtGroup, testHuman1), testEquipment);
    //printObjects(&data.objGroup);

    //equip weapons
    ID testWeapon = createObject(&data, 472680);
    std::vector<ID> grippers = getLinkedObjs(&data, data.crtGroup.at(testHuman2).body, _ANY, FUNCTIONAL, "gripper", false);
    linkObjects(&data, grippers[0], _ADJOINS, testWeapon, false, 100);

    ID testWeapon2 = createObject(&data, 472680);
    std::vector<ID> grippers2 = getLinkedObjs(&data, data.crtGroup.at(testHuman1).body, _ANY, FUNCTIONAL, "gripper", false);
    linkObjects(&data, grippers2[0], _ADJOINS, testWeapon2, false, 100);

    startBattle(&data);

    //test world loading
    createWorld(&data);
    
    //game loop
    while(!grph.windowShouldClose()){
        processModels(&data);
        graphicsDraw(&grph);
    }

    deleteChunk(&data.loadedChunk);

    grph.cleanup();
}

int main(int argc, char** args) {
    gameSetup();
    gameLoop();
    return 0;
}
