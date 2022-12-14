#include "TasksGraph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct edgeNode {
    int origin;
    int dest;
    int time;
    int effort;
    edgeNode *next;
};

/*
 * Inputs:
 *  -
 * Outputs:
 *  - Returns a pointer to the header node of a list.
 * Restrictions:
 *  -
 */
graph *newGraph() {
    graph *g = (graph *) malloc(sizeof(graph));
    g->vertices = NULL;
    g->edges = NULL;
    g->size = 0;
    return g;
}

/*
 * Inputs:
 *  - pTask (task)
 * Outputs:
 *  - Returns a pointer to a vertexNode node.
 * Restrictions:
 *  - pTask must be a task type struct
 */
vertexNode *newVertexNode(task pTask) {
    vertexNode *n = (vertexNode *) malloc(sizeof(vertexNode));
    n->task = pTask;
    n->tree = NULL;
    n->next = NULL;
    return n;
}

/*
 * Inputs:
 *  - pOrigin (int)
 *  - pDest (int)
 *  - pTime (int)
 *  - pEffort (int)
 * Outputs:
 *  - Returns a pointer to an edgeNode node.
 * Restrictions:
 *  - pOrigin must be an integer number, and must be an ID of a graph task.
 *  - pDest must be an integer number, and must be an ID of a graph task.
 *  - pTime must be an integer number, > 0.
 *  - pEffort must be an integer number, > 0, <= 10.
 */
edgeNode *newEdgeNode(int pOrigin, int pDest, int pTime, int pEffort) {
    edgeNode *n = (edgeNode *) malloc(sizeof(edgeNode));
    n->origin = pOrigin;
    n->dest = pDest;
    n->time = pTime;
    n->effort = pEffort;
    n->next = NULL;
    return n;
}

/*
 * Inputs:
 *  - G (graph *)
 *  - pTask (task)
 * Outputs:
 *  - Adds a new vertex to the Graph.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pTask must be a task type struct
 */
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

/*
 * Inputs:
 *  - G (graph *)
 *  - pID (int)
 * Outputs:
 *  - Returns the time of the task with the same ID as pID.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pID must be an integer, and it must be the ID of a task.
 */
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

/*
 * Inputs:
 *  - G (graph *)
 *  - pID (int)
 * Outputs:
 *  - Returns the effort of the task with the same ID as pID.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pID must be an integer, and it must be the ID of a task.
 */
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

/*
 * Inputs:
 *  - G (graph *)
 *  - pID (int)
 * Outputs:
 *  - Returns the pointer to the treeNode of the vertexNode with the task with the same ID as pID.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pID must be an integer, and it must be the ID of a task.
 */
treeNode *getDocumentNode(graph *G, int pID) {
    treeNode *n;
    for (vertexNode *i = G->vertices; i != NULL; i = i->next)
        if (searchDocumentID(i->tree, pID) == 1) {
            n = getTreeNode(i->tree, pID);
            return n;
        }
    return NULL;
}

/*
 * Inputs:
 *  - G (graph *)
 *  - pID (int)
 * Outputs:
 *  - Returns 1 if there is a vertexNode with a task with the same ID as pID.
 *  - Returns 0 if there is not one.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pID must be an integer, and it must be the ID of a task.
 */
int searchTaskID(graph *G, int pID) {
    for (vertexNode *n = G->vertices; n != NULL; n = n->next) {
        if (n->task.ID == pID)
            return 1;
    }
    return 0;
}

/*
 * Inputs:
 *  - G (graph *)
 *  - pDesc (char [])
 * Outputs:
 *  - Returns 1 if there is a vertexNode with a task with the same description as pDesc.
 *  - Returns 0 if there is not one.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pDesc must be a char array.
 */
int searchTaskDesc(graph *G, char pDesc[]) {
    for (vertexNode *n = G->vertices; n != NULL; n = n->next) {
        if (strcmp(n->task.description, pDesc) == 0)
            return 1;
    }
    return 0;
}

