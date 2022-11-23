#ifndef MAIN_C_RESOURCESLIST_H
#define MAIN_C_RESOURCESLIST_H

#include "FilesTree.h"

typedef struct resourcesList resourcesList;
typedef struct resourcesNode resourcesNode;

typedef struct {
    int ID;
    char name[STRSIZE];
    char type[STRSIZE];
    char capacity[STRSIZE];
    int amount;
    char manager[STRSIZE];
} resource;

resourcesList *newResourcesList();

resourcesNode *newResourcesNode(resource pRes);

void insertResource(resourcesList *L, resource pRes);

void deleteResource(resourcesList *L, int pID);

int isEmptyRList(resourcesList *L);

void freeResourcesList(resourcesList *L);

void printResourcesList(const resourcesList *L);

void saveResourcesList(resourcesList *L);

void loadResourcesList(resourcesList *L);

#endif //MAIN_C_RESOURCESLIST_H
