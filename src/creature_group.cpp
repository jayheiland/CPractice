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

Creature *ac(gameData *dt, ID crt){
    return &dt->crtGroup.at(crt);
}

ID createCreature(gameData *dt, creatureCode crtCode, std::string name, factionCode fctCode){
    Creature crt;
    crt.name = name;
    crt.crtCode = crtCode;
    crt.fctCode = fctCode;
    ID whateverPart =  createObjectsFromComponentMap(dt, dt->crtRules.at(crtCode).bodyMapName);
    std::vector<ID> brainParts = getLinkedObjs(dt, whateverPart, _ANY, true, "thought center");
    crt.body = brainParts[0];
    crt.battleTarget = 0;
    ID id = genID();
    dt->crtGroup.insert(std::make_pair(id, crt));
    return id;
}

void printCreatures(std::unordered_map<ID, Creature> *crtGroup){
    std::cout << "-------------------------------Loaded Creatures----------------------------------" << std::endl;
    for(std::pair<ID, Creature> obj : *crtGroup){
        printCreature(&obj.second);
    }
}

void processCreatures(gameData *dt){
    determineBattleTargets(dt);
    processBattles(dt);
}

void determineBattleTargets(gameData *dt){
    // for(auto& crt : dt->crtGroup){
    //     for(auto& other : dt->crtGroup){
    //         auto crtEnemies = dt->fctGroup.at(crt.second.fctCode).enemies;
    //         if(crt.first != other.first && find(crtEnemies.begin(), crtEnemies.end(), other.second.fctCode)!=crtEnemies.end()){
    //             setBattleTarget(&dt->crtGroup, crt.first, other.first);
    //             return;
    //         }
    //     }
    // }
}

void processBattles(gameData *dt){
    for(auto& crt : dt->crtGroup){
        //test: get any body part to attack
        ID targetPart = getLinkedObjs(dt, dt->crtGroup.at(crt.second.battleTarget).body, _ANY, true, "")[0];
        attackObject(dt, getPhysWeapons(dt, crt.second.body)[0], targetPart);
    }
}

void setBattleTarget(std::unordered_map<ID, Creature> *crtGroup, ID aggressor, ID subject){
    crtGroup->at(aggressor).battleTarget = subject;
}