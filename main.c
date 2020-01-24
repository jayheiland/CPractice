#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INT_MAX 2147483647

typedef char smallString[50];
typedef char longString[500];

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
    if(vec1->x == vec2->x && vec1->y == vec2->y && vec1->z == vec2->z){
        return 1;
    }
    return 0;
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

int getUnvisitedNeighbor(struct worldNode *node, struct worldNode *unvis){
    if(node->east != NULL && node->east->visited_Pathing != 0){
        unvis = node->east;
        return 1;
    }
    else if(node->west != NULL && node->west->visited_Pathing != 0){
        unvis = node->west;
        return 1;
    }
    else if(node->north != NULL && node->north->visited_Pathing != 0){
        unvis = node->north;
        return 1;
    }
    else if(node->south != NULL && node->south->visited_Pathing != 0){
        unvis = node->south;
        return 1;
    }
    else if(node->up != NULL && node->up->visited_Pathing != 0){
        unvis = node->up;
        return 1;
    }
    else if(node->down != NULL && node->down->visited_Pathing != 0){
        unvis = node->down;
        return 1;
    }
    else{
        return 0;
    }
}

struct worldNode *getNearestNeighbor(struct worldNode *node){
    int largestDist = INT_MAX;
    struct worldNode *nearest;
    if(node->east->distance_Pathing < largestDist){ nearest = node->east; largestDist = node->east->distance_Pathing; }
    else if(node->west->distance_Pathing < largestDist){ nearest = node->west; largestDist = node->west->distance_Pathing; }
    else if(node->north->distance_Pathing < largestDist){ nearest = node->north; largestDist = node->north->distance_Pathing; }
    else if(node->south->distance_Pathing < largestDist){ nearest = node->south; largestDist = node->south->distance_Pathing; }
    else if(node->up->distance_Pathing < largestDist){ nearest = node->up; largestDist = node->up->distance_Pathing; }
    else if(node->down->distance_Pathing < largestDist){ nearest = node->down; largestDist = node->down->distance_Pathing; }
    return nearest;
}

struct worldNode ***newWorld(Vec3 *size){
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

void markNodeNeighborsDistances(struct worldNode ***world, struct worldNode *curr, Vec3 *end, int edgeLen){
    struct worldNode *unvis = NULL;
    while(getUnvisitedNeighbor(curr, unvis)){
        int calcLen = (curr->distance_Pathing) + edgeLen;
        if(calcLen < unvis->distance_Pathing){
            unvis->distance_Pathing = calcLen;
        }
    }
}

Vec3 *worldPath(struct worldNode ***world, Vec3 *size, Vec3 *start, Vec3 *end){
    struct worldNode *curr;
    int edgeLen = 1;
    size_t x = size->x;
    size_t y = size->y;
    size_t z = size->z;
    Vec3 *unvisNodes = (Vec3 *)malloc(x * y * z * sizeof(Vec3));
    Vec3 *unvisNodesInitialPtr = unvisNodes;
    Vec3 *path, *tempPath;
    int unvisCount = 0;
    int i,j,k, idx;
    printf("initial values of unvisNodes: \n");
    for (i = 0; i <  size->x; i++){
        for (j = 0; j < size->y; j++){
            for (k = 0; k < size->z; k++){
                world[i][j][k].visited_Pathing = 0;
                world[i][j][k].distance_Pathing = INT_MAX;
                set(&unvisNodes[unvisCount], i,j,k);
                printf("index %d: %d,%d,%d\n", unvisCount, unvisNodes[unvisCount].x, unvisNodes[unvisCount].y, unvisNodes[unvisCount].z);
                unvisCount++;
            }
        }
    }

    world[start->x][start->y][start->z].distance_Pathing = 0;

    curr = &world[start->x][start->y][start->z];

    while(!world[end->x][end->y][end->z].visited_Pathing){
        printf("calling top level quicksort\n");
        quicksort(world, unvisNodes, 0, unvisCount-1);
        if(world[unvisNodes[0].x][unvisNodes[0].y][unvisNodes[0].z].distance_Pathing == INT_MAX){
            break;
        }
        curr = &world[unvisNodes[0].x][unvisNodes[0].y][unvisNodes[0].z];
        markNodeNeighborsDistances(world, curr, end, edgeLen);
        curr->visited_Pathing = 0;
        unvisNodes = &unvisNodes[1];
    }
    free(unvisNodesInitialPtr);

    tempPath = (Vec3 *)malloc((size_t)4 * (size_t)size->x * sizeof(Vec3));
    curr = &world[end->x][end->y][end->z];
    idx = 0;
    while(!equal(&curr->loc, start)){
        tempPath[idx] = curr->loc;
        curr = getNearestNeighbor(curr);
        idx++;
    }
    path = (Vec3 *)malloc((size_t)idx * sizeof(Vec3));
    memcpy(path, tempPath, (size_t)idx * sizeof(Vec3));
    free(tempPath);

    return path;
}

void gameLoop(){
    Vec3 world_size = {3,3,3};
    struct worldNode ***world = newWorld(&world_size);
    Vec3 test = {0,0,0};
    Vec3 testDest = {world_size.x-1,world_size.y-1,world_size.z-1};
    Vec3 *path;
    printf("entered gameloop\n");
    //printf("world[%d][%d][%d].south is at: %d,%d,%d\n", test.x,test.y,test.z,world[test.x][test.y][test.z].south->loc.x,world[test.x][test.y][test.z].south->loc.y,world[test.x][test.y][test.z].south->loc.z);
    path = worldPath(world, &world_size, &test, &testDest);
    free(path);
    delWorld(world, &world_size);
}

int main(void) {
    gameLoop();

    return 0;
}
