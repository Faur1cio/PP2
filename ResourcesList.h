#ifndef MAIN_C_RESOURCESLIST_H
#define MAIN_C_RESOURCESLIST_H

#include "FilesTree.h"

typedef struct ResourcesList ResourcesList;
typedef struct ResourcesNode ResourcesNode;

typedef struct {
    int ID;
    char name[STRSIZE];
    char type[STRSIZE];
    char capacity[STRSIZE];
    int amount;
    char manager[STRSIZE];
} resource;

ResourcesList *newResourcesList();

ResourcesNode *newResourcesNode(resource pRes);

void insertResource(ResourcesList *L, resource pRes);

void deleteResource(ResourcesList *L, int pID);

void freeResourcesList(ResourcesList *L);

void printResourcesList(const ResourcesList *L);

void saveResourcesList(ResourcesList *L);

void loadResourcesList(ResourcesList *L);

#endif //MAIN_C_RESOURCESLIST_H
