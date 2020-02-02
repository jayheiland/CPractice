#include "general.h"

void logError(char func[], char msg[]){
    printf("Error in %s: %s\n", func, msg);
}

//generates a pseudo-random ID string that is 16 characters long
void generateID(char *id){
    int num1 = 10000000 + (rand() % 9999999);
    int num2 = 10000000 + (rand() % 9999999);
    sprintf(id, "%d%d", num1, num2);
}
