#include "worldm.h"

void set(Vec3 *vec, int x, int y, int z){
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

int equal(Vec3 *vec1, Vec3 *vec2){
    //printf("Comparing %d,%d,%d and %d,%d,%d\n", vec1->x, vec1->y, vec1->z, vec2->x, vec2->y, vec2->z);
    if(vec1->x == vec2->x && vec1->y == vec2->y && vec1->z == vec2->z){
        return 1;
    }
    return 0;
}

void printPath(Vec3 *path, int length){
    int idx;
    for(idx = 0; idx < length; idx++){
        printf("%d: (%d,%d,%d) | ", idx, path[idx].x, path[idx].y, path[idx].z);
    }
    printf("\n");
}

WorldNode *getNearestNeighbor(WorldNode *node, Vec3 *worldSize){
    double smallestDist = DBL_MAX;
    WorldNode *nearest = NULL;
    if(node->loc.x > 0 && node->east->distance_Pathing < smallestDist){ nearest = node->east; smallestDist = node->east->distance_Pathing; }
    if(node->loc.x < worldSize->x-1 && node->west->distance_Pathing < smallestDist){ nearest = node->west; smallestDist = node->west->distance_Pathing; }
    if(node->loc.y < worldSize->y-1 && node->north->distance_Pathing < smallestDist){ nearest = node->north; smallestDist = node->north->distance_Pathing; }
    if(node->loc.y > 0 && node->south->distance_Pathing < smallestDist){ nearest = node->south; smallestDist = node->south->distance_Pathing; }
    if(node->loc.z < worldSize->z-1 && node->up->distance_Pathing < smallestDist){ nearest = node->up; smallestDist = node->up->distance_Pathing; }
    if(node->loc.z > 0 && node->down->distance_Pathing < smallestDist){ nearest = node->down; smallestDist = node->down->distance_Pathing; }

    if(node->loc.x > 0 && node->loc.y < worldSize->y-1 && node->northeast->distance_Pathing < smallestDist){ nearest = node->northeast; smallestDist = node->northeast->distance_Pathing; }
    if(node->loc.x < worldSize->x-1 && node->loc.y < worldSize->y-1 && node->northwest->distance_Pathing < smallestDist){ nearest = node->northwest; smallestDist = node->northwest->distance_Pathing; }
    if(node->loc.x > 0 && node->loc.y > 0 && node->southeast->distance_Pathing < smallestDist){ nearest = node->southeast; smallestDist = node->southeast->distance_Pathing; }
    if(node->loc.x < worldSize->x-1 && node->loc.y > 0 && node->southwest->distance_Pathing < smallestDist){ nearest = node->southwest; smallestDist = node->southwest->distance_Pathing; }

    return nearest;
}

// void setFocusedChunk(gamedata *dt, std::string chunkPath, std::string nodeInfoPath, int xMapMax, int yMapMax){
//     std::vector<std::string> *tokens;
//     splitString(tokens, chunkPath, '-');
//     int xFocus = std::stoi(tokens->at(1));
//     int yFocus = std::stoi(tokens->at(2));
//     if(xFocus > 0 || xFocus < xMapMax || yFocus > 0 || yFocus < yMapMax){
//         dt->loadedChunks[0][0] = loadChunk(dt, tokens->at(0) + "-" + std::to_string(xFocus-1) + "-" + std::to_string(yFocus-1) + ".json", nodeInfoPath, {0,0,0});
//         dt->loadedChunks[0][1] = loadChunk(dt, tokens->at(0) + "-" + std::to_string(xFocus-1) + "-" + std::to_string(yFocus) + ".json", nodeInfoPath, {0,1,0});
//         dt->loadedChunks[0][2] = loadChunk(dt, tokens->at(0) + "-" + std::to_string(xFocus-1) + "-" + std::to_string(yFocus+1) + ".json", nodeInfoPath, {0,2,0});

//         dt->loadedChunks[1][0] = loadChunk(dt, tokens->at(0) + "-" + std::to_string(xFocus) + "-" + std::to_string(yFocus-1) + ".json", nodeInfoPath, {1,0,0});
//         dt->loadedChunks[1][1] = loadChunk(dt, tokens->at(0) + "-" + std::to_string(xFocus) + "-" + std::to_string(yFocus) + ".json", nodeInfoPath, {1,1,0});
//         dt->loadedChunks[1][2] = loadChunk(dt, tokens->at(0) + "-" + std::to_string(xFocus) + "-" + std::to_string(yFocus+1) + ".json", nodeInfoPath, {1,2,0});

//         dt->loadedChunks[2][0] = loadChunk(dt, tokens->at(0) + "-" + std::to_string(xFocus+1) + "-" + std::to_string(yFocus-1) + ".json", nodeInfoPath, {2,0,0});
//         dt->loadedChunks[2][1] = loadChunk(dt, tokens->at(0) + "-" + std::to_string(xFocus+1) + "-" + std::to_string(yFocus) + ".json", nodeInfoPath, {2,1,0});
//         dt->loadedChunks[2][2] = loadChunk(dt, tokens->at(0) + "-" + std::to_string(xFocus+1) + "-" + std::to_string(yFocus+1) + ".json", nodeInfoPath, {2,2,0});

//         stitchLoadedChunks(gamedata *dt);
//     }
// }

WorldChunk loadChunk(gamedata *dt, std::string chunkPath, std::string nodeInfoPath){
    JsonObject *chunkJson = parseJsonFile(chunkPath);
    JsonObject *nodeInfo = parseJsonFile(nodeInfoPath);

    //load all textures for this chunk
    for(auto ndInfo : nodeInfo->getJsonArray("nodeInfo").getJsonObjectArray()){
        NodeInfo newNodeInfo;
        newNodeInfo.material = ndInfo->getString("material");
        dt->nodeInfoMap.insert(std::make_pair(ndInfo->getString("name"), newNodeInfo));
    }
    for(auto nInfo : dt->nodeInfoMap){
        std::cout << "loaded nodeinfo: " << nInfo.second.material << std::endl;
    }

    //get chunk dimensions
    WorldChunk newChunk;
    Vec3 size;
    size.z = chunkJson->getJsonArray("nodes").getJsonArrayArray().size();
    size.y = chunkJson->getJsonArray("nodes").getJsonArrayArray()[0]->getJsonArrayArray().size();
    size.x = chunkJson->getJsonArray("nodes").getJsonArrayArray()[0]->getJsonArrayArray()[0]->getStringArray().size();

    if(size.x <= 0 || size.y <= 0 || size.z <= 0){
        logError("Invalid world size");
    }

    //allocate memory for chunk
    size_t x = (size_t)size.x;
    size_t y = (size_t)size.y;
    size_t z = (size_t)size.z;
    size_t g,h;
    int i,j,k;
    WorldNode ***nodes = (WorldNode ***)malloc(x * sizeof(WorldNode **));
    for (g=0; g<x; g++){
        nodes[g] = (WorldNode **)malloc(y * sizeof(WorldNode *));
        for (h=0; h<y; h++){
            nodes[g][h] = (WorldNode *)malloc(z * sizeof(WorldNode));
        }
    }
    
    //load chunk
    for (i = 0; i <  size.x; i++){
        for (j = 0; j < size.y; j++){
            for (k = 0; k < size.z; k++){
                set(&nodes[i][j][k].loc, i,j,k);
                strcpy(nodes[i][j][k].nodeName, chunkJson->getJsonArray("nodes").getJsonArrayArray().at(k)->getJsonArrayArray().at(j)->getStringArray().at(i).c_str());

                //set cardinal neighbor worldNode pointers
                //note: worldNode indexes count up east to west, south to north, and down to up
                if(i>0){ nodes[i][j][k].east = &nodes[i-1][j][k]; }
                else{ nodes[i][j][k].east = NULL; }
                if(i<(size.x)-1){ nodes[i][j][k].west = &nodes[i+1][j][k]; }
                else{ nodes[i][j][k].west = NULL; }

                if(j>0){ nodes[i][j][k].south = &nodes[i][j-1][k]; }
                else{ nodes[i][j][k].south = NULL; }
                if(j<(size.y)-1){ nodes[i][j][k].north = &nodes[i][j+1][k]; }
                else{ nodes[i][j][k].north = NULL; }

                if(k>0){ nodes[i][j][k].down = &nodes[i][j][k-1]; }
                else{ nodes[i][j][k].down = NULL; }
                if(k<(size.z)-1){ nodes[i][j][k].up = &nodes[i][j][k+1]; }
                else{ nodes[i][j][k].up = NULL; }

                //diagonal neighbors
                if(i>0 && j < (size.y)-1){ nodes[i][j][k].northeast= &nodes[i-1][j+1][k]; }
                else{ nodes[i][j][k].northeast = NULL; }
                
                if(i<(size.x)-1 && j < (size.y)-1){ nodes[i][j][k].northwest = &nodes[i+1][j+1][k]; }
                else{ nodes[i][j][k].northwest = NULL; }

                if(i>0 && j>0){ nodes[i][j][k].southeast = &nodes[i-1][j-1][k]; }
                else{ nodes[i][j][k].southeast = NULL; }

                if(i<(size.x)-1 && j>0){ nodes[i][j][k].southwest = &nodes[i+1][j-1][k]; }
                else{ nodes[i][j][k].southwest = NULL; }

                //add node 3D model
                if(dt->nodeInfoMap.at(nodes[i][j][k].nodeName).material != "air"){
                    Loc bBoxLoc;
                    bBoxLoc.x = i;
                    bBoxLoc.y = j;
                    bBoxLoc.z = k;
                    dt->boundingBoxToLocation.insert(std::make_pair(dt->grph->createBoundingBox(glm::vec3((float)i-0.5f,(float)j-0.5f,(float)k-0.5f), glm::vec3((float)i+0.5f,(float)j+0.5f,(float)k+0.5f)), bBoxLoc));
                }
            }
        }
    }
    TextureID chunkTxtr = dt->grph->createTexture("textures/grey.png");
    newChunk.model = dt->grph->createModel("models/arena.obj", chunkTxtr, glm::vec3(4.0f, 4.0f, 0.0f));
    newChunk.size = size;
    newChunk.nodes = nodes;
    newChunk.origin = {(int)chunkJson->getJsonArray("origin").getDoubleArray()[0], (int)chunkJson->getJsonArray("origin").getDoubleArray()[1]};
    deleteJsonObject(chunkJson);
    deleteJsonObject(nodeInfo);
    return newChunk;
}

void deleteChunk(WorldChunk *chunk){
    WorldNode ***nodes = chunk->nodes;
    Vec3* size = &chunk->size;
    int j,k;
    for (j=0; j<size->y; j++){
        for (k=0; k<size->z; k++){
            free(nodes[j][k]);
        }
        free(nodes[j]);
    }
    free(nodes);
}

void quicksort(WorldNode ***world, Vec3 *unvisNodes, int first, int last){
   int i, j, pivot;
   Vec3 temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(world[unvisNodes[i].x][unvisNodes[i].y][unvisNodes[i].z].distance_Pathing <= 
            world[unvisNodes[j].x][unvisNodes[j].y][unvisNodes[j].z].distance_Pathing && i<last){
            i++;
         }
         while(world[unvisNodes[j].x][unvisNodes[j].y][unvisNodes[j].z].distance_Pathing > 
            world[unvisNodes[pivot].x][unvisNodes[pivot].y][unvisNodes[pivot].z].distance_Pathing){
            j--;
         }
         if(i<j){
            temp=unvisNodes[i];
            unvisNodes[i]=unvisNodes[j];
            unvisNodes[j]=temp;
         }
      }

      temp=unvisNodes[pivot];
      unvisNodes[pivot]=unvisNodes[j];
      unvisNodes[j]=temp;
      quicksort(world, unvisNodes,first,j-1);
      quicksort(world, unvisNodes,j+1,last);

   }
}

