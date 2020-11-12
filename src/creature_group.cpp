#include "creature_group.h"

void loadCreatureRules_Json(std::unordered_map<creatureCode, CreatureRule> *crtRules, std::string path){
    CreatureRule crtRule;
    JsonObject *rulesFromFile = parseJsonFile(path);
    for(auto rule : rulesFromFile->getJsonArray("creatureRules").getJsonObjectArray()){
        crtRule.speciesName = rule->getString("speciesName");
        crtRule.bodyMapName = rule->getString("bodyMapName");
        crtRules->insert(std::make_pair((creatureCode)rule->getDouble("creatureCode"), crtRule));
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

ID createCreature(gameData *dt, creatureCode crtCode, bool isPlayerCharacter, std::string name, factionCode fctCode){
    Creature crt;
    crt.name = name;
    crt.crtCode = crtCode;
    crt.fctCode = fctCode;
    crt.isPC = isPlayerCharacter;
    ID whateverPart =  createObjectsFromComponentMap(dt, dt->crtRules.at(crtCode).bodyMapName);
    std::vector<ID> brainParts = getLinkedObjs(dt, whateverPart, _ANY, FUNCTIONAL, "thought center", false);
    crt.body = brainParts[0];
    crt.battleTarget = 0;
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