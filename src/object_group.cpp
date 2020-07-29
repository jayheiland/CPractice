#include "object_group.h"

void loadObjectRules_Json(std::unordered_map<objectCode, ObjectRule> *objRules, std::string objRulesPath){
    JsonObject *rulesFromFile = parseJsonFile(objRulesPath);
    for(auto rule : rulesFromFile->getJsonArray("objectRules").getJsonObjectArray()){
        ObjectRule newRule;
        objectCode objCode = 0;
        newRule.maxContainerVolume = 0;
        newRule.length=0;
        newRule.height=0;
        newRule.width=0;

        newRule.name = rule->getString("name");
        objCode = rule->getDouble("objectCode");
        if(rule->getJsonArray("materialTags").size() > 0){
            newRule.alternativeMaterials = rule->getJsonArray("materialTags").getStringArray();
        }
        for(auto cmpRule : rule->getJsonArray("components").getJsonObjectArray()){
            ObjectRuleComponentReq multiRuleCmpReq;
            multiRuleCmpReq.count = (int)cmpRule->getDouble("count");
            for(auto alt : cmpRule->getJsonArray("alternativeComponents").getDoubleArray()){
                multiRuleCmpReq.alternativeComponents.push_back((objectCode)alt);
            }
            newRule.components.push_back(multiRuleCmpReq);
        }
        for(auto site : rule->getJsonArray("equippableSites").getDoubleArray()){
            newRule.equippableSites.push_back((objectCode)site);
        }
        if(rule->getDouble("length") != -1.0){
            newRule.length = rule->getDouble("length");
            newRule.width = rule->getDouble("width");
            newRule.height = rule->getDouble("height");
        }
        if(rule->getDouble("maxContainerVolume") != -1.0){
            newRule.maxContainerVolume = rule->getDouble("maxContainerVolume");
        }

        objRules->insert(std::make_pair(objCode, newRule));
    }
}

void loadObjectRules(std::unordered_map<objectCode, ObjectRule> *objRules, std::string objRulesPath){
    ObjectRule newRule;
    objectCode objCode = 0;
    std::string line;
    int lineNum = 1;
    newRule.maxContainerVolume = 0;
    newRule.length=0;
    newRule.height=0;
    newRule.width=0;
    std::ifstream infile;
    //read ElementalObject rules
    infile.open(objRulesPath);
    if(!infile.is_open()){
        logError("Could not open elemental object rules file: '" + objRulesPath + "'");
        return;
    }
    while (std::getline(infile, line)){
        if(line == "}"){
            if(objCode != 0){
                objRules->insert(std::make_pair(objCode, newRule));
                objCode = 0;
                newRule.components.clear();
                newRule.name.clear();
                newRule.equippableSites.clear();
                newRule.maxContainerVolume=0;
                newRule.length=0;
                newRule.height=0;
                newRule.width=0;
            }
            else{
                logError("Could not process object rules file: '" + objRulesPath + "', at Line " + std::to_string(lineNum) + ". Parser object code is " + std::to_string(objCode));
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
                    newRule.name = tokens[1];
                }
            }
            //parse object code
            else if(tokens[0] == "objectCode"){
                objCode = std::stoi(stripChar(tokens[1], ' '));
            }
            //parse material tags
            else if(tokens[0] == "materialTags"){
                tokens[1] = stripChar(tokens[1], ' ');
                std::vector<std::string> mTags;
                splitString(&mTags, tokens[1], ',');
                newRule.alternativeMaterials.clear();
                newRule.alternativeMaterials = mTags;
            }
            else if(tokens[0] == "components"){
                tokens[1] = stripChar(tokens[1], ' ');
                tokens[1] = stripChar(tokens[1], '(');
                tokens[1] = stripChar(tokens[1], ')');
                std::vector<std::string> objReqs;
                splitString(&objReqs, tokens[1], ',');
                for(std::string req : objReqs){
                    ObjectRuleComponentReq multiRuleReq;
                    std::vector<std::string> objReqTokens;
                    splitString(&objReqTokens, req, '=');
                    multiRuleReq.count = std::stoi(objReqTokens[1]);
                    std::vector<std::string> altReqs;
                    splitString(&altReqs, objReqTokens[0], '|');
                    for(std::string alt : altReqs){
                        multiRuleReq.alternativeComponents.push_back(std::stoi(alt));
                    }
                    newRule.components.push_back(multiRuleReq);
                }
            }
            else if(tokens[0] == "equippableSites"){
                tokens[1] = stripChar(tokens[1], ' ');
                std::vector<std::string> eqSites;
                splitString(&eqSites, tokens[1], ',');
                for(std::string site : eqSites){
                    newRule.equippableSites.push_back(std::stoi(site));
                }
            }
            else if(tokens[0] == "length"){
                newRule.length = std::stod(stripChar(tokens[1], ' '));
            }
            else if(tokens[0] == "width"){
                newRule.width = std::stod(stripChar(tokens[1], ' '));
            }
            else if(tokens[0] == "height"){
                newRule.height = std::stod(stripChar(tokens[1], ' '));
            }
            else if(tokens[0] == "maxContainerVolume"){
                newRule.maxContainerVolume = std::stoi(stripChar(tokens[1], ' '));
            }
            else{
                logError("Could not process elemental object rules file: '" + objRulesPath + "', at Line " + std::to_string(lineNum));
            }
        }
        else if(line == "{" || line == ""){
            
        }
        else{
            logError("Could not process elemental object rules file: '" + objRulesPath + "', at Line " + std::to_string(lineNum));
            return;
        }
        lineNum++;
    }
    infile.close();
}

