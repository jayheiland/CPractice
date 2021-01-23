#include "creaturem.h"

void loadCreatureRules_Json(gameData *dt, std::string path){
    CreatureRule crtRule;
    JsonObject *rulesFromFile = parseJsonFile(path);
    for(auto rule : rulesFromFile->getJsonArray("creatureRules").getJsonObjectArray()){
        crtRule.speciesName = rule->getString("speciesName");
        crtRule.bodyMapName = rule->getString("bodyMapName");
        crtRule.textureName = rule->getString("textureName");
        dt->crtRules.insert(std::make_pair((creatureCode)rule->getDouble("creatureCode"), crtRule));
    }
    for(auto txtr : rulesFromFile->getJsonArray("textures").getJsonArrayArray()){
        dt->crtTextures.insert(std::make_pair(txtr->getStringArray()[0], dt->grph->createTexture(txtr->getStringArray()[1])));
    }
}

void loadFactions_Json(std::unordered_map<factionCode, Faction> *fctGroup, std::string path){
    Faction newFaction;
    JsonObject *factionsFromFile = parseJsonFile(path);
    for(auto fct : factionsFromFile->getJsonArray("factions").getJsonObjectArray()){
        newFaction.name = fct->getString("name");
        for(double enemyFactionCode : fct->getJsonArray("enemies").getDoubleArray()){
            newFaction.enemies.push_back((factionCode)enemyFactionCode);
        }
        fctGroup->insert(std::make_pair((factionCode)fct->getDouble("factionCode"), newFaction));
    }
    for(auto loadedFct : *fctGroup){
        std::cout << "Faction '" << loadedFct.second.name << "' is currently loaded" << std::endl;
    }
}

//ac = 'access creature'
Creature *ac(gameData *dt, ID id){
    return &dt->crtGroup.at(id);
}

ID createCreature(gameData *dt, creatureCode crtCode, bool isPlayerCharacter, std::string name, factionCode fctCode, Vec3 pos){
    Creature crt;
    crt.name = name;
    crt.crtCode = crtCode;
    crt.fctCode = fctCode;
    crt.isPC = isPlayerCharacter;
    ID whateverPart =  createObjectsFromComponentMap(dt, dt->crtRules.at(crtCode).bodyMapName);
    std::vector<ID> brainParts = getLinkedObjs(dt, whateverPart, ANY, FUNCTIONAL, "thought center", false);
    crt.body = brainParts[0];
    crt.battleTarget = 0;
    crt.loc.chunk = dt->loadedChunk.chunkLoc;
    crt.loc.loc = pos;
    crt.model = dt->grph->createModel("./models/cartwright_sprite.obj", dt->crtTextures.at(dt->crtRules.at(crtCode).textureName), glm::vec3(pos.x, pos.y, pos.z));
    //attributes
    crt.att_agi = 4;
    //attributes, end
    ID id = genID();
    dt->crtGroup[id] = crt;
    dt->boundingBoxToCreature.insert(std::make_pair(dt->grph->createBoundingBox(glm::vec3(pos.x-0.5, pos.y-0.5, pos.z-0.5), glm::vec3(pos.x+0.5, pos.y+0.5, pos.z+1.5)), id));
    return id;
}

std::vector<std::string> getMobilityTags(gameData *dt, ID crt){
    std::vector<std::string> result;
    if(getLinkedObjs(dt, ac(dt, crt)->body, ANY, FUNCTIONAL, "ambulator", false).size() > 0){
        result.push_back("ambulator");
    }
    if(getLinkedObjs(dt, ac(dt, crt)->body, ANY, FUNCTIONAL, "swimmer", false).size() > 0){
        result.push_back("swimmer");
    }
    if(getLinkedObjs(dt, ac(dt, crt)->body, ANY, FUNCTIONAL, "flier", false).size() > 0){
        result.push_back("flier");
    }
    return result;
}

void moveToLocation(gameData *dt, ID creature, GraphObjID boundingBox, WorldLoc loc){
    auto crtPtr = ac(dt, creature);
    auto path = worldPath(dt, &crtPtr->loc.loc, &loc.loc, (double)crtPtr->att_agi, getMobilityTags(dt, creature));
    if(path.size() > 0){
        for(int idx = path.size()-1; idx >= 0; idx--){
            Vec3 newLoc = path[idx].loc;
            dt->crtGroup.at(creature).loc.loc = newLoc;
            dt->grph->setModelPosition(crtPtr->model, glm::vec3(newLoc.x, newLoc.y, newLoc.z));
            dt->grph->setBoundingBoxBounds(boundingBox, glm::vec3(newLoc.x-0.5, newLoc.y-0.5, newLoc.z-0.5), glm::vec3(newLoc.x+0.5, newLoc.y+0.5, newLoc.z+1.5));
        }
    }
}

void printCreatures(std::unordered_map<ID, Creature> *crtGroup){
    std::cout << "-------------------------------Loaded Creatures----------------------------------" << std::endl;
    for(std::pair<ID, Creature> obj : *crtGroup){
        printCreature(&obj.second);
    }
}

void setBattleTarget(std::unordered_map<ID, Creature> *crtGroup, ID aggressor, ID subject){
    crtGroup->at(aggressor).battleTarget = subject;
}