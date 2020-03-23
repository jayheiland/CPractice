#include "material_group.h"

MaterialHandler::MaterialHandler(){}

void MaterialHandler::loadMaterials(std::string path){
    Material newMat;
    std::string line;
    int lineNum = 1;
    std::ifstream infile;
    infile.open(path);
    if(!infile.is_open()){
        logError("Could not open materials file: '" + path + "'");
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
            if(std::string(tokens[0]) == "name"){ 
                newMat.name = tokens[1]; 
            }
            if(std::string(tokens[0]) == "materialTags"){ 
                newMat.tags.clear();
                std::vector<std::string> newTags;
                splitString(&newTags, tokens[1], ',');
                for(std::string tag : newTags){
                    newMat.tags.push_back(tag); 
                }
                
            }
        }
        else if(line == "{"){
            
        }
        else{
            logError("Could not process file: '" + path + "', at Line " + std::to_string(lineNum));
            return;
        }
        lineNum++;
    }
    infile.close();
}

//debug
void MaterialHandler::printMaterials(){
    std::cout << "loaded materials: \n";
    for ( auto itr = group.begin(); itr != group.end(); ++itr ){
        std::cout << itr->first << "\n";
        for(std::string tag : itr->second.tags){
            std::cout << "\t" << tag << "\n";
        }
    }
    std::cout << "\n";
}