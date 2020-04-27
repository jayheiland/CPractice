#include "creature_group.h"

extern std::unordered_map<creatureCode, CreatureRule> crtRules;

void loadCreatureRules(std::string path){
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
                crtRules.insert(std::make_pair(crtCode, crtRule));
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

void addCreature(std::unordered_map<ID, Creature> *crtGroup, std::unordered_map<ID, Object> *objGroup, creatureCode crtCode, std::string name){
    Creature crt;
    crt.name = name;
    crt.speciesName = crtRules[crtCode].speciesName;
    crt.body = createObject(objGroup, crtRules[crtCode].bodyCode);
    ID id = genID();
    crtGroup->insert(std::make_pair(id, crt));
}