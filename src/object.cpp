#include "object.h"

void Object::printObject(){}

MultiObject::MultiObject(){}

void MultiObject::printObject(){
    printf("name: %s\n", name.c_str());
    printf("component id's: ");
    for(ID id_ : components){
        printf("  %lu, ", id_);
    }
    printf("\n");
    printf("containedThings id's: ");
    for(ID id_ : containedObjects){
        printf("  %lu\n", id_);
    }
    printf("\n");
    printf("maxContainerVolume: %f\n\n", maxContainerVolume);

}

ElementalObject::ElementalObject(){}

void ElementalObject::printObject(){
    std::cout << name << std::endl << materialName << std::endl 
        << length << "," << width << "," << height << std::endl << std::endl;
}