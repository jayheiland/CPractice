#include "graphics.h"

uint LeftClicked_ButtonID;

int KeyPressed;

void graphicsSetup(GraphicsLayer *grph){
    grph->setKeyEventCallback(onKeyEvent);
    grph->setCamera(glm::vec3(20.0f, 20.0f, 16.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	grph->loadFont("textures/font.png");
    resetLeftClickedButtonID();
    resetKeyPressed();
}

void graphicsDraw(GraphicsLayer *grph){
    grph->draw();
}

void onButtonLeftClick(uint buttonID){
    LeftClicked_ButtonID = buttonID;
}

GraphObjID getLeftClickedButtonID(){
    return LeftClicked_ButtonID;
}

void resetLeftClickedButtonID(){
    LeftClicked_ButtonID = 0;
}

void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        KeyPressed = key;
    }
}

int getKeyPressed(){
    return KeyPressed;
}

void resetKeyPressed(){
    KeyPressed = 18848353;
}