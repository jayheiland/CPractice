#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INT_MAX 2147483647

typedef char smallString[50];
typedef char longString[500];

void logError(char func[], char msg[]){
    printf("Error in %s: %s\n", func, msg);
}

typedef struct{
    int x;
    int y;
    int z;
} Vec3;

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

struct worldNode{
    Vec3 loc;
    int processed;
    int nodeType;
    int visited_Pathing;
    unsigned int distance_Pathing;
    struct worldNode* east;
    struct worldNode* west;
    struct worldNode* north;
    struct worldNode* south;
    struct worldNode* up;
    struct worldNode* down;
};

struct worldNode *getNearestNeighbor(struct worldNode *node, Vec3 *worldSize){
    int smallestDist = INT_MAX;
    struct worldNode *nearest = NULL;
    if(node->loc.x > 0 && node->east->distance_Pathing < smallestDist){ nearest = node->east; smallestDist = node->east->distance_Pathing; }
    if(node->loc.x < worldSize->x-1 && node->west->distance_Pathing < smallestDist){ nearest = node->west; smallestDist = node->west->distance_Pathing; }
    if(node->loc.y < worldSize->y-1 && node->north->distance_Pathing < smallestDist){ nearest = node->north; smallestDist = node->north->distance_Pathing; }
    if(node->loc.y > 0 && node->south->distance_Pathing < smallestDist){ nearest = node->south; smallestDist = node->south->distance_Pathing; }
    if(node->loc.z < worldSize->z-1 && node->up->distance_Pathing < smallestDist){ nearest = node->up; smallestDist = node->up->distance_Pathing; }
    if(node->loc.z > 0 && node->down->distance_Pathing < smallestDist){ nearest = node->down; smallestDist = node->down->distance_Pathing; }
    return nearest;
}

struct worldNode ***newWorld(Vec3 *size){
    if(size->x <= 0 || size->y <= 0 || size->z <= 0){
        logError("newWorld", "Invalid world size");
    }
    size_t x = (size_t)size->x;
    size_t y = (size_t)size->y;
    size_t z = (size_t)size->z;
    size_t g,h;
    int i,j,k;
    struct worldNode ***world = (struct worldNode ***)malloc(x * sizeof(struct worldNode **));
    for (g=0; g<y; g++){
        world[g] = (struct worldNode **)malloc(y * sizeof(struct worldNode *));
        for (h=0; h<z; h++){
            world[g][h] = (struct worldNode *)malloc(z * sizeof(struct worldNode));
        }
    }
    
    for (i = 0; i <  size->x; i++){
        for (j = 0; j < size->y; j++){
            for (k = 0; k < size->z; k++){
                set(&world[i][j][k].loc, i,j,k);
                world[i][j][k].nodeType = 1;

                //set neighbor worldNode pointers
                //note: worldNode indexes count up east to west, south to north, and down to up
                if(i>0){ world[i][j][k].east = &world[i-1][j][k]; }
                else{ world[i][j][k].east = NULL; }
                if(i<(size->x)-1){ world[i][j][k].west = &world[i+1][j][k]; }
                else{ world[i][j][k].west = NULL; }

                if(j>0){ world[i][j][k].south = &world[i][j-1][k]; }
                else{ world[i][j][k].south = NULL; }
                if(j<(size->y)-1){ world[i][j][k].north = &world[i][j+1][k]; }
                else{ world[i][j][k].north = NULL; }

                if(k>0){ world[i][j][k].down = &world[i][j][k-1]; }
                else{ world[i][j][k].down = NULL; }
                if(k<(size->z)-1){ world[i][j][k].up = &world[i][j][k+1]; }
                else{ world[i][j][k].up = NULL; }
            }
        }
    }

    return world;
}

void delWorld(struct worldNode ***world, Vec3* size){
    int j,k;
    for (j=0; j<size->y; j++){
        for (k=0; k<size->z; k++){
            free(world[j][k]);
        }
        free(world[j]);
    }
    free(world);
}