ID createObject(gameData *data, objectCode objCode){
    if(data->objRules.find(objCode) != data->objRules.end()){
        Object newObj;
        ObjectRule rule = data->objRules[objCode];
        newObj.name = rule.name;
        newObj.objCode = objCode;
        for(ObjectRuleComponentReq req : rule.components){
            for(int idx = 0; idx < req.count; idx++){
                newObj.components.push_back(createObject(data, req.alternativeComponents[0]));
            }
        }
        newObj.materialName = getMaterialWithTag(&data->matGroup, rule.alternativeMaterials[0]);
        newObj.length = rule.length;
        newObj.width = rule.width;
        newObj.height = rule.height;
        newObj.maxContainerVolume = rule.maxContainerVolume;
        newObj.integrity = (newObj.length * newObj.width * newObj.height) * data->matGroup.at(newObj.materialName).density * 4.0;
        ID id = genID();
        data->objGroup.insert(std::make_pair(id, newObj));
        return id;
    }
    return 0;
}

void removeObject(std::unordered_map<ID, Object> *objGroup, ID id_){
    if(objGroup->find(id_) != objGroup->end()){
        for(ID compId : objGroup->at(id_).components){
            removeObject(objGroup, compId);
        }
        objGroup->erase(id_);
    }
}

void equipObject(gameData *data, ID equipper, ID equipment){
    for(auto itr = data->objRules.at(data->objGroup.at(equipment).objCode).equippableSites.begin(); itr < data->objRules.at(data->objGroup.at(equipment).objCode).equippableSites.end(); itr++){
        if(*itr == data->objGroup.at(equipper).objCode){
            data->objGroup.at(equipper).equippedObjects.push_back(equipment);
            data->objGroup.at(equipment).equippedSites.push_back(equipper);
        }
    }
}

void unequipObject(std::unordered_map<ID, Object> *objGroup, ID equipper, ID equipment){
    for(auto itr = objGroup->at(equipper).equippedObjects.begin(); itr < objGroup->at(equipper).equippedObjects.end(); itr++){
        if(*itr == equipment){
            objGroup->at(equipper).equippedObjects.erase(itr);
        }
    }
    for(auto itr = objGroup->at(equipment).equippedSites.begin(); itr < objGroup->at(equipment).equippedSites.end(); itr++){
        if(*itr == equipper){
            objGroup->at(equipment).equippedSites.erase(itr);
        }
    }
}

void printObjects(std::unordered_map<ID, Object> *objGroup){
    std::cout << "------------------------------Loaded Objects----------------------------------" << std::endl;
    for(std::pair<ID, Object> obj : *objGroup){
        printObject(objGroup, &obj.second);
    }
}

ID getWeapon(std::unordered_map<ID, Object> *objGroup, ID body){
    for(auto& cmp : objGroup->at(body).components){
        if(objGroup->at(cmp).materialName == "metal"){
            return cmp;
        }
        getWeapon(objGroup, cmp);
    }
    return NULL_ID;
}

void attackObject(gameData *data, ID weapon, ID subject){
    if(subject != NULL_ID){
        data->objGroup.at(subject).integrity -= getMass(data, weapon);
        if(data->objGroup.at(subject).integrity <= 0){
            data->objGroup.at(subject).integrity = 0;
        }
        std::cout << data->objGroup.at(weapon).name << " dealt " << getMass(data, weapon) << " damage to " 
            << data->objGroup.at(subject).name << ", reducing its integrity to " << data->objGroup.at(subject).integrity << "\n";
    }
}

double getMass(gameData *data, ID subject){
    Object obj = data->objGroup.at(subject);
    return obj.length * obj.width * obj.height * data->matGroup.at(obj.materialName).density;
}