/*
 * Inputs:
 *  - G (graph *)
 *  - pID (int)
 * Outputs:
 *  - Returns the pointer to the vertexNode with the task with the same ID as pID.
 *  - Returns NULL if there's not one.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pID must be an integer, and it must be the ID of a task.
 */
vertexNode *getVertexNode(graph *G, int pID) {
    for (vertexNode *n = G->vertices; n != NULL; n = n->next) {
        if (n->task.ID == pID)
            return n;
    }
    return NULL;
}

/*
 * Inputs:
 *  - G (graph *)
 *  - pOrigin (int)
 *  - pDest (int)
 * Outputs:
 *  - Returns 1 if there is an edgeNode with the same origin and dest as pOrigin and pDest.
 *  - Returns 0 if there is not one.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pOrigin must be an integer number, and must be an ID of a graph task.
 *  - pDest must be an integer number, and must be an ID of a graph task.
 */
int linearSearchEdge(graph *G, int pOrigin, int pDest) {
    edgeNode *n;
    for (n = G->edges; n != NULL; n = n->next)
        if (n->origin == pOrigin && n->dest == pDest)
            return 1;
    return 0;
}

/*
 * Inputs:
 *  - G (graph *)
 *  - pOrigin (int)
 *  - pDest (int)
 * Outputs:
 *  - Adds an edgeNode to the Graph.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pOrigin must be an integer number, and must be an ID of a graph task.
 *  - pDest must be an integer number, and must be an ID of a graph task.
 */
void insertEdge(graph *G, int pOrigin, int pDest) {
    if (linearSearchEdge(G, pOrigin, pDest) == 1 || pOrigin == pDest)
        return;

    edgeNode *n, *aux;
    int time = getTaskTime(G, pOrigin);
    int effort = getTaskEffort(G, pOrigin);
    edgeNode *newN = newEdgeNode(pOrigin, pDest, time, effort);
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

void addNewRoute(graph *G, const int *pArr, int pSize) {
    for (int i = 0; i < pSize; i++) {
        if (i != pSize - 1)
            insertEdge(G, pArr[i], pArr[i + 1]);
    }
}

/*
 * Inputs:
 *  - G (graph *)
 * Outputs:
 *  - Frees the graph.
 * Restrictions:
 *   - G must be a pointer to a graph node, and G must be != NULL.
 */
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

/*
 * Inputs:
 *  - G (graph *)
 * Outputs:
 *  - Saves the graph in multiple files.
 * Restrictions:
 *   - G must be a pointer to a graph node, and G must be != NULL.
 */
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

    fclose(file1);
    fclose(file2);
}

/*
 * Inputs:
 *  - G (graph *)
 * Outputs:
 *  - Loads the graph from multiple files.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 */
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

/*
 * Inputs:
 *  - G (graph *)
 * Outputs:
 *  - Updates the information for each edge after a change in the tasks' information.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 */
void updateEdges(graph *G) {
    for (edgeNode *n = G->edges; n != NULL; n = n->next) {
        n->effort = getTaskEffort(G, n->origin);
        n->time = getTaskTime(G, n->origin);
    }
}

/*
 * Inputs:
 *  - G (graph *)
 *  - pArr (const int *)
 *  - pSize (int)
 * Outputs:
 *  - Prints the route contained in pArr.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pArr must be a pointer to an integer array.
 *  - pSize must be the size of pArr.
 */
void printNewRoute(graph *G, const int *pArr, int pSize) {
    printf("\n[*] The the new route is:\n|| ");
    for (int i = 0; i < pSize; i++) {
        if (i != pSize - 1)
            printf("%d - {t:%d, e:%d} - > ", pArr[i], getTaskTime(G, pArr[i]), getTaskEffort(G, pArr[i]));
        else
            printf("%d ||", pArr[i], getTaskTime(G, pArr[i]), getTaskEffort(G, pArr[i]));
    }
    printf("\n");
}

/*
 * Inputs:
 *  - G (graph *)
 * Outputs:
 *  - Prints the adjacency list of the graph G.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 */
