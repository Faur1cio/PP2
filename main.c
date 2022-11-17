#include <stdio.h>
#include "FilesTree.h"
#include "TasksGraph.h"

graph *Graph = NULL;

void menu(){
    printf("[*] Main menu\n");
    printf("[1] Project Tasks\n");
    printf("[2] Project Documentation\n");
    printf("[3] Manage Routes\n");
    printf("[5] Work Breakdown Instruction\n");
    printf("[6] Recommended Route\n");
    printf("[7] Exit\n");
}

int main() {
    Graph = newGraph();
    loadGraph(Graph);

    menu();

    saveGraph(Graph);
    freeGraph(Graph);
    return 0;
}
