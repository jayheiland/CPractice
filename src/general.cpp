#include "general.h"

void logError(const char func[], const char msg[]){
    printf("Error in %s: %s\n", func, msg);
}

unsigned long int genID(){
    return masterIDCounter++;
}