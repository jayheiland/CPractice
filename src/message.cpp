#include "message.h"

extern engineData ENGINE_DATA;

//helper function, handles messages directed at graphics code
void send_GraphicsMsg(char *tokens[TOK_MAX]){
    if(!strcmp(tokens[0], "RESIZE_WINDOW")){
        ENGINE_DATA.windowWidth = atoi(tokens[1]);
        ENGINE_DATA.windowHeight = atoi(tokens[2]);
        SDL_SetWindowSize(ENGINE_DATA.window, ENGINE_DATA.windowWidth, ENGINE_DATA.windowHeight);
    }
    if(!strcmp(tokens[0], "FULLSCREEN")){
        if(!strcmp(tokens[1], "1")){
            SDL_SetWindowFullscreen(ENGINE_DATA.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
        else if(!strcmp(tokens[1], "0")){
            SDL_SetWindowFullscreen(ENGINE_DATA.window, 0);
        }
    }
}

//helper function, handles messages directed at Creatures
void send_CreatureMsg(char *tokens[TOK_MAX]){
    
}

void send(const char msg[]){
    //printf("Message before tokenizing: %s\n", msg);
    //parse message into tokens
    int idx = 0;
    char *tokens[TOK_MAX];
    if(strcmp(msg, " _KEY_PRESSED") != 0){
        for (char *p = strtok((char *)msg," "); idx < 4 && p != NULL; p = strtok(NULL, " "))
        {
            tokens[idx] = strdup(p);
            idx++;
        }
    }
    else{
        tokens[0] = strdup(msg);
    }
    //quit game
    if(!strcmp(tokens[0], "QUIT_APP")){
        ENGINE_DATA.quitGame = 1;
    }
    //developer console
    if(!strcmp(tokens[0], "TOGGLE_DEBUG_MODE")){
        ENGINE_DATA.debugMode = !ENGINE_DATA.debugMode;
    }
    if(ENGINE_DATA.debugMode){
        if(!strcmp(tokens[0], "CONFIRM")){
            if(strlen(ENGINE_DATA.debugConsoleStr) > 0){
                send(ENGINE_DATA.debugConsoleStr);
            }
            memset(ENGINE_DATA.debugConsoleStr, 0, strlen(ENGINE_DATA.debugConsoleStr));
        }
        else if(strstr(tokens[0], "_KEY_PRESSED") != NULL){
            char tmp[2];
            tmp[0] = tokens[0][0];
            tmp[1] = '\0';
            strcat(ENGINE_DATA.debugConsoleStr, tmp);
        }
    }

    //testing stuff
    if(!strcmp(tokens[0], "RAND")){
        int idx;
        ID testID;
        for(idx = 0; idx < 10; idx++){
            testID = genID();
            printf("%lu\n", testID);
        }
    }
    if(!strcmp(tokens[0], "TIME")){
        time_t result = time(NULL);
        printf("%s\n", asctime(gmtime(&result)));
    }

    //helpers
    send_GraphicsMsg(tokens);
    send_CreatureMsg(tokens);
}
