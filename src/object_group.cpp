#include "object_group.h"

void loadObjectRules_Json(std::unordered_map<objectCode, ObjectRule> *objRules, std::string objRulesPath){
    JsonObject *rulesFromFile = parseJsonFile(objRulesPath);
    for(auto rule : rulesFromFile->getJsonArray("objectRules").getJsonObjectArray()){
        ObjectRule newRule;
        objectCode objCode = 0;
        newRule.defaultLength=0;
        newRule.defaultHeight=0;
        newRule.defaultWidth=0;

        newRule.name = rule->getString("name");
        objCode = rule->getDouble("objectCode");
        for(auto mat : rule->getJsonArray("materialTags").getStringArray()){
            newRule.materialTags.push_back(mat);
        }
        if(rule->getJsonArray("usageTags").size() > 0){
            newRule.usageTags = rule->getJsonArray("usageTags").getStringArray();
        }
        if(rule->getDouble("length") != -1.0){
            newRule.defaultLength = rule->getDouble("length");
            newRule.defaultWidth = rule->getDouble("width");
            newRule.defaultHeight = rule->getDouble("height");
        }

        objRules->insert(std::make_pair(objCode, newRule));
    }
}

void loadComponentMaps(std::unordered_map<std::string, ComponentMap> *componentMaps, std::string cmpMapsPath){
    JsonObject *mapsFromFile = parseJsonFile(cmpMapsPath);
    for(auto map : mapsFromFile->getJsonArray("componentMaps").getJsonObjectArray()){
        ComponentMap newMap;
        for(auto node : map->getJsonArray("map").getJsonObjectArray()){
            CmpMapNode newNode;
            for(auto altCmp : node->getJsonArray("alternativeComponents").getDoubleArray()){
                newNode.alternativeComponents.push_back(altCmp);
            }
            for(auto mapLink : node->getJsonArray("objectLinks").getJsonObjectArray()){
                CmpMapLink newObjLink;
                if(mapLink->getString("objLinkType") == "adjoins"){
                    newObjLink.type = _ADJOINS;
                }
                else if(mapLink->getString("objLinkType") == "wraps"){
                    newObjLink.type = _WRAPS;
                }
                else if(mapLink->getString("objLinkType") == "wrapped by"){
                    newObjLink.type = _WRAPPED_BY;
                }
                newObjLink.isFunctional = true;
                newObjLink.strength = mapLink->getDouble("strength");
                newObjLink.subject = mapLink->getString("subject");

                newNode.linkedObjects.push_back(newObjLink);
            }
            newMap.map.insert(std::make_pair(node->getString("name"), newNode));
        }
        componentMaps->insert(std::make_pair(map->getString("name"), newMap));
    }
}

ID createObject(gameData *dt, objectCode objCode){
    Object newObj;
    ObjectRule rule = dt->objRules.at(objCode);
    newObj.name = rule.name;
    newObj.objCode = objCode;
    newObj.length = rule.defaultLength;
    newObj.width = rule.defaultWidth;
    newObj.height = rule.defaultHeight;
    newObj.materialName = dt->objRules.at(objCode).materialTags[0];
    newObj.materialName = getMaterialWithTag(&dt->matGroup, dt->objRules.at(objCode).materialTags[0]);
    newObj.integrity = (newObj.length * newObj.width * newObj.height) * dt->matGroup.at(newObj.materialName).density;
    ID id = genID();
    dt->objGroup.insert(std::make_pair(id, newObj));
    return id;
}

ID createObjectsFromComponentMap(gameData *dt, std::string mapName){
    ComponentMap cm = dt->componentMaps.at(mapName);
    std::vector<std::pair<std::string, ID> > cmpNamesToIDsMap;
    for(auto node : cm.map){
        cmpNamesToIDsMap.push_back(std::make_pair(node.first, createObject(dt, node.second.alternativeComponents[0])));
    }
    for(auto pair : cmpNamesToIDsMap){
        Object *obj = ao(dt, pair.second);
        for(auto mapLink : cm.map.at(pair.first).linkedObjects){
            ObjectLink objLink;
            for(auto pr : cmpNamesToIDsMap){
                if(pr.first == mapLink.subject){
                    objLink.subject = pr.second;
                    break;
                }
            }
            objLink.isFunctional = mapLink.isFunctional;
            objLink.strength = mapLink.strength;
            objLink.type = mapLink.type;
            obj->linkedObjects.push_back(objLink);
        }
    }
    return cmpNamesToIDsMap[0].second;
}

void removeObject(std::unordered_map<ID, Object> *objGroup, ID id_){
    objGroup->erase(id_);
}

void linkObjects(gameData *dt, ID obj1, objLinkType linkType, ID obj2, bool isFunctional, double strength){
    ObjectLink link1;
    link1.type = linkType;
    link1.isFunctional = isFunctional;
    link1.strength = strength;
    link1.subject = obj2;
    ao(dt, obj1)->linkedObjects.push_back(link1);

    ObjectLink link2;
    if(linkType == _WRAPS){
        link2.type = _WRAPPED_BY;
    }
    else if(linkType == _WRAPPED_BY){
        link2.type = _WRAPS;
    }
    else{
        link2.type = _ADJOINS;
    }
    link2.isFunctional = isFunctional;
    link2.strength = strength;
    link2.subject = obj1;
    ao(dt, obj2)->linkedObjects.push_back(link2);
}

