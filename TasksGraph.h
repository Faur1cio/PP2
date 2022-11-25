#include "docsTree.h"

#ifndef PP2_GRAPH_H
#define PP2_GRAPH_H

typedef struct graph graph;
typedef struct vertexNode vertexNode;
typedef struct edgeNode edgeNode;
typedef struct task task;

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

struct vertexNode {
    task task;
    treeNode *tree;
    vertexNode *next;
};

graph *newGraph();

void insertVertex(graph *G, task pTask);

void insertEdge(graph *G, int pOrigin, int pDest);

void addNewRoute(graph *G, const int *pArr, int pSize);

vertexNode *getVertexNode(graph *G, int pID);

treeNode *getDocumentNode(graph *G, int pID);

void deleteDocument(graph *G, int pID);

int searchID(graph *G, int pID);

int searchTaskID(graph *G, int pID);

int searchTaskDesc(graph *G, char pDesc[]);

void freeGraph(graph *G);

void updateEdges(graph *G);

void saveGraph(graph *G);

void loadGraph(graph *G);

void printProjectTasks(graph *G);

void printTasksList(graph *G);

void printTaskDocumentation(graph *G, char pDesc[], int pID);

void printDocumentByID(graph *G, int pID);

void printNewRoute(graph *G, const int *pArr, int pSize);

void printAdjacencyList(graph *G);

void dijkstraAlgorithm(graph *G, int pIDSource);

#endif //PP2_GRAPH_H
