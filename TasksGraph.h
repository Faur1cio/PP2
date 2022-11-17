#include "FilesTree.h"

#ifndef PP2_GRAFO_H
#define PP2_GRAFO_H

typedef struct graph graph;
typedef struct vertexNode vertexNode;
typedef struct edgeNode edgeNode;
typedef struct task task;

graph *newGraph();

void freeGraph(graph *G);

void saveGraph(graph *G);

void loadGraph(graph *G);

#endif //PP2_GRAFO_H
