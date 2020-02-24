#include "thing.h"

void Thing::printThing(){
    printf("Name :%s\n", name.c_str());
    printf("id: %lu\n", id);
    printf("component id's: ");
    for(ID id_ : components){
        printf("  %lu, ", id_);
    }
    printf("\n");
    printf("equippableAreas id's: ");
    for(ID id_ : equippableAreas){
        printf("  %lu, ", id_);
    }
    printf("\n");
    printf("containedThings id's: ");
    for(ID id_ : containedThings){
        printf("  %lu\n", id_);
    }
    printf("\n");
    printf("maxContainerVolume: %d\n", maxContainerVolume);
}