void printAdjacencyList(graph *G) {
    vertexNode *V;
    edgeNode *E;
    printf("[*] Adjacency List:\n");
    for (V = G->vertices; V != NULL; V = V->next) {
        printf("%d", V->task.ID);
        for (E = G->edges; E != NULL; E = E->next)
            if (E->origin == V->task.ID)
                printf(" -> {%d, t:%d, e:%d}", E->dest, E->time, E->effort);
        printf("\n");
    }
    printf("\n");
}

/*
 * Inputs:
 *  - G (graph *)
 * Outputs:
 *  - Prints the tasks contained in the graph G.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 */
void printProjectTasks(graph *G) {
    if (G->vertices == NULL){
        printf("[!] There are no tasks yet\n");
        return;
    }
    for (vertexNode *n = G->vertices; n != NULL; n = n->next) {
        printf("ID\t\t%d\n", n->task.ID);
        printf("Desc.\t\t%s\n", n->task.description);
        printf("Type\t\t%s\n", n->task.type);
        printf("Effort\t\t%d\n", n->task.effort);
        printf("Time\t\t%d\n", n->task.time);
        printf("Manger\t\t%s\n\n", n->task.manager);
    }
}

/*
 * Inputs:
 *  - G (graph *)
 * Outputs:
 *  - Prints the tasks contained in the graph G as a list.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 */
void printTasksList(graph *G) {
    vertexNode *n = G->vertices;
    printf("\n");
    for (int i = 0; i < G->size; i++) {
        if (i == 0)
            printf("{%d, ", n->task.ID);
        else if (i == G->size - 1)
            printf("%d}", n->task.ID);
        else
            printf("%d, ", n->task.ID);
        n = n->next;
    }
    printf("\n");
}

/*
 * Inputs:
 *  - G (graph *)
 *  - pDesc (char [])
 *  - pID (int)
 * Outputs:
 *  - Prints the tree of the vertexNode with the task with the same description as pDesc or with the same ID as pID.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pDesc must be a char array, pDesc mus be the description of graph task.
 *  - pID must be an integer, and it must be the ID of a task.
 */
void printTaskDocumentation(graph *G, char pDesc[], int pID) {
    int exists = 0;
    for (vertexNode *n = G->vertices; n != NULL; n = n->next) {
        if ((strcmp(n->task.description, pDesc) == 0) || n->task.ID == pID) {
            if (n->tree != NULL)
                exists = 1;
            printDocTree(n->tree);
        }
    }
    if (exists == 0) {
        printf("[!] There's no related Documentation!!\n");
    }
}

/*
 * Inputs:
 *  - G (graph *)
 *  - pID (int)
 * Outputs:
 *  - Prints the information of the document with the same ID as pID.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pID must be an integer, and it must be the ID of a document.
 */
void printDocumentByID(graph *G, int pID) {
    int exists = 0;
    for (vertexNode *n = G->vertices; n != NULL; n = n->next)
        if (searchDocumentID(n->tree, pID) == 1) {
            printDocument(n->tree, pID);
            exists = 1;
        }
    if (exists == 0) {
        printf("[!] There's no related document!!\n");
    }
}

/*
 * Inputs:
 *  - G (graph *)
 *  - pID (int)
 * Outputs:
 *  - Deletes the document with the same ID as pID, of the tree where it belongs.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pID must be an integer, and it must be the ID of a document.
 */
void deleteDocument(graph *G, int pID) {
    int exists = 0;
    for (vertexNode *n = G->vertices; n != NULL; n = n->next)
        if (searchDocumentID(n->tree, pID) == 1) {
            if (n->tree->doc.ID == pID && isLeaf(n->tree) == 1)
                n->tree = NULL;
            else
                n->tree = deleteTreeNode(n->tree, pID);
            exists = 1;
        }
    if (exists == 0) {
        printf("[!] There's no related document!!\n");
    }
}

/*
 * Inputs:
 *  - G (graph *)
 *  - pID (int)
 * Outputs:
 *  - Returns the index of the vertexNode with the task with the same ID as pID.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pID must be an integer, and it must be the ID of a task.
 */
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

