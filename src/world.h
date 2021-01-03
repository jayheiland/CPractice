#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "golden_plains.h"
#include "general.h"
#include "json_parser.hpp"

struct Vec3{
    int x;
    int y;
    int z;
    bool operator==(const Vec3& a) const
    {
        return (x == a.x && y == a.y && z == a.z);
    }
};

struct worldLoc{
    Vec3 chunk;
    Vec3 loc;
};

//a piece of 3D world space
struct worldNode{
    Vec3 loc;
    char nodeName[5];
    GraphObjID model;
    int visited_Pathing;
    uint distance_Pathing;
    struct worldNode* east;
    struct worldNode* west;
    struct worldNode* north;
    struct worldNode* south;
    struct worldNode* up;
    struct worldNode* down;
    struct worldNode* northeast;
    struct worldNode* northwest;
    struct worldNode* southeast;
    struct worldNode* southwest;
};

//a 3D matrix of worldNodes
struct WorldChunk{
    Vec3 chunkLoc;
    Vec3 size;
    worldNode ***nodes;
    std::unordered_map<std::string, TextureID> textures;
    struct WorldChunk* east;
    struct WorldChunk* west;
    struct WorldChunk* north;
    struct WorldChunk* south;
    struct WorldChunk* up;
    struct WorldChunk* down;
};

int equal(Vec3 *vec1, Vec3 *vec2);
void printPath(Vec3 *path, int length);
WorldChunk loadChunk(std::string chunkPath, std::string nodeInfoPath, GraphicsLayer *grph, std::unordered_map<std::string, TextureID> *textures, std::unordered_map<GraphObjID, worldLoc> *boundingBoxToLocation);
void deleteChunk(WorldChunk *chunk);
Vec3 *worldPath(worldNode ***world, Vec3 *worldSize, Vec3 *start, Vec3 *end, int *pathLen);
worldNode *getNode(WorldChunk *chunk, Vec3 loc);