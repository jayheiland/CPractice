#include "battle_handler.h"


void startBattle(gameData *dt){
    dt->inBattle = true;
    createTurnQueue(dt);
}

void processBattle(gameData *dt){
    if(dt->inBattle){
        if(ac(dt, dt->turnQueue.front())->isPC){
            if(dt->weaponSelector.selectorButtons.size() == 0){
                createWeaponSelectorMenu(dt, dt->turnQueue.front());
            }
            if(dt->targetSelector.selectorButtons.size() == 0){
                createTargetSelectorMenu(dt, dt->turnQueue.back());
            }
            ID btnId = getLeftClickedButtonID();
            for(auto button : dt->weaponSelector.selectorButtons){
                if(btnId == button.second){
                    std::cout << "You selected the " << ao(dt,button.first)->name << std::endl;
                    dt->weaponSelector.selectedObject = button.first;
                    resetLeftClickedButtonID();
                }
            }
        }
        else{
            //basic target-picking NPC behavior
            for(auto crt : dt->crtGroup){
                if(crt.second.isPC){
                    setBattleTarget(&dt->crtGroup, dt->turnQueue.front(), crt.first);
                    break;
                }
            }
            Creature crt = *ac(dt, dt->turnQueue.front());
            ID targetPart = getLinkedObjs(dt, ac(dt, crt.battleTarget)->body, _ANY, FUNCTIONAL, "", false)[0];
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
    int iter = 1;
    for(auto obj : objects){
        GraphObjID btn = dt->grph->createButton(onButtonLeftClick, ao(dt, obj)->name, x, 1.0-(iter*y), 200, 200);
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
    std::vector<ID> targets = getLinkedObjs(dt, ac(dt,character)->body, _ANY, FUNCTIONAL, "", false);
    std::pair<uint, uint> dimen = dt->grph->getScreenDimensions();
    createStackSelector(dt, &dt->targetSelector, targets, 1.0-(300.0/dimen.first), 50.0/dimen.second);
}