#include "battle.h"


void startBattle(gameData *dt){
    dt->inBattle = true;
    createTurnQueue(dt);
}

void processBattle(gameData *dt){
    if(dt->inBattle){
        //PC turn
        if(ac(dt, dt->turnQueue.front())->isPC){
            //create menus
            if(dt->weaponSelector.selectorButtons.size() == 0){
                createWeaponSelectorMenu(dt, dt->turnQueue.front());
            }
            //handle world clicks
            GraphObjID bBoxId = dt->grph->getClickedBoundingBox(LMB);
            if(bBoxId != 0){
                Vec3 lClickedLoc;
                if(dt->boundingBoxToCreature.find(bBoxId) != dt->boundingBoxToCreature.end()){
                    ID selecCrt = dt->boundingBoxToCreature.at(bBoxId);
                    if(dt->crtGroup.at(selecCrt).isPC){
                        dt->selectedPC = selecCrt;
                        std::cout << "Selected PC: " << dt->selectedPC << " at z :" << ac(dt, dt->selectedPC)->loc.loc.z << std::endl;
                    }
                    else{
                        dt->selectedNPC = selecCrt;
                    }
                    createTargetSelectorMenu(dt, selecCrt);
                    std::cout << "got creature: " << selecCrt << std::endl;
                }
                else{
                    lClickedLoc = dt->boundingBoxToLocation.at(bBoxId).loc;
                }
                //std::cout << "Clicked the node at: " << clickedLoc.x << "," << clickedLoc.y << "," << clickedLoc.z << " which is type: " << getNode(&dt->loadedChunk, clickedLoc) << std::endl;
            }
            bBoxId = dt->grph->getClickedBoundingBox(RMB);
            if(bBoxId != 0 && dt->boundingBoxToCreature.find(bBoxId) == dt->boundingBoxToCreature.end()){
                Vec3 rClickedLoc = dt->boundingBoxToLocation.at(bBoxId).loc;
                // std::cout << "Right clicked the node at: " << rClickedLoc.x << "," << rClickedLoc.y << "," << rClickedLoc.z << " which is type: " << getNode(&dt->loadedChunk, rClickedLoc)->nodeName << std::endl;
                rClickedLoc.z++; //move to the node above the one you clicked
                WorldLoc destination;
                destination.loc = rClickedLoc;
                // std::cout << "Attempting to move to node at: " << destination.loc.x << "," << destination.loc.y << "," << destination.loc.z << " which is type: " << getNode(&dt->loadedChunk, rClickedLoc)->nodeName << std::endl;
                moveToLocation(dt, dt->selectedPC, destination);
            }
            //handle button clicks
            ID btnId = getLeftClickedButtonID();
            for(auto wpn : dt->weaponSelector.selectorButtons){
                // if(btnId != 0){
                //     std::cout << "clicked button\n";
                // }
                if(btnId == wpn.second){
                    std::cout << "You selected the " << ao(dt,wpn.first)->name << std::endl;
                    dt->weaponSelector.selectedObject = wpn.first;
                }
            }
            for(auto trg : dt->targetSelector.selectorButtons){
                if(btnId == trg.second){
                    std::cout << "You targeted the " << ao(dt,trg.first)->name << std::endl;
                    dt->targetSelector.selectedObject = trg.first;
                }
            }
            resetLeftClickedButtonID();
            //key inputs
            switch(getKeyPressed()){
                case GLFW_KEY_SPACE:{
                    if(dt->weaponSelector.selectedObject != NULL_ID){
                        attackObject(dt, dt->weaponSelector.selectedObject, dt->targetSelector.selectedObject);
                    }
                    dt->weaponSelector.selectedObject = NULL_ID;
                    resetKeyPressed();
                    advanceTurnQueue(dt);
                    break;
                }
                case GLFW_KEY_W: panCamera(dt, PANUP); break;
            }
            resetKeyPressed();
        }
        //NPC turn
        else{
            //basic target-picking NPC behavior
            for(auto crt : dt->crtGroup){
                if(crt.second.isPC){
                    setBattleTarget(&dt->crtGroup, dt->turnQueue.front(), crt.first);
                    break;
                }
            }
            Creature crt = *ac(dt, dt->turnQueue.front());
            ID targetPart = getLinkedObjs(dt, ac(dt, crt.battleTarget)->body, ANY, FUNCTIONAL, "", false)[0];
            attackObject(dt, getPhysWeapons(dt, crt.body)[0], targetPart);
            advanceTurnQueue(dt);
        }
    }
}

void createTurnQueue(gameData *dt){
    dt->turnQueue = {};
    for(auto crt : dt->crtGroup){
        dt->turnQueue.push(crt.first);
    }
}

void advanceTurnQueue(gameData *dt){
    dt->turnQueue.push(dt->turnQueue.front());
    dt->turnQueue.pop();
}

void createStackSelector(gameData *dt, GUI_StackSelector *selector, std::vector<ID> objects, double x, double y){
    for(auto btn : selector->selectorButtons){
        dt->grph->removeButton(btn.second);
    }
    selector->selectorButtons.clear();
    selector->selectedObject = NULL_ID;
    int iter = 1;
    for(auto obj : objects){
        GraphObjID btn = dt->grph->createButton(onButtonLeftClick, ao(dt, obj)->name, x, 1.0-(iter*y));
        iter++;
        selector->selectorButtons.push_back(std::make_pair(obj, btn));
    }
}

void createWeaponSelectorMenu(gameData *dt, ID playerChar){
    std::vector<ID> weapons = getPhysWeapons(dt, ac(dt, playerChar)->body);
    std::pair<uint, uint> dimen = dt->grph->getScreenDimensions();
    createStackSelector(dt, &dt->weaponSelector, weapons, 20.0/dimen.first, 50.0/dimen.second);
}

void createTargetSelectorMenu(gameData *dt, ID character){
    std::vector<ID> targets = getLinkedObjs(dt, ac(dt,character)->body, ANY, FUNCTIONAL, "", false);
    targets.push_back(ac(dt,character)->body);
    std::pair<uint, uint> dimen = dt->grph->getScreenDimensions();
    createStackSelector(dt, &dt->targetSelector, targets, 1.0-(300.0/dimen.first), 50.0/dimen.second);
}