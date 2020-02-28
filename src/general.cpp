#include "general.h"

void logError(std::string func, std::string msg){
    printf("Error in %s: %s\n", func.c_str(), msg.c_str());
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