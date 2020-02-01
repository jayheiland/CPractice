#include <string.h>

#include "world.h"

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

worldNode *getNearestNeighbor(worldNode *node, Vec3 *worldSize){
    int smallestDist = INT_MAX;
    worldNode *nearest = NULL;
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

worldNode ***newWorld(Vec3 *size){
    if(size->x <= 0 || size->y <= 0 || size->z <= 0){
        logError("newWorld", "Invalid world size");
    }
    size_t x = (size_t)size->x;
    size_t y = (size_t)size->y;
    size_t z = (size_t)size->z;
    size_t g,h;
    int i,j,k;
    worldNode ***world = (worldNode ***)malloc(x * sizeof(worldNode **));
    for (g=0; g<y; g++){
        world[g] = (worldNode **)malloc(y * sizeof(worldNode *));
        for (h=0; h<z; h++){
            world[g][h] = (worldNode *)malloc(z * sizeof(worldNode));
        }
    }
    
    for (i = 0; i <  size->x; i++){
        for (j = 0; j < size->y; j++){
            for (k = 0; k < size->z; k++){
                set(&world[i][j][k].loc, i,j,k);
                world[i][j][k].nodeType = 1;

                //set cardinal neighbor worldNode pointers
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

                //diagonal neighbors
                if(i>0 && j < (size->y)-1){ world[i][j][k].northeast= &world[i-1][j+1][k]; }
                else{ world[i][j][k].northeast = NULL; }
                
                if(i<(size->x)-1 && j < (size->y)-1){ world[i][j][k].northwest = &world[i+1][j+1][k]; }
                else{ world[i][j][k].northwest = NULL; }

                if(i>0 && j>0){ world[i][j][k].southeast = &world[i-1][j-1][k]; }
                else{ world[i][j][k].southeast = NULL; }

                if(i<(size->x)-1 && j>0){ world[i][j][k].southwest = &world[i+1][j-1][k]; }
                else{ world[i][j][k].southwest = NULL; }
            }
        }
    }

    return world;
}

void delWorld(worldNode ***world, Vec3* size){
    int j,k;
    for (j=0; j<size->y; j++){
        for (k=0; k<size->z; k++){
            free(world[j][k]);
        }
        free(world[j]);
    }
    free(world);
}

void quicksort(worldNode ***world, Vec3 *unvisNodes, int first, int last){
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

void markNodeNeighborsDistances(worldNode ***world, worldNode *curr, Vec3 *end, int edgeLen, Vec3 *worldSize){
    int calcLen = (curr->distance_Pathing) + edgeLen;
    if(curr->loc.x > 0 && !curr->east->visited_Pathing && calcLen < curr->east->distance_Pathing){
        curr->east->distance_Pathing = calcLen;
        //printf("Node at %d,%d,%d had east marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
    }
    if(curr->loc.x < worldSize->x-1 && !curr->west->visited_Pathing  && calcLen < curr->west->distance_Pathing){
        curr->west->distance_Pathing = calcLen;
        //printf("Node at %d,%d,%d had west marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
    }
    if(curr->loc.y < worldSize->y-1 && !curr->north->visited_Pathing  && calcLen < curr->north->distance_Pathing){
        curr->north->distance_Pathing = calcLen;
        //printf("Node at %d,%d,%d had north marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
    }
    if(curr->loc.y > 0 && !curr->south->visited_Pathing  && calcLen < curr->south->distance_Pathing){
        curr->south->distance_Pathing = calcLen;
        //printf("Node at %d,%d,%d had south marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
    }
    if(curr->loc.z < worldSize->z-1 && !curr->up->visited_Pathing  && calcLen < curr->up->distance_Pathing){
        curr->up->distance_Pathing = calcLen;
        //printf("Node at %d,%d,%d had up marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
    }
    if(curr->loc.z > 0 && !curr->down->visited_Pathing  && calcLen < curr->down->distance_Pathing){
        curr->down->distance_Pathing = calcLen;
        //printf("Node at %d,%d,%d had down marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
    }


    //diagonal neighbors
    if(curr->loc.x > 0 && curr->loc.y < worldSize->y-1 && !curr->northeast->visited_Pathing  && calcLen < curr->northeast->distance_Pathing){
        curr->northeast->distance_Pathing = calcLen;
        //printf("Node at %d,%d,%d had down marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
    }
    if(curr->loc.x < worldSize->x-1 && curr->loc.y < worldSize->y-1 && !curr->northwest->visited_Pathing  && calcLen < curr->northwest->distance_Pathing){
        curr->northwest->distance_Pathing = calcLen;
        //printf("Node at %d,%d,%d had down marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
    }
    if(curr->loc.x > 0 && curr->loc.y > 0 && !curr->southeast->visited_Pathing  && calcLen < curr->southeast->distance_Pathing){
        curr->southeast->distance_Pathing = calcLen;
        //printf("Node at %d,%d,%d had down marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
    }
    if(curr->loc.x < worldSize->x-1 && curr->loc.y > 0 && !curr->southwest->visited_Pathing  && calcLen < curr->southwest->distance_Pathing){
        curr->southwest->distance_Pathing = calcLen;
        //printf("Node at %d,%d,%d had down marked\n", curr->loc.x, curr->loc.y, curr->loc.z);
    }
    //printf("Newly visited node at %d,%d,%d has a current distance of: %d\n", curr->loc.x, curr->loc.y, curr->loc.z, curr->distance_Pathing);
}

Vec3 *worldPath(worldNode ***world, Vec3 *worldSize, Vec3 *start, Vec3 *end, int *pathLen){
    worldNode *curr;
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