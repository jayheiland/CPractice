#include "material_group.h"

void loadMaterials(std::unordered_map<std::string, Material> *matGroup, std::string path){
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
            matGroup->insert(entry);
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

std::string getMaterialWithTag(std::unordered_map<std::string, Material> *matGroup, std::string desiredTag){
    for(std::pair<std::string, Material> mat : *matGroup){
        for(std::string tag : mat.second.tags){
            if(tag == desiredTag){
                return mat.second.name;
            }
        }
    }
    return "";
}

//debug
void printMaterials(std::unordered_map<std::string, Material> *matGroup){
    std::cout << "-------------------------------Loaded Materials----------------------------------\n";
    for ( auto itr = matGroup->begin(); itr != matGroup->end(); ++itr ){
        std::cout << itr->first << "\n";
        for(std::string tag : itr->second.tags){
            std::cout << "\t" << tag << "\n";
        }
    }
    std::cout << "\n";
}