#include "object.h"

void printObject(std::unordered_map<ID, Object> *objGroup, Object *obj){
    printf("name: %s\n", obj->name.c_str());
    printf("component id's: ");
    for(ID id_ : obj->components){
        printf("  %lu, ", id_);
    }
    printf("\n");
    printf("containedThings id's: ");
    for(ID id_ : obj->containedObjects){
        printf("  %lu\n", id_);
    }
    printf("\n");
    std::cout << "equipped objects: " << std::endl;
    for(ID id_ : obj->equippedObjects){
        std::cout << "\t" << objGroup->at(id_).name << std::endl;
    }
    printf("maxContainerVolume: %f\n", obj->maxContainerVolume);
    std::cout << "material name: " << obj->materialName << std::endl 
        << "dimensions: " << obj->length << "," << obj->width << "," << obj->height << std::endl << std::endl;
}