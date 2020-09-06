#include "object.h"

void printObject(std::unordered_map<ID, Object> *objGroup, std::unordered_map<objectCode, ObjectRule> *objRules, ID id){
    Object obj = objGroup->at(id);
    printf("name: %s\n", obj.name.c_str());
    printf("usage tags: ");
    for(std::string useTag : objRules->at(objGroup->at(id).objCode).usageTags){
        printf("  %s, ", useTag.c_str());
    }
    printf("\n\n");
}