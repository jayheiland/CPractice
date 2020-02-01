#include "message.h"

extern engineData ENGINE_DATA;

void send(char msg[]){
    printf("%s\n", msg);
    if(strcmp(msg, "QUIT_APP")==0){
        ENGINE_DATA.quitGame = 1;
    }
}