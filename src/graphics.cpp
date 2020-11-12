#include "graphics.h"

uint LeftClick_ButtonID;

int KeyPress;

void graphicsSetup(GraphicsLayer *grph){
    grph->setCamera(glm::vec3(0.0f, 2.5f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	grph->loadFont("textures/font.png");
    resetLeftClickedButtonID();
}

void graphicsDraw(GraphicsLayer *grph){
    grph->draw();
}

void onButtonLeftClick(uint buttonID){
    LeftClick_ButtonID = buttonID;
}

GraphObjID getLeftClickedButtonID(){
    return LeftClick_ButtonID;
}

void resetLeftClickedButtonID(){
    LeftClick_ButtonID = 0;
}

int getKeyPress(){
    return KeyPress;
}

void resetKeyPress(){
    KeyPress = 0;
}