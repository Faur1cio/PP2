#include "ResourcesList.h"
#include <stdlib.h>
#include <stdio.h>

struct ResourcesList {
    ResourcesNode *head;
    int size;
};

struct ResourcesNode {
    resource data;
    ResourcesNode *next;
};

ResourcesList *newResourcesList() {
    ResourcesList *L;
    L = (ResourcesList *) malloc(sizeof(ResourcesList));
    L->head = NULL;
    L->size = 0;
    return L;
}

ResourcesNode *newResourcesNode(resource pRes) {
    ResourcesNode *N;
    N = (ResourcesNode *) malloc(sizeof(ResourcesNode));
    N->next = NULL;
    N->data = pRes;
    return N;
}

void insertResource(ResourcesList *L, resource pRes) {
    ResourcesNode *n, *aux, *newNode;
    newNode = newResourcesNode(pRes);
    L->size++;
    if (L->head == NULL) {
        L->head = newNode;
        return;
    }
    n = L->head;
    while (n != NULL) {
        aux = n;
        n = n->next;
    }
    aux->next = newNode;
}

void deleteResource(ResourcesList *L, int pID) {
    ResourcesNode *aux, *n;
    if (L->head == NULL)
        return;
    if (L->head->data.ID == pID) {
        aux = L->head;
        L->head = L->head->next;
        free(aux);
        return;
    }
    n = L->head;
    while (n != NULL) {
        if (n->data.ID == pID) {
            aux->next = n->next;
            free(n);
            L->size--;
            return;
        }
        aux = n;
        n = n->next;
    }
}

void freeResourcesList(ResourcesList *L) {
    ResourcesNode *n, *aux;
    L->size = 0;
    if (L->head == NULL) {
        return;
    }
    n = L->head;
    while (n != NULL) {
        aux = n;
        n = n->next;
        free(aux);
    }
    L->head = NULL;
}

void printResourcesList(const ResourcesList *L) {
    printf("\nID\t\tName\t\tType\t\tCapacity\t\tAmount\t\tManager\n");
    printf("--\t\t----\t\t----\t\t--------\t\t------\t\t-------\n");
    for (ResourcesNode *n = L->head; n != NULL; n = n->next) {
        printf("%d\t\t%s\t\t%s\t\t%s\t\t%d\t\t%s", n->data.ID, n->data.name, n->data.type, n->data.amount,
               n->data.manager);
    }
    printf("\n");
}

void saveResourcesList(ResourcesList *L) {
    FILE *file;
    file = fopen("Resources", "wb");
    if (file == NULL)
        return;

    for (ResourcesNode *n = L->head; n != NULL; n = n->next)
        fwrite(n, sizeof(ResourcesNode), 1, file);

    fclose(file);
}

void loadResourcesList(ResourcesList *L) {
    ResourcesNode *temp = (ResourcesNode *) malloc(sizeof(ResourcesNode));
    FILE *file;
    file = fopen("Resources", "rb");
    if (file == NULL)
        return;

    while (fread(temp, sizeof(ResourcesNode), 1, file))
        insertResource(L, temp->data);

    free(temp);
    fclose(file);
}