bool canGoTo(gamedata *dt, WorldNode *node, std::vector<std::string> mobilityTags){
    Loc loc = node->loc;
    // printf("enter canGoTo with node at %d,%d,%d\n", loc.x, loc.y, loc.z);
    MaterialPhase phase;
    if(node->loc.z > 0){
        loc.z--;
        std::string nName = getNode(dt, loc)->nodeName;
        std::string nMat = dt->nodeInfoMap.at(nName).material;
        phase = dt->matGroup.at(nMat).phase;
        if(phase == SOLID && contains(mobilityTags, "ambulator")){
            return true;
            // printf("walker canGoTo return true\n");
        }
        loc.z++;
    }
    phase = dt->matGroup.at(dt->nodeInfoMap.at(getNode(dt, loc)->nodeName).material).phase;
    switch(phase){
        case LIQUID: if(contains(mobilityTags, "swimmer")) return true;
        case GAS: if(contains(mobilityTags, "flier")) return true;
        case SOLID: return false;
    }
    return false;
}

void markNodeNeighborsDistances(gamedata *dt, WorldNode *curr, double edgeLen, std::vector<std::string> mobilityTags){
    double calcLen = (curr->distance_Pathing) + edgeLen;
    Vec3 loc = curr->loc;
    Vec3 size = dt->loadedChunk.size;
    //east
    if(loc.x > 0 && !curr->east->visited_Pathing && calcLen < curr->east->distance_Pathing && canGoTo(dt, curr->east, mobilityTags)){
        curr->east->distance_Pathing = calcLen;
        // printf("Node at %d,%d,%d had east marked\n", loc.x, loc.y, loc.z);
    }
    //west
    if(loc.x < size.x-1 && !curr->west->visited_Pathing  && calcLen < curr->west->distance_Pathing && canGoTo(dt, curr->west, mobilityTags)){
        curr->west->distance_Pathing = calcLen;
        // printf("Node at %d,%d,%d had west marked\n", loc.x, loc.y, loc.z);
    }
    //north
    if(loc.y < size.y-1 && !curr->north->visited_Pathing  && calcLen < curr->north->distance_Pathing && canGoTo(dt, curr->north, mobilityTags)){
        curr->north->distance_Pathing = calcLen;
        // printf("Node at %d,%d,%d had north marked\n", loc.x, loc.y, loc.z);
    }
    //south
    if(loc.y > 0 && !curr->south->visited_Pathing  && calcLen < curr->south->distance_Pathing && canGoTo(dt, curr->south, mobilityTags)){
        curr->south->distance_Pathing = calcLen;
        // printf("Node at %d,%d,%d had south marked\n", loc.x, loc.y, loc.z);
    }
    //up
    if(loc.z < size.z-1 && !curr->up->visited_Pathing  && calcLen < curr->up->distance_Pathing && canGoTo(dt, curr->up, mobilityTags)){
        curr->up->distance_Pathing = calcLen;
        // printf("Node at %d,%d,%d had up marked\n", loc.x, loc.y, loc.z);
    }
    //down
    // std::cout << "down neighbor is: " << getNode(&dt->loadedChunk, loc)->nodeName << std::endl;
    if(loc.z > 0 && !curr->down->visited_Pathing  && calcLen < curr->down->distance_Pathing && canGoTo(dt, curr->down, mobilityTags)){
        curr->down->distance_Pathing = calcLen;
        // printf("Node at %d,%d,%d had down marked\n", loc.x, loc.y, loc.z);
    }


    //diagonal neighbors
    double diagExtra = 0.4142;
    if(loc.x > 0 && loc.y < size.y-1 && !curr->northeast->visited_Pathing  && calcLen < curr->northeast->distance_Pathing && canGoTo(dt, curr->northeast, mobilityTags)){
        curr->northeast->distance_Pathing = calcLen + diagExtra;
        // printf("Node at %d,%d,%d had northeast marked\n", loc.x, loc.y, loc.z);
    }
    if(loc.x < size.x-1 && loc.y < size.y-1 && !curr->northwest->visited_Pathing  && calcLen < curr->northwest->distance_Pathing && canGoTo(dt, curr->northwest, mobilityTags)){
        curr->northwest->distance_Pathing = calcLen + diagExtra;
        // printf("Node at %d,%d,%d had northwest marked\n", loc.x, loc.y, loc.z);
    }
    if(loc.x > 0 && loc.y > 0 && !curr->southeast->visited_Pathing  && calcLen < curr->southeast->distance_Pathing && canGoTo(dt, curr->southeast, mobilityTags)){
        curr->southeast->distance_Pathing = calcLen + diagExtra;
        // printf("Node at %d,%d,%d had southeast marked\n", loc.x, loc.y, loc.z);
    }
    if(loc.x < size.x-1 && loc.y > 0 && !curr->southwest->visited_Pathing  && calcLen < curr->southwest->distance_Pathing && canGoTo(dt, curr->southwest, mobilityTags)){
        curr->southwest->distance_Pathing = calcLen + diagExtra;
        // printf("Node at %d,%d,%d had southwest marked\n", loc.x, loc.y, loc.z);
    }
    //printf("Newly visited node at %d,%d,%d has a current distance of: %\n", loc.x, loc.y, loc.z, curr->distance_Pathing);
}