void quicksort(struct worldNode ***world, Vec3 *unvisNodes, int first, int last){
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

void markNodeNeighborsDistances(struct worldNode ***world, struct worldNode *curr, Vec3 *end, int edgeLen, Vec3 *worldSize){
    int calcLen = (curr->distance_Pathing) + edgeLen;
    if(curr->loc.x > 0 && !curr->east->visited_Pathing){
        if(calcLen < curr->east->distance_Pathing){
            curr->east->distance_Pathing = calcLen;
            //printf("Node at %d,%d,%d had east marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
        }
    }
    if(curr->loc.x < worldSize->x-1 && !curr->west->visited_Pathing){
        if(calcLen < curr->west->distance_Pathing){
            curr->west->distance_Pathing = calcLen;
            //printf("Node at %d,%d,%d had west marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
        }
    }
    if(curr->loc.y < worldSize->y-1 && !curr->north->visited_Pathing){
        if(calcLen < curr->north->distance_Pathing){
            curr->north->distance_Pathing = calcLen;
            //printf("Node at %d,%d,%d had north marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
        }
    }
    if(curr->loc.y > 0 && !curr->south->visited_Pathing){
        if(calcLen < curr->south->distance_Pathing){
            curr->south->distance_Pathing = calcLen;
            //printf("Node at %d,%d,%d had south marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
        }
    }
    if(curr->loc.z < worldSize->z-1 && !curr->up->visited_Pathing){
        if(calcLen < curr->up->distance_Pathing){
            curr->up->distance_Pathing = calcLen;
            //printf("Node at %d,%d,%d had up marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
        }
    }
    if(curr->loc.z > 0 && !curr->down->visited_Pathing){
        if(calcLen < curr->down->distance_Pathing){
            curr->down->distance_Pathing = calcLen;
            //printf("Node at %d,%d,%d had down marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
        }
    }
    //printf("Newly visited node at %d,%d,%d has a current distance of: %d\n", curr->loc.x, curr->loc.y, curr->loc.z, curr->distance_Pathing);
}

Vec3 *worldPath(struct worldNode ***world, Vec3 *worldSize, Vec3 *start, Vec3 *end, int *pathLen){
    struct worldNode *curr;
    int edgeLen = 1;
    size_t x = worldSize->x;
    size_t y = worldSize->y;
    size_t z = worldSize->z;
    Vec3 *unvisNodes = (Vec3 *)malloc(x * y * z * sizeof(Vec3));
    Vec3 *path, *tempPath;
    int unvisCount = 0;
    int i,j,k, idx;
    if(equal(start, end)){
        path = (Vec3 *)malloc(sizeof(Vec3));
        path[0] = *start;
        *pathLen = 1;
        return path;
    }
    for (i = 0; i <  worldSize->x; i++){
        for (j = 0; j < worldSize->y; j++){
            for (k = 0; k < worldSize->z; k++){
                world[i][j][k].visited_Pathing = 0;
                world[i][j][k].distance_Pathing = INT_MAX;
                set(&unvisNodes[unvisCount], i,j,k);
                //printf("index %d: %d,%d,%d\n", unvisCount, unvisNodes[unvisCount].x, unvisNodes[unvisCount].y, unvisNodes[unvisCount].z);
                unvisCount++;
            }
        }
    }

    world[start->x][start->y][start->z].distance_Pathing = 0;

    curr = &world[start->x][start->y][start->z];

    while(!world[end->x][end->y][end->z].visited_Pathing){
        //debug
        /*printf("Before sorting unvisNodes array (of unvisCount = %d):\n", unvisCount);
        for(idx = 0; idx < unvisCount; idx++){
            printf("%d: %d,%d,%d  dist: %d\n", idx, unvisNodes[idx].x, unvisNodes[idx].y, unvisNodes[idx].z, world[unvisNodes[idx].x][unvisNodes[idx].y][unvisNodes[idx].z].distance_Pathing);
        }
        //reg
        quicksort(world, unvisNodes, 0, unvisCount-1);
        //debug
        printf("After sorting unvisNodes array (of unvisCount = %d):\n", unvisCount);
        for(idx = 0; idx < unvisCount; idx++){
            printf("%d: %d,%d,%d  dist: %d\n", idx, unvisNodes[idx].x, unvisNodes[idx].y, unvisNodes[idx].z, world[unvisNodes[idx].x][unvisNodes[idx].y][unvisNodes[idx].z].distance_Pathing);
        }*/
        //reg
        if(world[unvisNodes[0].x][unvisNodes[0].y][unvisNodes[0].z].distance_Pathing == INT_MAX){
            printf("Broke from distance painting loop. Likely no possible path.\n");
            path = (Vec3 *)malloc(sizeof(Vec3));
            path[0] = *start;
            *pathLen = 1;
            return path;
        }
        curr = &world[unvisNodes[0].x][unvisNodes[0].y][unvisNodes[0].z];
        markNodeNeighborsDistances(world, curr, end, edgeLen, worldSize);
        curr->visited_Pathing = 1;
        for(idx = 1; idx < unvisCount; idx++){
            unvisNodes[idx-1] = unvisNodes[idx];
        }
        unvisCount--;
    }
    free(unvisNodes);

    tempPath = (Vec3 *)malloc((size_t)4 * (size_t)worldSize->x * sizeof(Vec3));
    curr = &world[end->x][end->y][end->z];
    idx = 0;
    while(!equal(&curr->loc, start)){
        tempPath[idx] = curr->loc;
        curr = getNearestNeighbor(curr, worldSize);
        idx++;
    }
    path = (Vec3 *)malloc((size_t)idx * sizeof(Vec3));
    memcpy(path, tempPath, (size_t)idx * sizeof(Vec3));
    free(tempPath);
    *pathLen = idx;
    return path;
}

void gameLoop(){
    Vec3 worldSize = {20,20,20};
    struct worldNode ***world = newWorld(&worldSize);
    Vec3 test = {0,0,0};
    Vec3 testDest = {worldSize.x-1,worldSize.y-1,worldSize.z-1};
    Vec3 *path;
    int pathLen;
    path = worldPath(world, &worldSize, &test, &testDest, &pathLen);
    printPath(path, pathLen);
    free(path);
    delWorld(world, &worldSize);
}

int main(int argc, char** args) {
    gameLoop();

    return 0;
}
