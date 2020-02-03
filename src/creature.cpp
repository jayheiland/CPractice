#include "creature.h"

void updateCreatures(creatureGroup *group, unsigned long long int *clock){
    
}

void addCreature(creatureGroup *group, creature *newCreature){
    std::pair<unsigned long int, creature> newEntry (newCreature->id, *newCreature);
    group->hashtable->insert(newEntry);
}

void removeCreature(creatureGroup *group, unsigned long int id_){
    group->hashtable->erase(id_);
}

void loadCreatures(creatureGroup *group){
    FILE *f;
    char key[16];
    char data[100];
    if((f = fopen("../data/test.savegame", "r")) != NULL){
        while(1){
            int scan = fscanf(f, "creature {\n");
            if(scan == EOF || scan == 0){
                break;
            }
            fscanf(f, "    %s : %s\n", &key, &data);
        }
    }
}


//debug functions
void printFilesInDir(char *d){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("../data/")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            printf ("%s\n", ent->d_name);
        }
        closedir (dir);
    }
}
