#include "material_group.h"

MaterialGroup::MaterialGroup(){}

void MaterialGroup::loadMaterials(std::string path){
    Material newMat;
    std::string line;
    int lineNum = 1;
    std::ifstream infile;
    infile.open(path);
    if(!infile.is_open()){
        logError("loadMaterials", "Could not open materials file: '" + path + "'");
        return;
    }
    while (std::getline(infile, line)){
        if(line == "}"){
            std::pair<std::string, Material> entry(newMat.name, newMat);
            group.insert(entry);
        }
        else if(line.size() > 1){
            std::vector<std::string> tokens;
            splitString(&tokens, line, ':');
            //strip away whitespace
            for(int idx = 0; idx < tokens.size(); idx++){
                tokens[idx] = stripChar(tokens[idx], ' ');
            }
            if(std::string(tokens[0]) == "name"){ newMat.name = std::string(tokens[1]); }
        }
        else if(line == "{"){
            
        }
        else{
            logError("loadMaterials", "Could not process file: '" + path + "', at Line " + std::to_string(lineNum));
            return;
        }
        lineNum++;
    }
    infile.close();
}

//debug
void MaterialGroup::printMaterials(){
    std::cout << "loaded materials: \n";
    for ( auto itr = group.begin(); itr != group.end(); ++itr ){
        std::cout << "   " << itr->first << "\n";
    }
    std::cout << "\n";
}