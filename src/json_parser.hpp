#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

//JSON supports string names and string, double, boolean, JSON object, or JSON array values

class JsonObject;
class JsonArray;

typedef union {
    char stringValue[500];
    double doubleValue;
    bool booleanValue;
    JsonObject *objectValue;
    JsonArray *arrayValue;
} Value;

class nameValuePair{
    private:
    public:
        std::string name;
        Value value;
};

class JsonArray{
    private:
        std::vector<Value> values;
    public:
        std::vector<std::string> getStringArray(){
            std::vector<std::string> result;
            for(auto val : values){
                result.push_back(val.stringValue);
            }
            return result;
        }
        std::vector<double> getDoubleArray(){
            std::vector<double> result;
            for(auto val : values){
                result.push_back(val.doubleValue);
            }
            return result;
        }
        std::vector<bool> getBooleanArray(){
            std::vector<bool> result;
            for(auto val : values){
                result.push_back(val.booleanValue);
            }
            return result;
        }
        std::vector<JsonObject *> getJsonObjectArray(){
            std::vector<JsonObject *> result;
            for(auto val : values){
                result.push_back(val.objectValue);
            }
            return result;
        }
        std::vector<JsonArray *> getJsonArrayArray(){
            std::vector<JsonArray *> result;
            for(auto val : values){
                result.push_back(val.arrayValue);
            }
            return result;
        }
        void pushBack(Value val){
            values.push_back(val);
        }
        int size(){
            return values.size();
        }
};

inline Value parseJsonValue(int *idx, std::string str);
inline void parseJsonObject(JsonObject *obj, int *idx, std::string str);
inline void deleteNameValuePair(nameValuePair pair);

class JsonObject{
    private:
        std::vector<nameValuePair> nameValuePairs;
    public:
        std::string getString(std::string name){
            for(uint idx = 0; idx < nameValuePairs.size(); idx++){
                if(nameValuePairs[idx].name == name){
                    return nameValuePairs[idx].value.stringValue;
                }
            }
            //throw std::runtime_error("JSON Parser: Could not find string value for name' " + name + "'");
            return NULL;
        }

        double getDouble(std::string name){
            for(uint idx = 0; idx < nameValuePairs.size(); idx++){
                if(nameValuePairs[idx].name == name){
                    return nameValuePairs[idx].value.doubleValue;
                }
            }
            //throw std::runtime_error("JSON Parser: Could not find double value for name' " + name + "'");
            return -1.0;
        }

        bool getBool(std::string name){
            for(uint idx = 0; idx < nameValuePairs.size(); idx++){
                if(nameValuePairs[idx].name == name){
                    return nameValuePairs[idx].value.booleanValue;
                }
            }
            //throw std::runtime_error("JSON Parser: Could not find boolean value for name' " + name + "'");
            return false;
        }

        JsonObject getJsonObject(std::string name){
            JsonObject empty;
            for(uint idx = 0; idx < nameValuePairs.size(); idx++){
                if(nameValuePairs[idx].name == name){
                    return *nameValuePairs[idx].value.objectValue;
                }
            }
            //throw std::runtime_error("JSON Parser: Could not find JSON object value for name' " + name + "'");
            return empty;
        }

        JsonArray getJsonArray(std::string name){
            JsonArray empty;
            for(uint idx = 0; idx < nameValuePairs.size(); idx++){
                if(nameValuePairs[idx].name == name){
                    return *nameValuePairs[idx].value.arrayValue;
                }
            }
            //std::cout << "JSON Parser: Could not find JSON array value for name' " << name << "'" << std::endl;
            return empty;
        }

        void appendNameValuePair(nameValuePair pair){
            nameValuePairs.push_back(pair);
        }

        void jsonObj_deleteNameValuePairs(){
            for(auto& pair : nameValuePairs){
                deleteNameValuePair(pair);
            }
        }
};

inline void parserLog(std::string type, std::string content){
    //std::cout << "JSON Parser Log: Parsed JSON " << type << " '" << content << "'." << std::endl;
}

inline std::string parseJsonString(int *idx, std::string str){
    std::string result = "";
    (*idx)++;
    while(str[*idx] != '"'){
        result += str[*idx];
        (*idx)++;
    }
    (*idx)++;
    parserLog("string value", result);
    return result;
}

inline double parseJsonDouble(int *idx, std::string str){
    std::string result = "";
    while(isdigit(str[*idx]) || str[*idx] == '.'){
        result+=str[*idx];
        (*idx)++;
    }
    parserLog("double value", result);
    return std::stod(result);
}

inline bool parseJsonBoolean(int *idx, std::string str){
    if(str[*idx] == 't' ){
        (*idx)+=4;
        return true;
    }
    else {
        (*idx)+=5;
        return false;
    }
}

inline JsonArray *parseJsonArray(int *idx, std::string str){
    JsonArray *result = new JsonArray();
    (*idx)++;
    Value firstVal = parseJsonValue(idx, str);
    result->pushBack(firstVal);
    while(str[*idx] != ']'){
        if(str[*idx] == ','){
            (*idx)++;
            result->pushBack(parseJsonValue(idx, str));
        }
        else{
            (*idx)++;
        }
    }
    (*idx)++;
    return result;
}

inline Value parseJsonValue(int *idx, std::string str){
    Value result;
    while(str[*idx] != '"' && !isdigit(str[*idx]) && str[*idx] != 't' && str[*idx] != 'f' && str[*idx] != '[' && str[*idx] != '{'){
        (*idx)++;
    }
    if(str[*idx] == '"'){
        std::string val = parseJsonString(idx, str);
        strcpy(result.stringValue, val.c_str());
    }
    else if(isdigit(str[*idx])){
        result.doubleValue = parseJsonDouble(idx, str);
    }
    else if(str[*idx] == 't' || str[*idx] == 'f'){
        result.booleanValue = parseJsonBoolean(idx, str);
    }
    else if(str[*idx] == '['){
        result.arrayValue = parseJsonArray(idx, str);
    }
    else if(str[*idx] == '{'){
        JsonObject *obj = new JsonObject();
        parseJsonObject(obj, idx, str);
        result.objectValue = obj;
    }
    return result;
}

inline void parseJsonNameValuePair(JsonObject *obj, int *idx, std::string str){
    nameValuePair pair;
    while(str[*idx] != '"'){
        (*idx)++;
    }
    pair.name = parseJsonString(idx, str);
    while(str[*idx] != ':'){
        (*idx)++;
    }
    pair.value = parseJsonValue(idx, str);
    while(str[*idx] != ',' && str[*idx] != '}'){
        (*idx)++;
    }
    parserLog("name-value pair", pair.name);
    obj->appendNameValuePair(pair);
}

inline void parseJsonObject(JsonObject *obj, int *idx, std::string str){
    while(str[*idx] != '}'){
        (*idx)++;
        if(str[*idx] == '"'){
            parseJsonNameValuePair(obj, idx, str);
        }
    }
}

inline JsonObject *parseJsonFile(std::string path){
    JsonObject *obj = new JsonObject();
    std::ifstream infile;
    infile.open(path);
    if(!infile.is_open()){
        logError("JSON Parser: Could not open file: '" + path + "'");
        return obj;
    }
    std::string content;
    content.assign( (std::istreambuf_iterator<char>(infile) ),
                    (std::istreambuf_iterator<char>()    ) );
    
    int idx = 0;
    parseJsonObject(obj, &idx, content);
    return obj;
}

inline void deleteNameValuePair(nameValuePair pair){

}

inline void deleteJsonObject(JsonObject *obj){

}