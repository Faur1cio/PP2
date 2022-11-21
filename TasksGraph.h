#include "FilesTree.h"

#ifndef PP2_GRAFO_H
#define PP2_GRAFO_H

typedef struct graph graph;
typedef struct vertexNode vertexNode;
typedef struct edgeNode edgeNode;
typedef struct task task;

struct task {
    int ID;
    char description[STRSIZE];
    char type[STRSIZE];
    int effort; // 1 to 10
    int time; //minutes
    char manager[STRSIZE];
};

struct vertexNode {
    task task;
    treeNode *tree;
    vertexNode *next;
};

graph *newGraph();

void freeGraph(graph *G);

void saveGraph(graph *G);

void loadGraph(graph *G);

void printProjectTasks(graph *G);

int searchID(graph *G, int pID);

void insertVertex(graph *G, task pTask);

vertexNode *getVertexNode(graph *G, int pID);

int linearSearchTask(graph *G, int pID);

void updateEdges(graph *G);

#endif //PP2_GRAFO_H
