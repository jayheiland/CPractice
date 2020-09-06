#include "material_group.h"

void loadMaterials_Json(std::unordered_map<std::string, Material> *matGroup, std::string path){
    Material newMat;
    JsonObject *materialsFromFile = parseJsonFile(path);
    for(auto mat : materialsFromFile->getJsonArray("materials").getJsonObjectArray()){
        newMat.name = mat->getString("name");
        newMat.density = mat->getDouble("density");
        newMat.tags = mat->getJsonArray("materialTags").getStringArray();
        matGroup->insert(std::make_pair(newMat.name, newMat));
    }
}

std::string getMaterialWithTag(std::unordered_map<std::string, Material> *matGroup, std::string desiredTag){
    for(auto mat : *matGroup){
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