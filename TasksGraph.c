#include "TasksGraph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 9999999

struct graph {
    vertexNode *vertices;
    edgeNode *edges;
    int size;
};

struct task {
    int ID;
    char description[STRSIZE];
    char type[STRSIZE];
    int effort; // 1 to 10
    int time; //minutes
    char manager[STRSIZE];
};

struct edgeNode {
    int origin;
    int dest;
    int time;
    int effort;
    edgeNode *next;
};

struct vertexNode {
    task task;
    treeNode *tree;
    vertexNode *next;
};

graph *newGraph() {
    graph *g = (graph *) malloc(sizeof(graph));
    g->vertices = NULL;
    g->edges = NULL;
    g->size = 0;
    return g;
}

vertexNode *newVertexNode(task pTask) {
    vertexNode *n = (vertexNode *) malloc(sizeof(vertexNode));
    n->task = pTask;
    n->tree = NULL;
    n->next = NULL;
    return n;
}

edgeNode *newEdgeNode(int pOrigin, int pDest, int pTime, int pEffort) {
    edgeNode *n = (edgeNode *) malloc(sizeof(edgeNode));
    n->origin = pOrigin;
    n->dest = pDest;
    n->time = pTime;
    n->effort = pEffort;
    n->next = NULL;
    return n;
}

void insertVertex(graph *G, task pTask) {
    vertexNode *n, *aux;
    vertexNode *newN = newVertexNode(pTask);
    G->size++;
    if (G->vertices == NULL) {
        G->vertices = newN;
        return;
    }
    n = G->vertices;
    while (n != NULL) {
        aux = n;
        n = n->next;
    }
    aux->next = newN;
}

int getTaskTime(graph *G, int pID) {
    vertexNode *n;
    n = G->vertices;
    for (int i = 0; i < G->size; i++) {
        if (n->task.ID == pID)
            return n->task.time;
        n = n->next;
    }
    return 0;
}

int getTaskEffort(graph *G, int pID) {
    vertexNode *n;
    n = G->vertices;
    for (int i = 0; i < G->size; i++) {
        if (n->task.ID == pID)
            return n->task.effort;
        n = n->next;
    }
    return 0;
}

int linearSearchEdge(graph *G, int pOrigin, int pDest) {
    edgeNode *n;
    for (n = G->edges; n != NULL; n = n->next)
        if (n->origin == pOrigin && n->dest == pDest)
            return 1;
    return 0;
}

void insertEdge(graph *G, int pOrigin, int pDest) {
    if(linearSearchEdge(G, pOrigin, pDest) == 1) return;
    edgeNode *n, *aux;
    int time = getTaskTime(G, pOrigin);
    int effort = getTaskEffort(G, pOrigin);
    edgeNode *newN = newEdgeNode(pOrigin, pDest, time, effort);
    G->size++;
    if (G->edges == NULL) {
        G->edges = newN;
        return;
    }
    n = G->edges;
    while (n != NULL) {
        aux = n;
        n = n->next;
    }
    aux->next = newN;
}

void printAdjacencyList(graph *G) {
    vertexNode *V;
    edgeNode *E;
    printf("Adjacency List:\n");
    for (V = G->vertices; V != NULL; V = V->next) {
        printf("%d");
        for (E = G->edges; E != NULL; E = E->next)
            if (E->origin == V->task.ID)
                printf(" -> {%d, time:%d, effort:%d}", E->dest, E->time, E->effort);
        printf("\n");
    }
    printf("\n");
}

int linearSearchVertex(graph *G, int pID) {
    vertexNode *n;
    n = G->vertices;
    for (int i = 0; i < G->size; i++) {
        if (n->task.ID == pID)
            return i;
        n = n->next;
    }
    return -1;
}

int searchID(graph *G, int pID) {
    vertexNode *n;
    for (n = G->vertices; n != NULL; n = n->next)
        if (n->task.ID == pID || searchDocument(n->tree, pID) == 1)
            return 1;
    return 0;
}

void graphMatrixEffort(graph *G, int **matrix) {
    int i, j;
    for (i = 0; i < G->size; i++)
        for (j = 0; j < G->size; j++) {
            if (i == j)
                matrix[i][j] = 0;
            else
                matrix[i][j] = INF;
        }
    for (edgeNode *n = G->edges; n != NULL; n = n->next) {
        i = linearSearchVertex(G, n->origin);
        j = linearSearchVertex(G, n->dest);
        matrix[i][j] = n->effort;
    }
}

void graphMatrixTime(graph *G, int **matrix) {
    int i, j;
    for (i = 0; i < G->size; i++)
        for (j = 0; j < G->size; j++) {
            if (i == j)
                matrix[i][j] = 0;
            else
                matrix[i][j] = INF;
        }
    for (edgeNode *n = G->edges; n != NULL; n = n->next) {
        i = linearSearchVertex(G, n->origin);
        j = linearSearchVertex(G, n->dest);
        matrix[i][j] = n->time;
    }
}

void freeGraph(graph *G) {
    vertexNode *n, *aux;
    edgeNode *n2, *aux2;
    if (G->vertices == NULL) {
        return;
    }
    n = G->vertices;
    while (n != NULL) {
        aux = n;
        n = n->next;
        freeTree(aux->tree);
        free(aux);
    }
    n2 = G->edges;
    while (n2 != NULL) {
        aux2 = n2;
        n2 = n2->next;
        free(aux2);
    }
    G->vertices = NULL;
    G->edges = NULL;
}

void saveGraph(graph *G) {
    FILE *file1, *file2;
    char str[STRSIZE];
    file1 = fopen("verticesList", "wb");
    file2 = fopen("EdgesList", "wb");

    if (file1 == NULL || file2 == NULL)
        return;

    for (vertexNode *n = G->vertices; n != NULL; n = n->next) {
        fwrite(n, sizeof(vertexNode), 1, file1);
        str[0] = '\0';
        sprintf(str, "%d", n->task.ID);
        writeTreeToFile(str, n->tree);
    }
    for (edgeNode *n = G->edges; n != NULL; n = n->next)
        fwrite(n, sizeof(edgeNode), 1, file2);

    printf("\nData stored successfully!!\n");
    fclose(file1);
    fclose(file2);
}

void loadGraph(graph *G) {
    vertexNode *temp1 = (vertexNode *) malloc(sizeof(vertexNode));
    edgeNode *temp2 = (edgeNode *) malloc(sizeof(edgeNode));

    FILE *file1, *file2;
    char str[STRSIZE];
    file1 = fopen("verticesList", "rb");
    file2 = fopen("EdgesList", "rb");

    if (file1 == NULL || file2 == NULL)
        return;

    while (fread(temp1, sizeof(vertexNode), 1, file1))
        insertVertex(G, temp1->task);

    for (vertexNode *n = G->vertices; n != NULL; n = n->next) {
        str[0] = '\0';
        sprintf(str, "%d", n->task.ID);
        readFileToTree(str, &n->tree);
    }

    while (fread(temp2, sizeof(edgeNode), 1, file2))
        insertEdge(G, temp2->origin, temp2->dest);

    free(temp1);
    free(temp2);
    fclose(file1);
    fclose(file2);
}