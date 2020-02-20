#include "thing_group.h"

ThingGroup::ThingGroup(){}

void ThingGroup::addThing(Thing tng){
    std::pair<ID, Thing> entry (tng.id, tng);
    group.insert(entry);
}

void ThingGroup::loadThings(std::string path){

}

void ThingGroup::printThings(){
    for(std::pair<ID, Thing> tng : group){
        tng.second.printThing();
    }
}