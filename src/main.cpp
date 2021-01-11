#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <unordered_map>
#include <iostream>

#include "material_group.h"
#include "objectm.h"
#include "creaturem.h"
#include "worldm.h"
#include "graphics.h"
#include "battle.h"

//engine settings; hardcoded for now, to be loaded from a file later
engineData ENGINE_DATA;
ID masterIDCounter;

void createWorld(gameData *dt){
    dt->loadedChunk = loadChunk(dt, "./data/arena.json", "./data/nodeInfo.json");
    // Vec3 test = {0,0,2};
    // Vec3 testDest = {dt->loadedChunk.size.x-1, dt->loadedChunk.size.y-1, 2};
    // Vec3 *path;
    // int pathLen;
    // std::vector<std::string> mobility = {"flier"};
    // path = worldPath(dt, &test, &testDest, &pathLen, mobility);
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
    data.grph = &grph;
    graphicsSetup(&data);
    

    //test creature interaction
    
    std::string filePath = "./data/";
    loadMaterials_Json(&data.matGroup, filePath + "materials.json");
    printMaterials(&data.matGroup);

    loadObjectRules_Json(&data.objRules, filePath + "elementalObjectRules.json");
    loadObjectRules_Json(&data.objRules, filePath + "humanBody_objectRules.json");
    loadComponentMaps(&data.componentMaps, filePath + "componentMaps.json");

    loadCreatureRules_Json(&data, filePath + "creatureRules.json");
    loadFactions_Json(&data.fctGroup, filePath + "factions.json");

    Vec3 pos1;
    pos1.x = 5;
    pos1.y = 5;
    pos1.z = 1;
    ID testHuman1 = createCreature(&data, 100000, true, "Luneth", 916422, pos1);
    data.selectedPC = testHuman1;
    Creature selectedPC = data.crtGroup.at(data.selectedPC);
    //data.grph->createTextBox(selectedPC.name, 0, 0, 0, 0);

    Vec3 pos2;
    pos2.x = 7,
    pos2.y = 4;
    pos2.z = 1;
    ID testHuman2 = createCreature(&data, 100000, false, "Ingus", 773941, pos2);
    data.selectedNPC = testHuman2;

    Vec3 pos3;
    pos3.x = 4;
    pos3.y = 2;
    pos3.z = 1;
    ID testHuman3 = createCreature(&data, 100000, false, "Refia", 773941, pos3);

    printCreatures(&data.crtGroup);
    //printObjects(&data.objGroup);
    ID testEquipment = createObject(&data, 735631);
    linkObjects(&data, ac(&data, testHuman1)->body, ADJOINS, testEquipment, false, 100);
    //printObjects(&data.objGroup);
    unlinkObjects(&data, ac(&data, testHuman1)->body, testEquipment);
    //printObjects(&data.objGroup);

    //equip weapons
    ID testWeapon = createObject(&data, 472680);
    std::vector<ID> grippers = getLinkedObjs(&data, data.crtGroup.at(testHuman2).body, ANY, FUNCTIONAL, "gripper", false);
    linkObjects(&data, grippers[0], ADJOINS, testWeapon, false, 100);

    ID testWeapon2 = createObject(&data, 472680);
    std::vector<ID> grippers2 = getLinkedObjs(&data, data.crtGroup.at(testHuman1).body, ANY, FUNCTIONAL, "gripper", false);
    linkObjects(&data, grippers2[0], ADJOINS, testWeapon2, false, 100);

    ID testWeapon3 = createObject(&data, 472680);
    std::vector<ID> grippers3 = getLinkedObjs(&data, data.crtGroup.at(testHuman3).body, ANY, FUNCTIONAL, "gripper", false);
    linkObjects(&data, grippers3[0], ADJOINS, testWeapon3, false, 100);

    startBattle(&data);

    //test world loading
    createWorld(&data);

    //test creature sprite loading
    // TextureID guyTxtr = grph.createTexture("./textures/prongle.png");
    // grph.createModel("./models/cartwright_sprite.obj", guyTxtr, glm::vec3(5,5,3));
    
    //game loop
    while(!grph.windowShouldClose()){
        processModels(&data);
        graphicsDraw(&grph);
    }

    //memory cleanup
    deleteChunk(&data.loadedChunk);
    grph.cleanup();
}

int main(int argc, char** args) {
    gameSetup();
    gameLoop();
    return 0;
}
