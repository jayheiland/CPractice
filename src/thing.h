#ifndef THING_H
#define THING_H

typedef struct{
    char *name;
    unsigned long int id;
    int templateID;
    unsigned long int *components; //pointer to allocated id array of every thing that makes up this thing
    int componentCount;
    int isComponent; /*if true, then this thing does not display as a distinct object in the world; rather, it is an internal 
    component of another thing*/
    int isContainer;
    int equipmentType; //a number identifying the type of equipment, 0 if it is not equipment
    int equipmentSlotType; //a number identifying the type of equipment slot, 0 if it is not an equipment slot
    int containerType; /*a number identifying the type of container, 0 if it is not a container (a container is a thing that
    can be used to carry other things*/
    unsigned long int *containedThings; //pointer to allocated id array of every thing carried within this thing
    int containedThingsCount;
    int maxContainerVolume; //max total volume of things that can be carried within this thing

    int *chemProperties;

} thing;

#endif