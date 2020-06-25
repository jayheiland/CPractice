#include "general.h"

void logError(std::string msg){
    printf("Error: %s\n", msg.c_str());
}

unsigned long int genID(){
    return masterIDCounter++;
}

void splitString(std::vector<std::string> *tokens, std::string str, char delimiter){
    std::istringstream ss(str);
        while(ss.good()){
            std::string tk;
            std::getline(ss, tk, delimiter);
            tokens->push_back(tk);
        }
}

std::string stripChar(std::string str, char nix){
    std::string result = "";
    for(char c : str){
        if(c != nix){
            result += c;
        }
    }
    return result;
}

std::string stripCharAround(std::string str, char bookend){
    std::string result = "";
    bool strip = true;
    for(char c : str){
        if(strip && c == bookend){
            strip = false;
        }
        else if(!strip && c == bookend){
            strip = true;
        }
        else if(!strip && c != bookend){
            result += c;
        }
    }
    return result;
}

bool strContains(std::string str, int num, char ch){
    int count = 0;
    for(char charInStr : str){
        if(charInStr == ch){
            count++;
        }
    }
    if(count >= num){
        return true;
    }
    return false;
}

int roll(int numberDice, int numberSides){
    int total = 0;
    for(int die = 0; die < numberDice; die++){
        total += rand() % numberSides + 1;
    }
    return total;
}
