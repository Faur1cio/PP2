#include "resourcesList.h"
#include <stdlib.h>
#include <stdio.h>

struct resourcesList {
    resourcesNode *head;
    int size;
};

struct resourcesNode {
    resource data;
    resourcesNode *next;
};

int isEmptyRList(resourcesList *L) {
    if (L->head == NULL)
        return 1;
    return 0;
}

resourcesList *newResourcesList() {
    resourcesList *L;
    L = (resourcesList *) malloc(sizeof(resourcesList));
    L->head = NULL;
    L->size = 0;
    return L;
}

resourcesNode *newResourcesNode(resource pRes) {
    resourcesNode *N;
    N = (resourcesNode *) malloc(sizeof(resourcesNode));
    N->next = NULL;
    N->data = pRes;
    return N;
}

void insertResource(resourcesList *L, resource pRes) {
    resourcesNode *n, *aux, *newNode;
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

void deleteResource(resourcesList *L, int pID) {
    resourcesNode *aux, *n;
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

void freeResourcesList(resourcesList *L) {
    resourcesNode *n, *aux;
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

void printResourcesList(const resourcesList *L) {
    printf("\nID    Name    Type    Capacity    Amount    Manager\n\n");
    for (resourcesNode *n = L->head; n != NULL; n = n->next) {
        printf("|| %d, %s, %s, %s, %d, %s", n->data.ID, n->data.name, n->data.type, n->data.capacity, n->data.amount,
               n->data.manager);
    }
    printf("\n");
}

void saveResourcesList(resourcesList *L) {
    FILE *file;
    file = fopen("Resources", "wb");
    if (file == NULL)
        return;

    for (resourcesNode *n = L->head; n != NULL; n = n->next)
        fwrite(n, sizeof(resourcesNode), 1, file);

    fclose(file);
}

void loadResourcesList(resourcesList *L) {
    resourcesNode *temp = (resourcesNode *) malloc(sizeof(resourcesNode));
    FILE *file;
    file = fopen("Resources", "rb");
    if (file == NULL)
        return;

    while (fread(temp, sizeof(resourcesNode), 1, file))
        insertResource(L, temp->data);

    free(temp);
    fclose(file);
}