#include "creature_group.h"

void loadCreatureRules(std::unordered_map<creatureCode, CreatureRule> *crtRules, std::string path){
    CreatureRule crtRule;
    creatureCode crtCode = 0;
    std::string line;
    int lineNum = 1;
    std::ifstream infile;
    //read creature rules
    infile.open(path);
    if(!infile.is_open()){
        logError("Could not open creature rules file: '" + path + "'");
        return;
    }
    while (std::getline(infile, line)){
        if(line == "}"){
            if(crtCode != 0){
                crtRules->insert(std::make_pair(crtCode, crtRule));
                crtCode = 0;
            }
            else{
                logError("Could not process creature rules file: '" + path + "', at Line " + std::to_string(lineNum) + ". Parser creature code is " + std::to_string(crtCode));
            }
        }
        else if(line.size() > 1){
            std::vector<std::string> tokens;
            splitString(&tokens, line, ':');
            //parse string arg
            tokens[0] = stripChar(tokens[0], ' ');
            if(strContains(tokens[1], 2, '\'')){
                if(tokens[0] == "speciesName"){
                    tokens[1] = stripCharAround(tokens[1], '\'');
                    crtRule.speciesName = tokens[1];
                }
            }
            //parse creature code
            else if(tokens[0] == "creatureCode"){
                crtCode = std::stol(stripChar(tokens[1], ' '));
            }
            //parse body object code
            else if(tokens[0] == "body"){
                crtRule.bodyCode = std::stoi(stripChar(tokens[1], ' '));
            }
            else{
                logError("Could not process creature rules file: '" + path + "', at Line " + std::to_string(lineNum));
            }
        }
        else if(line == "{" || line == ""){
            
        }
        else{
            logError("Could not process creature rules file: '" + path + "', at Line " + std::to_string(lineNum));
            return;
        }
        lineNum++;
    }
    infile.close();
}

void loadFactions(std::unordered_map<factionCode, Faction> *fctGroup, std::string path){
    Faction faction;
    factionCode fctCode = 0;
    std::string line;
    int lineNum = 1;
    std::ifstream infile;
    //read creature rules
    infile.open(path);
    if(!infile.is_open()){
        logError("Could not open creature rules file: '" + path + "'");
        return;
    }
    while (std::getline(infile, line)){
        if(line == "}"){
            if(fctCode != 0){
                fctGroup->insert(std::make_pair(fctCode, faction));
                fctCode = 0;
            }
            else{
                logError("Could not process creature rules file: '" + path + "', at Line " + std::to_string(lineNum) + ". Parser creature code is " + std::to_string(fctCode));
            }
        }
        else if(line.size() > 1){
            std::vector<std::string> tokens;
            splitString(&tokens, line, ':');
            //parse string arg
            tokens[0] = stripChar(tokens[0], ' ');
            if(strContains(tokens[1], 2, '\'')){
                if(tokens[0] == "name"){
                    tokens[1] = stripCharAround(tokens[1], '\'');
                    faction.name = tokens[1];
                }
            }
            //parse creature code
            else if(tokens[0] == "factionCode"){
                fctCode = std::stol(stripChar(tokens[1], ' '));
            }
            //parse body object code
            else if(tokens[0] == "enemies"){
                std::vector<std::string> enemyCodes;
                splitString(&enemyCodes, tokens[1], ',');
                for(std::string code : enemyCodes){
                    faction.enemies.push_back(std::stoi(stripChar(code, ' ')));
                }
            }
            else{
                logError("Could not process factions file: '" + path + "', at Line " + std::to_string(lineNum));
            }
        }
        else if(line == "{" || line == ""){
            
        }
        else{
            logError("Could not process factions file: '" + path + "', at Line " + std::to_string(lineNum));
            return;
        }
        lineNum++;
    }
    infile.close();
}

ID createCreature(gameData *data, creatureCode crtCode, std::string name, factionCode fctCode){
    Creature crt;
    crt.name = name;
    crt.fctCode = fctCode;
    crt.speciesName = data->crtRules[crtCode].speciesName;
    crt.body = createObject(data, data->crtRules[crtCode].bodyCode);
    ID id = genID();
    data->crtGroup.insert(std::make_pair(id, crt));
    return id;
}

void printCreatures(std::unordered_map<ID, Creature> *crtGroup){
    std::cout << "-------------------------------Loaded Creatures----------------------------------" << std::endl;
    for(std::pair<ID, Creature> obj : *crtGroup){
        printCreature(&obj.second);
    }
}

void processCreatures(gameData *data){
    for(auto& crt : data->crtGroup){

    }
}