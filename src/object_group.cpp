#include "object_group.h"

MultiObjectGroup::MultiObjectGroup(){}

void ObjectHandler::loadRules(std::string multiObjRulesPath, std::string elemObjRulesPath){
    ElementalObjectRule elemRule;
    MultiObjectRule multiRule;
    objectCode objCode = 0;
    std::string line;
    int lineNum = 1;
    elemRule.maxContainerVolume = 0;
    std::ifstream infile;
    //read ElementalObject rules
    infile.open(elemObjRulesPath);
    if(!infile.is_open()){
        logError("Could not open elemental object rules file: '" + elemObjRulesPath + "'");
        return;
    }
    while (std::getline(infile, line)){
        if(line == "}"){
            if(objCode != 0){
                elemObjRules.insert(std::make_pair(objCode, elemRule));
                objCode = 0;
                elemRule.alternativeMaterials.clear();
            }
            else{
                logError("Could not process elemental object rules file: '" + elemObjRulesPath + "', at Line " + std::to_string(lineNum) + ". Parser object code is " + std::to_string(objCode));
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
                    elemRule.name = tokens[1];
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
                elemRule.alternativeMaterials.clear();
                elemRule.alternativeMaterials = mTags;
            }
            else if(tokens[0] == "length"){
                elemRule.length = std::stod(stripChar(tokens[1], ' '));
            }
            else if(tokens[0] == "width"){
                elemRule.width = std::stod(stripChar(tokens[1], ' '));
            }
            else if(tokens[0] == "height"){
                elemRule.height = std::stod(stripChar(tokens[1], ' '));
            }
            else if(tokens[0] == "maxContainerVolume"){
                elemRule.maxContainerVolume = std::stoi(stripChar(tokens[1], ' '));
            }
            else{
                logError("Could not process elemental object rules file: '" + elemObjRulesPath + "', at Line " + std::to_string(lineNum));
            }
        }
        else if(line == "{" || line == ""){
            
        }
        else{
            logError("Could not process elemental object rules file: '" + elemObjRulesPath + "', at Line " + std::to_string(lineNum));
            return;
        }
        lineNum++;
    }
    infile.close();
    lineNum=1;
    //read MultiObject rules
    multiRule.maxContainerVolume = 0;
    infile.open(multiObjRulesPath);
    if(!infile.is_open()){
        logError("Could not open multi object rules file: '" + multiObjRulesPath + "'");
        return;
    }
    while (std::getline(infile, line)){
        if(line == "}"){
            if(objCode != 0){
                multiObjRules.insert(std::make_pair(objCode, multiRule));
                objCode = 0;
                multiRule.requirements.clear();
                multiRule.name.clear();
                multiRule.equippableSites.clear();
                multiRule.maxContainerVolume=0;
            }
            else{
                logError("Could not process multi object rules file: '" + multiObjRulesPath + "', at Line " + std::to_string(lineNum));
            }
        }
        else if(line.size() > 1){
            std::vector<std::string> tokens;
            splitString(&tokens, line, ':');
            tokens[0] = stripChar(tokens[0], ' ');
            //parse name
            if(strContains(tokens[1], 2, '\'')){
                if(tokens[0] == "name"){
                    tokens[1] = stripCharAround(tokens[1], '\'');
                    multiRule.name = tokens[1];
                }
            }
            //parse object code
            else if(tokens[0] == "objectCode"){
                objCode = std::stoi(stripChar(tokens[1], ' '));
            }
            else if(tokens[0] == "components"){
                tokens[1] = stripChar(tokens[1], ' ');
                tokens[1] = stripChar(tokens[1], '(');
                tokens[1] = stripChar(tokens[1], ')');
                std::vector<std::string> objReqs;
                splitString(&objReqs, tokens[1], ',');
                for(std::string req : objReqs){
                    MultiObjectRuleReq multiRuleReq;
                    std::vector<std::string> objReqTokens;
                    splitString(&objReqTokens, req, '=');
                    multiRuleReq.objectCount = std::stoi(objReqTokens[1]);
                    std::vector<std::string> altReqs;
                    splitString(&altReqs, objReqTokens[0], '|');
                    for(std::string alt : altReqs){
                        multiRuleReq.alternativeObjects.push_back(std::stoi(alt));
                    }
                    multiRule.requirements.push_back(multiRuleReq);
                }
            }
            else if(tokens[0] == "maxContainerVolume"){
                multiRule.maxContainerVolume = std::stoi(stripChar(tokens[1], ' '));
            }
            else{
                logError("Could not process multi object rules file: '" + multiObjRulesPath + "', at Line " + std::to_string(lineNum));
            }
        }
        else if(line == "{" || line == ""){
            
        }
        else{
            logError("Could not process multi object rules file: '" + multiObjRulesPath + "', at Line " + std::to_string(lineNum));
            return;
        }
        lineNum++;
    }
    infile.close();
}

ID ObjectHandler::createObject(objectCode objCode){
    if(elemObjRules.find(objCode) != elemObjRules.end()){
        ElementalObject elemObj;
        ElementalObjectRule rule = elemObjRules[objCode];
        elemObj.name = rule.name;
        elemObj.objCode = objCode;
        elemObj.materialName = rule.alternativeMaterials[0];
        elemObj.length = rule.length;
        elemObj.width = rule.width;
        elemObj.height = rule.height;
        elemObj.maxContainerVolume = rule.maxContainerVolume;
        ID id = genID();
        elementalObjGroup.group.insert(std::make_pair(id, elemObj));
        return id;
    }
    else if(multiObjRules.find(objCode) != multiObjRules.end()){
        MultiObject multiObj;
        MultiObjectRule rule = multiObjRules[objCode];
        multiObj.name = rule.name;
        multiObj.objCode = objCode;
        for(MultiObjectRuleReq req : rule.requirements){
            for(int idx = 0; idx < req.objectCount; idx++){
                multiObj.components.push_back(createObject(req.alternativeObjects[0]));
            }
        }
        multiObj.maxContainerVolume = rule.maxContainerVolume;
        ID id = genID();
        multiObjGroup.group.insert(std::make_pair(id, multiObj));
        return id;
    }
    return 0;
}

void ObjectHandler::removeObject(ID id_){
    if(multiObjGroup.group.find(id_) != multiObjGroup.group.end()){
        for(ID compId : multiObjGroup.group[id_].components){
            removeObject(compId);
        }
        multiObjGroup.group.erase(id_);
    }
    else if(elementalObjGroup.group.find(id_) != elementalObjGroup.group.end()){
        elementalObjGroup.group.erase(id_);
    }
}

void MultiObjectGroup::loadObjects(std::string path){

}

void MultiObjectGroup::printObjects(){
    for(std::pair<ID, MultiObject> obj : group){
        obj.second.printObject();
    }
}

ElementalObjectGroup::ElementalObjectGroup(){}

void ElementalObjectGroup::printObjects(){
    for(std::pair<ID, ElementalObject> obj : group){
        obj.second.printObject();
    }
}