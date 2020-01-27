/*IS_PLAYER tag allows creature to be controlled directly by the player, FRIENDLY means they are sympathetic to the player
creatures and may try to help*/
enum relationToPlyrUnits {HOSTILE, NEUTRAL, FRIENDLY, IS_PLAYER}; 

typedef struct{
    char name[10]; /*short species identifier, unused spaces filled with whitespace*/
    int lifespan;
} species;

typedef struct{
    int key;
    char speciesName[10];
    enum relationToPlyrUnits plyrRelation;
} creature;

typedef struct{
    int key;
    creature *head;
    creatureCollection *next;
} creatureCollection;

void update(unsigned long long int *clock){

}