void unlinkObjects(gameData *dt, ID obj1, ID obj2){
    std::vector<ObjectLink> *links1 = &dt->objGroup.at(obj1).linkedObjects;
    for(auto itr = links1->begin(); itr != links1->end(); itr++){
        if(itr->subject == obj2){
            links1->erase(itr);
            break;
        }
    }

    std::vector<ObjectLink> *links2 = &dt->objGroup.at(obj2).linkedObjects;
    for(auto itr = links2->begin(); itr != links2->end(); itr++){
        if(itr->subject == obj1){
            links2->erase(itr);
            break;
        }
    }
}

void printObjects(gameData *dt){
    std::cout << "------------------------------Loaded Objects----------------------------------" << std::endl;
    for(std::pair<ID, Object> obj : dt->objGroup){
        printObject(&dt->objGroup, &dt->objRules, obj.first);
    }
}

std::vector<ID> getPhysWeapons(gameData *dt, ID body){
    std::vector<ID> result;
    std::vector<ID> grippers = getLinkedObjs(dt, body, _ANY, true, "gripper");
    for(auto part : grippers){
        std::vector<ID> adjoins = getLinkedObjs(dt, part, _ADJOINS, false, "");
        result.insert(result.end(), adjoins.begin(), adjoins.end());
    }
    return result;
}

bool objHasUsageTag(gameData *dt, ID obj, std::string tag){
    auto rule = dt->objRules.at(ao(dt, obj)->objCode);
    if(tag == ""){
        return true;
    }
    for(auto itr = rule.usageTags.begin(); itr < rule.usageTags.end(); itr++){
        if(*itr == tag){
            return true;
        }
    }
    return false;
}

std::vector<ID> getLinkedObjs_Helper(gameData *dt, ID obj, objLinkType linkType, bool limitToFuncLinks, std::string usageTag, std::vector<ID> *visitedObjs){
    std::vector<ID> result;
    for(auto objLink : ao(dt, obj)->linkedObjects){
        if(find(visitedObjs->begin(), visitedObjs->end(), objLink.subject) == visitedObjs->end()){
            if((objLink.type == linkType || linkType == _ANY) && ((objLink.isFunctional && limitToFuncLinks) || !limitToFuncLinks) && objHasUsageTag(dt, objLink.subject, usageTag)){
                result.push_back(objLink.subject);
            }
        }
    }
    visitedObjs->push_back(obj);
    for(auto objLink : ao(dt, obj)->linkedObjects){
        if(find(visitedObjs->begin(), visitedObjs->end(), objLink.subject) == visitedObjs->end()){
            std::vector<ID> subResult = getLinkedObjs_Helper(dt, objLink.subject, linkType, limitToFuncLinks, usageTag, visitedObjs);
            result.insert(result.end(), subResult.begin(), subResult.end());
        }
    }
    return result;
}

/*
To "not care" about a property:
    linkType = _ANY
    isFunctional = NULL
    usageTag = ""
*/
std::vector<ID> getLinkedObjs(gameData *dt, ID obj, objLinkType linkType, bool limitToFuncLinks, std::string usageTag){
    std::vector<ID> visitedObjs;
    std::vector<ID> result;
    if(objHasUsageTag(dt, obj, usageTag)){
        result.push_back(obj);
    }
    std::vector<ID> subResult = getLinkedObjs_Helper(dt, obj, linkType, limitToFuncLinks, usageTag, &visitedObjs);
    result.insert(result.end(), subResult.begin(), subResult.end());
    return result;
}

void attackObject(gameData *dt, ID weapon, ID subject){
    if(subject != NULL_ID){
        Object *sub = ao(dt, subject);
        sub->integrity -= getMass(dt, weapon);
        if(sub->integrity <= 0){
            sub->integrity = 0;
        }
        std::cout << ao(dt, weapon)->name << " dealt " << getMass(dt, weapon) << " damage to " 
            << ao(dt, subject)->name << ", reducing its integrity to " << ao(dt, subject)->integrity << "\n";
    }
}

double getMass(gameData *dt, std::vector<ID> objs){
    double result = 0;
    for(auto obj : objs){
        Object *oPtr = ao(dt, obj);
        result += oPtr->height * oPtr->length * oPtr->width * dt->matGroup.at(oPtr->materialName).density;
    }
    return result;
}

double getMass(gameData *dt, ID obj){
    Object *oPtr = ao(dt, obj);
    return oPtr->height * oPtr->length * oPtr->width * dt->matGroup.at(oPtr->materialName).density;
}

Object *ao(gameData *dt, ID id){
    return &dt->objGroup.at(id);
}

std::vector<ID> getObjsWithCode(gameData *dt, objectCode objCode){
    std::vector<ID> result;
    for(auto obj : dt->objGroup){
        if(obj.second.objCode == objCode){
            result.push_back(obj.first);
        }
    }
    return result;
}

void printObjsWithCode(gameData *dt, objectCode objCode){
    std::vector<ID> objs = getObjsWithCode(dt, objCode);
    for(auto obj : objs){
        printObject(&dt->objGroup, &dt->objRules, obj);
    }
}