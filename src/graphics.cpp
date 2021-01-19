#include "graphics.h"

uint LeftClicked_ButtonID;

int KeyPressed;

void graphicsSetup(gameData *dt){
    dt->grph->setKeyEventCallback(onKeyEvent);
    dt->grph->setCamera(glm::vec3(15.0f, 15.0f, 9.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    dt->cameraTarget = {0,0,0};
    dt->cameraPos[0]=15.0;
    dt->cameraPos[1]=15.0;
    dt->cameraPos[2]=9.0;
	dt->grph->loadFont("textures/font.png");
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

void panCameraHelper(gameData *dt){

}

void panCamera(gameData *dt, CameraPanDirection direction){
    double diffX = dt->cameraPos[0]-dt->cameraTarget.loc.x;
    double diffY = dt->cameraPos[1]-dt->cameraTarget.loc.y;
    double moveX;
    double moveY;
    double panStep = 2.0;
    switch(direction){
        case PANUP: 
            if(diffX>0 && diffY>0){
                moveX=-panStep;
                moveY=-panStep;
            }
            else if(diffX>0 && diffY<0){
                moveX=-panStep;
                moveY=panStep;
            }
            else if(diffX<0 && diffY>0){
                moveX=panStep;
                moveY=-panStep;
            }
            else if(diffX<0 && diffY<0){
                moveX=panStep;
                moveY=panStep;
            }
            break;
        case PANDOWN: 
            if(diffX>0 && diffY>0){
                moveX=panStep;
                moveY=panStep;
            }
            else if(diffX>0 && diffY<0){
                moveX=panStep;
                moveY=-panStep;
            }
            else if(diffX<0 && diffY>0){
                moveX=-panStep;
                moveY=panStep;
            }
            else if(diffX<0 && diffY<0){
                moveX=-panStep;
                moveY=-panStep;
            }
            break;
        case PANLEFT: 
            if(diffX>0 && diffY>0){
                moveX=panStep;
                moveY=-panStep;
            }
            else if(diffX>0 && diffY<0){
                moveX=-panStep;
                moveY=-panStep;
            }
            else if(diffX<0 && diffY>0){
                moveX=panStep;
                moveY=panStep;
            }
            else if(diffX<0 && diffY<0){
                moveX=-panStep;
                moveY=panStep;
            }
            break;
        case PANRIGHT: 
            if(diffX>0 && diffY>0){
                moveX=-panStep;
                moveY=panStep;
            }
            else if(diffX>0 && diffY<0){
                moveX=panStep;
                moveY=panStep;
            }
            else if(diffX<0 && diffY>0){
                moveX=-panStep;
                moveY=-panStep;
            }
            else if(diffX<0 && diffY<0){
                moveX=panStep;
                moveY=-panStep;
            }
            break;
    }
    dt->cameraPos[0]+=moveX;
    dt->cameraPos[1]+=moveY;
    dt->cameraTarget.loc.x+=moveX;
    dt->cameraTarget.loc.y+=moveY;
    dt->grph->setCamera(glm::vec3((float)dt->cameraPos[0], (float)dt->cameraPos[1], (float)dt->cameraPos[2]), glm::vec3((float)dt->cameraTarget.loc.x, (float)dt->cameraTarget.loc.y, (float)dt->cameraTarget.loc.z));
}

void orbitCamera(gameData *dt, CameraOrbitDirection direction){
    double x = dt->cameraPos[0]-dt->cameraTarget.loc.x;
    double y = dt->cameraPos[1]-dt->cameraTarget.loc.y;
    float angle;
    switch(direction){
        case ORBITLEFT:{
            //default camera angle
            if(x>0 && y>0){
                dt->cameraPos[1]=dt->cameraTarget.loc.y-15.0;
                angle = glm::radians(270.0f);
            }
            //default camera angle
            else if(x>0 && y<0){
                dt->cameraPos[0]=dt->cameraTarget.loc.x-15.0;
                angle = glm::radians(180.0f);
            }
            else if(x<0 && y<0){
                dt->cameraPos[1]=dt->cameraTarget.loc.y+15.0;
                angle = glm::radians(90.0f);
            }
            else if(x<0 && y>0){
                dt->cameraPos[0]=dt->cameraTarget.loc.x+15.0;
                angle = glm::radians(0.0f);
            }
            break;
        }
        case ORBITRIGHT:{
            //default camera angle
            if(x>0 && y>0){
                dt->cameraPos[0]=dt->cameraTarget.loc.x-15.0;
                angle = glm::radians(90.0f);
            }
            //default camera angle
            else if(x>0 && y<0){
                dt->cameraPos[1]=dt->cameraTarget.loc.y+15.0;
                angle = glm::radians(0.0f);
            }
            else if(x<0 && y<0){
                dt->cameraPos[0]=dt->cameraTarget.loc.x+15.0;
                angle = glm::radians(270.0f);
            }
            else if(x<0 && y>0){
                dt->cameraPos[1]=dt->cameraTarget.loc.y-15.0;
                angle = glm::radians(180.0f);
            }
            break;
        }
    }
    for(auto crt : dt->crtGroup){
        dt->grph->setModelRotation(crt.second.model, glm::vec3(0.0f, 0.0f, 1.0f), angle);
    }
    dt->grph->setCamera(glm::vec3((float)dt->cameraPos[0], (float)dt->cameraPos[1], (float)dt->cameraPos[2]), glm::vec3((float)dt->cameraTarget.loc.x, (float)dt->cameraTarget.loc.y, (float)dt->cameraTarget.loc.z));
}