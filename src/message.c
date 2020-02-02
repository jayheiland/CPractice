#include "message.h"

extern engineData ENGINE_DATA;

void send(char msg[]){
    printf("%s\n", msg);
    if(!strcmp(msg, "QUIT_APP")){
        ENGINE_DATA.quitGame = 1;
    }
    if(!strcmp(msg, "TOGGLE_DEBUG_MODE")){
        ENGINE_DATA.debugMode = !ENGINE_DATA.debugMode;
    }
    if(ENGINE_DATA.debugMode){
        if(!strcmp(msg, "CONFIRM")){
            if(strlen(ENGINE_DATA.debugConsoleStr) > 0){
                send(ENGINE_DATA.debugConsoleStr);
            }
            memset(ENGINE_DATA.debugConsoleStr, 0, strlen(ENGINE_DATA.debugConsoleStr));
        }
        else if(strstr(msg, "_KEY_PRESSED") != NULL){
            char tmp[2];
            tmp[0] = msg[0];
            tmp[1] = '\0';
            strcat(ENGINE_DATA.debugConsoleStr, tmp);
        }
    }

    //testing stuff
    if(!strcmp(msg, "RAND")){
        int idx;
        for(idx = 0; idx < 10; idx++){
            char testID[ID_BUF];
            generateID(testID);
            printf("%s\n", testID);
        }
    }
    if(!strcmp(msg, "TIME")){
        time_t result = time(NULL);
        printf("%s\n", asctime(gmtime(&result)));
    }
}