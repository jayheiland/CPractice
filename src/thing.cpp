#include "thing.h"

void Thing::printThing(){
    printf("Name :%s\n", name);
    printf("id: %lu\n", id);
    printf("templateID: %lu\n", templateID);
    printf("Component id's: ");
    for(ID id_ : components){
        printf("%lu, ", id_);
    }
    printf("\n");
    printf("isContainer: %d\n", isContainer);
    printf("equipmentType: %d\n", equipmentType);
    printf("equipmentSlotType: %d\n", equipmentSlotType);
    printf("containerType: %d\n", containerType);
    printf("containedThings id's: ");
    for(ID id_ : containedThings){
        printf("%lu\n", id_);
    }
    printf("\n");
    printf("maxContainerVolume: %d\n", maxContainerVolume);
}