std::vector<Loc> worldPath(gamedata *dt, Loc *start, Loc *end, int maxDist, std::vector<std::string> mobilityTags){
    WorldNode *curr;
    std::vector<Loc> path;
    auto range = getPathingRange(dt, start, maxDist, mobilityTags);
    for(auto rangeLoc : range){
        if(rangeLoc == *end){
            curr = &dt->loadedChunk.nodes[end->x][end->y][end->z];
            while(!equal(&curr->loc, start)){
                Loc pathLoc;
                pathLoc = curr->loc;
                path.push_back(pathLoc);
                curr = getNearestNeighbor(curr, &dt->loadedChunk.size);
            }
        }
    }
    return path;
}

std::vector<Loc> getPathingRange(gamedata *dt, Vec3 *start, double maxDist, std::vector<std::string> mobilityTags){
    WorldNode *curr;
    double edgeLen = 1.0;
    size_t x = dt->loadedChunk.size.x;
    size_t y = dt->loadedChunk.size.y;
    size_t z = dt->loadedChunk.size.z;
    std::vector<Loc> range;
    Vec3 *unvisNodes = (Vec3 *)malloc(x * y * z * sizeof(Vec3));
    int unvisCount = 0;
    int i,j,k, idx;
    for (i = 0; i <  dt->loadedChunk.size.x; i++){
        for (j = 0; j < dt->loadedChunk.size.y; j++){
            for (k = 0; k < dt->loadedChunk.size.z; k++){
                dt->loadedChunk.nodes[i][j][k].visited_Pathing = 0;
                dt->loadedChunk.nodes[i][j][k].distance_Pathing = DBL_MAX;
                set(&unvisNodes[unvisCount], i,j,k);
                //printf("index %d: %d,%d,%d\n", unvisCount, unvisNodes[unvisCount].x, unvisNodes[unvisCount].y, unvisNodes[unvisCount].z);
                unvisCount++;
            }
        }
    }

    dt->loadedChunk.nodes[start->x][start->y][start->z].distance_Pathing = 0;

    curr = &dt->loadedChunk.nodes[start->x][start->y][start->z];

    while(curr->distance_Pathing < maxDist){
        Loc loc;
        loc = curr->loc;
        range.push_back(loc);
        //debug
        // printf("Before sorting unvisNodes array (of unvisCount = %d):\n", unvisCount);
        // for(idx = 0; idx < unvisCount; idx++){
        //     printf("%d: %d,%d,%d  dist: %d\n", idx, unvisNodes[idx].x, unvisNodes[idx].y, unvisNodes[idx].z, world[unvisNodes[idx].x][unvisNodes[idx].y][unvisNodes[idx].z].distance_Pathing);
        // }
        //uncomment this!
        quicksort(dt->loadedChunk.nodes, unvisNodes, 0, unvisCount-1);
        //debug
        // printf("After sorting unvisNodes array (of unvisCount = %d):\n", unvisCount);
        // for(idx = 0; idx < unvisCount; idx++){
        //     printf("%d: %d,%d,%d  dist: %d\n", idx, unvisNodes[idx].x, unvisNodes[idx].y, unvisNodes[idx].z, world[unvisNodes[idx].x][unvisNodes[idx].y][unvisNodes[idx].z].distance_Pathing);
        // }
        //uncomment this!
        if(dt->loadedChunk.nodes[unvisNodes[0].x][unvisNodes[0].y][unvisNodes[0].z].distance_Pathing == DBL_MAX){
            printf("Broke from distance painting loop. Likely no possible path.\n");
            return range;
        }
        curr = &dt->loadedChunk.nodes[unvisNodes[0].x][unvisNodes[0].y][unvisNodes[0].z];
        // std::cout << "about to mark dists for node at: " << curr->loc.x << "," << curr->loc.y << "," << curr->loc.z << std::endl;
        markNodeNeighborsDistances(dt, curr, edgeLen, mobilityTags);
        curr->visited_Pathing = 1;
        for(idx = 1; idx < unvisCount; idx++){
            unvisNodes[idx-1] = unvisNodes[idx];
        }
        unvisCount--;
    }
    free(unvisNodes);
    return range;
}

WorldNode *getNode(gamedata *dt, Loc loc){
    return &dt->loadedChunk.nodes[loc.x][loc.y][loc.z];
}