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
    std::vector<ID> brainParts = getLinkedObjs(dt, whateverPart, _ANY, FUNCTIONAL, "thought center", false);
    crt.body = brainParts[0];
    crt.battleTarget = 0;
    crt.loc.chunk = dt->loadedChunk.chunkLoc;
    crt.loc.loc = pos;
    dt->grph->createModel("./models/cartwright_sprite.obj", dt->crtTextures.at(dt->crtRules.at(crtCode).textureName), glm::vec3(pos.x, pos.y, pos.z+1));
    ID id = genID();
    dt->crtGroup[id] = crt;
    return id;
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