/*
 * Inputs:
 *  - G (graph *)
 *  - pID (int)
 * Outputs:
 *  - Returns 1 if there's an ID of a document or a task equal to pID.
 *  - Returns 0 if there's not one.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pID must be an integer.
 */
int searchID(graph *G, int pID) {
    vertexNode *n;
    for (n = G->vertices; n != NULL; n = n->next)
        if (n->task.ID == pID || searchDocumentID(n->tree, pID) == 1)
            return 1;
    return 0;
}

//Dijkstra

typedef struct {
    int weight;
    int previous;
} label;

int getMinLabel(int size, const label pLabels[], const int pStatusArr[]) {
    int min = INT_MAX, index;
    for (int i = 0; i < size; i++)
        if (pStatusArr[i] == 0 && pLabels[i].weight <= min) {
            min = pLabels[i].weight;
            index = i;
        }
    return index;
}

int findBinarySearch(int *array, int element, int low, int high) {
    if (high >= low) {
        int mid = low + (high - low) / 2;
        if (array[mid] == element)
            return 1;
        if (array[mid] > element)
            return findBinarySearch(array, element, low, mid - 1);
        return findBinarySearch(array, element, mid + 1, high);
    }
    return 0;
}

int getIDByIndex(graph *G, int index) {
    vertexNode *n = G->vertices;
    for (int i = 0; i < G->size; i++) {
        if (i == index)
            return n->task.ID;
        n = n->next;
    }
    return -1;
}

void printOrder(graph *G, label labels[], int dest) {
    if (labels[dest].previous == -1) {
        printf("%d", getIDByIndex(G, dest));
        return;
    } else
        printOrder(G, labels, labels[dest].previous);
    printf(" --> %d", getIDByIndex(G, dest));
}

void printRecommendedRoute(graph *G, int size, label labels[]) {
    printf("Effort  Recommended Routes\n");
    for (int i = 0; i < size; i++) {
        if (labels[i].weight != INT_MAX)
            printf("[%d]\t", labels[i].weight);
        else
            printf("[--]\t");
        printOrder(G, labels, i);
        printf("\n");
    }
}

/*
 * Inputs:
 *  - G (graph *)
 *  - pIDSource (int)
 * Outputs:
 *  - Prints the distance and the shortest route to every task from the task pIDSource.
 * Restrictions:
 *  - G must be a pointer to a graph node, and G must be != NULL.
 *  - pID must be an integer, and it must be the ID of a task.
 */
void dijkstraAlgorithm(graph *G, int pIDSource) {
    int i, j;
    int matrix[G->size][G->size];

    for (i = 0; i < G->size; i++)
        for (j = 0; j < G->size; j++)
            matrix[i][j] = 0;

    for (edgeNode *n = G->edges; n != NULL; n = n->next) {
        i = linearSearchVertex(G, n->origin);
        j = linearSearchVertex(G, n->dest);
        matrix[i][j] = n->effort;
    }
    int src = linearSearchVertex(G, pIDSource);

    label labels[G->size];
    int statusArr[G->size];

    for (i = 0; i < G->size; i++) {
        labels[i].weight = INT_MAX;
        labels[i].previous = -1;
        statusArr[i] = 0;
    }

    labels[src].weight = 0;

    while (findBinarySearch(statusArr, 0, 0, G->size - 1) == 1) {
        int currIndex = getMinLabel(G->size, labels, statusArr);
        statusArr[currIndex] = 1;

        for (i = 0; i < G->size; i++) {
            if (statusArr[i] == 0 && matrix[currIndex][i] != 0
                && labels[currIndex].weight != INT_MAX
                && labels[currIndex].weight + matrix[currIndex][i] < labels[i].weight) {

                labels[i].weight = labels[currIndex].weight + matrix[currIndex][i];
                labels[i].previous = currIndex;

            }
        }
    }
    printRecommendedRoute(G, G->size, labels);
}
