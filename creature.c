/*IS_PLAYER tag allows creature to be controlled directly by the player, FRIENDLY means they are sympathetic to the player
creatures and may try to help*/
enum relationToPlyrUnits {HOSTILE, NEUTRAL, FRIENDLY, IS_PLAYER}; 

struct creature{
    int key;
    enum relationToPlyrUnits plyrRelation;

};

struct creatureCollection{
    int key;
    struct creature *head;
    struct creatureCollection *next;
};

void update(unsigned long long int *clock){

}