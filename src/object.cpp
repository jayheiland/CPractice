#include "object.h"

void printObject(Object *obj){
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
    printf("maxContainerVolume: %f\n\n", obj->maxContainerVolume);
    std::cout << obj->name << std::endl << obj->materialName << std::endl 
        << obj->length << "," << obj->width << "," << obj->height << std::endl << std::endl;

}