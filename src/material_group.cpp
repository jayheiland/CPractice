#include "material_group.h"

void MaterialGroup::loadMaterials(std::string path){
    Material newMat;
    std::string arg[2];
    std::string line;
    std::ifstream matsFile ("../data/test.materials");
    if (matsFile.is_open())
    {
        while ( std::getline (matsFile,line) )
        {
            if(line == "{"){
                arg[0] = "";
                arg[1] = "";
            }
            else if(line == "}"){
                std::pair<std::string, Material> entry(newMat.name, newMat);
                group.insert(entry);
            }
            else{
                //sprintf(line, "   %s : %s", arg[0], arg[1]);
            }
        }
        matsFile.close();
    }
    else std::cout << "Unable to open materials file"; 
}

/*FILE *fp;
    char str[MAXCHAR];
    char* filename = "c:\\temp\\test.txt";
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    fclose(fp);



    

    sprintf(line, "   %s : %s", arg[0], arg[1]);*/