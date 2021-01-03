#pragma once

#include <unordered_map>
#include <vector>
#include <fstream>
#include <queue>

#include "golden_plains.h"
#include "general.h"
#include "object.h"
#include "creature.h"

struct engineData {
    char debugConsoleStr[1024];
    int defaultGuiBkgColor[4];
    int windowWidth, windowHeight;
    int debugMode;
};

struct GUI_StackSelector{
    bool visible;
    ID selectedObject;
    std::vector<std::pair<ID, GraphObjID> > selectorButtons;
};

struct gameData{
    //data models
    std::unordered_map<ID, Object> objGroup;
    std::unordered_map<objectCode, ObjectRule> objRules;
    std::unordered_map<std::string, ComponentMap> componentMaps;
    std::unordered_map<ID, Creature> crtGroup;
    std::unordered_map<creatureCode, CreatureRule> crtRules;
    std::unordered_map<factionCode, Faction> fctGroup;
    std::unordered_map<std::string, Material> matGroup;

    //world chunks
    WorldChunk loadedChunk;
    std::unordered_map<GraphObjID, worldLoc> boundingBoxToLocation;

    //creature textures
    std::unordered_map<std::string, TextureID> crtTextures;

    //overhead / management / battle
    ID selectedPC;
    ID selectedNPC;
    bool inBattle;
    std::queue<ID> turnQueue;
    std::unordered_map<GraphObjID, ID> boundingBoxToCreature;

    //graphics data
    GraphicsLayer *grph;

        //GUI elements
        GUI_StackSelector weaponSelector;
        GUI_StackSelector targetSelector;
};