#include "general.h"

void logError(const char func[], const char msg[]){
    printf("Error in %s: %s\n", func, msg);
}

//generates a pseudo-random ID string that is 16 characters long
void generateID(unsigned long int *id){
    *id = 1000000000 + (rand() % 4000000000);
}
