#include <stdio.h>
#include "docsTree.h"
#include "TasksGraph.h"
#include "resourcesList.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 50

graph *Graph = NULL;
resourcesList *Res = NULL;

void flushStdin() {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int countDigits(int pNum) {
    int count = 0;
    do {
        count++;
        pNum /= 10;
    } while (pNum != 0);
    return count;
}

int linearSearchArr(const int *pArr, int pSize, int pElement) {
    for (int i = 0; i < pSize; i++)
        if (pArr[i] == pElement)
            return 1;
    return 0;
}

int isNumeric(const char *str) {
    int i = 0;
    if (str[0] == '\0')
        return 0;
    while (str[i] != '\0') {
        if (isdigit(str[i]) == 0)
            return 0;
        i++;
    }
    return 1;
}

void registerTaskMenu(int pID) {
    task temp;
    temp.ID = pID;
    char tDesc[STRSIZE], tType[STRSIZE];
    char line[STRSIZE], tManager[STRSIZE];
    char str[STRSIZE];
    int tEffort, tTime;

    fflush(stdin);
    fflush(stdout);

    printf("[*] Insert the Description:");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%[^\n]", tDesc);
    strcpy(temp.description, tDesc);
    if (searchTaskDesc(Graph, tDesc) == 1) {
        printf("[!] Description already used, try again!!\n");
        return registerTaskMenu(pID);
    }

    printf("[*] Select the Type:\n");
    printf("[1] Operational Task.\n"
           "[2] Approval Task.\n"
           "[3] Contract signing.\n"
           "[4] Management Task.\n"
           "[5] Changes.\n");
    printf("[*] Select an option:");

    int choice = getchar();
    while (choice == '\n')
        choice = getchar();
    flushStdin();

    if (choice == '1')
        strcpy(tType, "Operational Task");
    else if (choice == '2')
        strcpy(tType, "Approval Task");
    else if (choice == '3')
        strcpy(tType, "Contract signing");
    else if (choice == '4')
        strcpy(tType, "Management Task");
    else if (choice == '5')
        strcpy(tType, "Changes");
    else {
        printf("[!] Invalid option, try again!!\n");
        return registerTaskMenu(pID);
    }
    strcpy(temp.type, tType);

    printf("[*] Insert the Effort (1 - 10):");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%s", str);
    if (!isNumeric(str)) {
        printf("[!] Invalid Effort, try again!!\n");
        return registerTaskMenu(pID);
    }
    tEffort = (int) strtol(str, (char **) NULL, 10);
    if (tEffort < 1 || tEffort > 10) {
        printf("[!] Invalid Effort, try again!!\n");
        return registerTaskMenu(pID);
    }
    temp.effort = tEffort;

    printf("[*] Insert the Time:");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%s", str);
    if (!isNumeric(str)) {
        printf("[!] Invalid Time, try again!!\n");
        return registerTaskMenu(pID);
    }
    tTime = (int) strtol(str, (char **) NULL, 10);
    temp.time = tTime;

    printf("[*] Insert the Manager Name:");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%[^\n]", tManager);
    strcpy(temp.manager, tManager);

    insertVertex(Graph, temp);
    printf("\n[i] Task Registered!\n");
}

void modifyTaskMenu(int pID) {
    printf("\n[*] Modify Task menu\n");
    printf("[1] Change description\n");
    printf("[2] Change Type\n");
    printf("[3] Change Effort\n");
    printf("[4] Change Time\n");
    printf("[5] Change Manager\n");
    printf("[0] Exit\n\n");
    printf("[*] Select an option:");

    fflush(stdout);
    fflush(stdin);

    int choice = getchar();
    while (choice == '\n')
        choice = getchar();
    printf("\n");
    flushStdin();

    vertexNode *node = getVertexNode(Graph, pID);
    task temp = node->task;
    char tDesc[STRSIZE], tType[STRSIZE];
    char line[STRSIZE], tManager[STRSIZE];
    char str[STRSIZE];
    int tEffort, tTime, choice2;

    switch (choice) {
        case '1':
            printf("[*] New Description:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%[^\n]", tDesc);
            strcpy(temp.description, tDesc);
            node->task = temp;
            return modifyTaskMenu(pID);
        case '2':
            printf("[*] New Type:\n");
            printf("[1] Operational Task.\n"
                   "[2] Approval Task.\n"
                   "[3] Contract signing.\n"
                   "[4] Management Task.\n"
                   "[5] Changes.\n");
            printf("[*] Select an option:");

            choice2 = getchar();
            while (choice2 == '\n')
                choice2 = getchar();
            flushStdin();

            if (choice2 == '1')
                strcpy(tType, "Operational Task");
            else if (choice2 == '2')
                strcpy(tType, "Approval Task");
            else if (choice2 == '3')
                strcpy(tType, "Contract signing");
            else if (choice2 == '4')
                strcpy(tType, "Management Task");
            else if (choice2 == '5')
                strcpy(tType, "Changes");
            else {
                printf("[!] Invalid option, try again!!\n");
                return modifyTaskMenu(pID);
            }
            strcpy(temp.type, tType);
            node->task = temp;
            return modifyTaskMenu(pID);
        case '3':
            printf("[*] New Effort (1 - 10):");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid Effort, try again!!\n");
                return modifyTaskMenu(pID);
            }
            tEffort = (int) strtol(str, (char **) NULL, 10);
            if (tEffort < 1 || tEffort > 10) {
                printf("[!] Invalid Effort, try again!!\n");
                return modifyTaskMenu(pID);
            }
            temp.effort = tEffort;
            node->task = temp;
            return modifyTaskMenu(pID);
        case '4':
            printf("[*] New Time:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid Time, try again!!\n");
                return modifyTaskMenu(pID);
            }
            tTime = (int) strtol(str, (char **) NULL, 10);
            temp.time = tTime;
            node->task = temp;
            return modifyTaskMenu(pID);
        case '5':
            printf("[*] New Manager Name:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%[^\n]", tManager);
            strcpy(temp.manager, tManager);
            node->task = temp;
            return modifyTaskMenu(pID);
        case '0':
            printf("\n[i] Task Modified!\n");
            return;
        default:
            printf("[!] Invalid option, try again!!\n");
            return modifyTaskMenu(pID);
    }
}

void projectTasksMenu() {
    printf("\n[*] Project Tasks menu\n");
    printf("[1] Show Project Tasks\n");
    printf("[2] Register Task\n");
    printf("[3] Modify Task\n");
    printf("[0] Exit\n\n");
    printf("[*] Select an option:");

    int choice = getchar();
    while (choice == '\n')
        choice = getchar();
    printf("\n");
    flushStdin();

    char str[STRSIZE], line[STRSIZE];
    int number;

    switch (choice) {
        case '1':
            printf("[*] Showing Tasks:\n");
            printProjectTasks(Graph);
            return projectTasksMenu();
        case '2':
            printf("[*] New Task:\n");
            printf("[*] Insert the ID:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid ID, it must be a number, try again!!\n");
                return projectTasksMenu();
            }
            number = (int) strtol(str, (char **) NULL, 10);
            if (countDigits(number) != 3) {
                printf("[!] Invalid ID, it must be a 3 digit number, try again!!\n");
                return projectTasksMenu();
            }
            if (searchID(Graph, number)) {
                printf("[!] Invalid ID, it's already being used, try again!!\n");
                return projectTasksMenu();
            }
            registerTaskMenu(number);
            return projectTasksMenu();
        case '3':
            printf("[*] Modify Task:\n");
            printf("[*] Insert the ID:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid ID, it must be a number, try again!!\n");
                return projectTasksMenu();
            }
            number = (int) strtol(str, (char **) NULL, 10);
            if (!searchTaskID(Graph, number)) {
                printf("[!] Invalid ID, try again!!\n");
                return projectTasksMenu();
            }
            modifyTaskMenu(number);
            updateEdges(Graph);
            return projectTasksMenu();
        case '0':
            return;
        default:
            printf("[!] Invalid option, try again!!\n");
            return projectTasksMenu();
    }
}

void registerDocument(int pID) {
    printf("[*] New Document\n");
    vertexNode *node = getVertexNode(Graph, pID);
    document temp;
    int tID;
    char tPath[STRSIZE], tDesc[STRSIZE], tType[STRSIZE];
    char line[STRSIZE], str[STRSIZE];

    fflush(stdin);
    fflush(stdout);

    printf("[*] Insert the ID:");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%s", str);
    if (!isNumeric(str)) {
        printf("[!] Invalid ID, it must be a number, try again!!\n");
        return projectTasksMenu();
    }
    tID = (int) strtol(str, (char **) NULL, 10);
    if (countDigits(tID) != 3) {
        printf("[!] Invalid ID, it must be a 3 digit number, try again!!\n");
        return registerDocument(pID);
    }
    if (searchID(Graph, tID)) {
        printf("[!] Invalid ID, it's already being used, try again!!\n");
        return registerDocument(pID);
    }
    temp.ID = tID;

    printf("[*] Insert the Path:");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%s", tPath);
    strcpy(temp.path, tPath);

    printf("[*] Insert the Description:");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%[^\n]", tDesc);
    strcpy(temp.description, tDesc);

    printf("[*] Insert the Type:");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%[^\n]", tType);
    strcpy(temp.type, tType);

    node->tree = insertTree(node->tree, temp);
    printf("\n[i] Document Registered!\n");
}

void modifyDocumentMenu(int pID) {
    printf("\n[*] Modify Document menu\n");
    printf("[1] Change Path\n");
    printf("[2] Change Description\n");
    printf("[3] Change Type\n");
    printf("[0] Exit\n\n");
    printf("[*] Select an option:");

    fflush(stdout);
    fflush(stdin);

    int choice = getchar();
    while (choice == '\n')
        choice = getchar();
    printf("\n");
    flushStdin();

    treeNode *node = getDocumentNode(Graph, pID);
    if (node == NULL) {
        printf("[!] Unknown error, try again!!\n");
        return;
    }
    document temp = node->doc;
    char line[STRSIZE], str[STRSIZE];

    switch (choice) {
        case '1':
            printf("[*] New Path:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            strcpy(temp.path, str);
            node->doc = temp;
            return modifyDocumentMenu(pID);
        case '2':
            printf("[*] New Description:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%[^\n]", str);
            strcpy(temp.description, str);
            node->doc = temp;
            return modifyDocumentMenu(pID);
        case '3':
            printf("[*] New Type:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%[^\n]", str);
            strcpy(temp.type, str);
            node->doc = temp;
            return modifyDocumentMenu(pID);
        case '0':
            printf("\n[i] Document Modified!!\n");
            return;
        default:
            printf("[!] Invalid option, try again!!\n");
            return modifyDocumentMenu(pID);
    }
}

void projectDocumentationMenu() {
    printf("\n[*] Project Documentation menu\n");
    printf("[1] Show Task Documentation\n");
    printf("[2] Show Document\n");
    printf("[3] Register Document\n");
    printf("[4] Modify Document\n");
    printf("[5] Delete Document\n");
    printf("[0] Exit\n\n");
    printf("[*] Select an option:");

    int choice = getchar();
    while (choice == '\n')
        choice = getchar();
    printf("\n");
    flushStdin();

    char line[STRSIZE], str[STRSIZE];
    int number;

    switch (choice) {
        case '1':
            printf("[*] Showing Task Documentation\n");
            printf("[*] Insert the ID, or the description of the Task:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (isNumeric(str) == 1) {
                number = (int) strtol(str, (char **) NULL, 10);
                printTaskDocumentation(Graph, "", number);
            } else {
                printTaskDocumentation(Graph, str, -1);
            }
            return projectDocumentationMenu();
        case '2':
            printf("[*] Showing Document\n");
            printf("[*] Insert the ID:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid ID, it must be a number, try again!!\n");
                return projectDocumentationMenu();
            }
            number = (int) strtol(str, (char **) NULL, 10);
            printDocumentByID(Graph, number);
            return projectDocumentationMenu();
        case '3':
            printf("[*] Register Document\n");
            printf("[*] Insert the Task ID:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid ID, it must be a number, try again!!\n");
                return projectDocumentationMenu();
            }
            number = (int) strtol(str, (char **) NULL, 10);
            if (!searchTaskID(Graph, number)) {
                printf("[!] Invalid ID, try again!!\n");
                return projectDocumentationMenu();
            }
            registerDocument(number);
            return projectDocumentationMenu();
        case '4':
            printf("[*] Modify Document\n");
            printf("[*] Insert the Document ID:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid ID, it must be a number, try again!!\n");
                return projectDocumentationMenu();
            }
            number = (int) strtol(str, (char **) NULL, 10);
            if (!searchID(Graph, number)) {
                printf("[!] Invalid ID, try again!!\n");
                return projectDocumentationMenu();
            }
            if (searchTaskID(Graph, number) == 1) {
                printf("[!] Invalid ID, it must be a document, try again!!\n");
                return projectDocumentationMenu();
            }
            modifyDocumentMenu(number);
            return projectDocumentationMenu();
        case '5':
            printf("[*] Delete Document\n");
            printf("[*] Insert the Document ID:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid ID, it must be a number, try again!!\n");
                return projectDocumentationMenu();
            }
            number = (int) strtol(str, (char **) NULL, 10);
            if (!searchID(Graph, number)) {
                printf("[!] Invalid ID, try again!!\n");
                return projectDocumentationMenu();
            }
            deleteDocument(Graph, number);
            return projectDocumentationMenu();
        case '0':
            return;
        default:
            printf("[!] Invalid option, try again!!\n");
            return projectDocumentationMenu();
    }
}

void manageRoutesMenu() {
    printf("\n[*] Routes menu\n");
    printf("[1] Create/Add a Route\n");
    printf("[2] Show Adjacency List\n");
    printf("[0] Exit\n\n");
    printf("[*] Select an option:");

    int choice = getchar();
    while (choice == '\n')
        choice = getchar();
    printf("\n");
    flushStdin();

    int route[Graph->size];
    char line[STRSIZE], str[STRSIZE];
    int number;

    switch (choice) {
        case '1':
            if (Graph->size < 2) {
                printf("[!] There are not enough tasks!!\n");
                return manageRoutesMenu();
            }
            printf("[*] Adding Route\n");
            printf("[*] List of tasks IDs:");
            printTasksList(Graph);
            printf("[*] Select the IDs and put them in order\n");
            int i = 0;
            while (i < Graph->size) {
                printf("[*] Inset the Task #%d:", i);
                fgets(line, STRSIZE, stdin);
                sscanf(line, "%s", str);
                if (!isNumeric(str)) {
                    printf("[!] Invalid ID, it must be a number, try again!!\n");
                    continue;
                }
                number = (int) strtol(str, (char **) NULL, 10);
                if (!searchTaskID(Graph, number)) {
                    printf("[!] Invalid ID, try again!!\n");
                    continue;
                }
                if (linearSearchArr(route, Graph->size, number) != 0) {
                    printf("[!] Task already in the route, try again!!\n");
                    continue;
                }
                route[i] = number;
                i++;
            }
            printNewRoute(Graph, route, Graph->size);
            addNewRoute(Graph, route, Graph->size);
            return manageRoutesMenu();
        case '2':
            if (Graph->size < 2) {
                printf("[!] There are not enough tasks!!\n");
                return manageRoutesMenu();
            }
            printAdjacencyList(Graph);
            return manageRoutesMenu();
        case '0':
            return;
        default:
            printf("[!] Invalid option, try again!!\n");
            return manageRoutesMenu();
    }
}

void addResourceMenu() {
    printf("[*] New Resource\n");
    resource temp;
    int ID, amount;
    char name[STRSIZE], type[STRSIZE];
    char capacity[STRSIZE], manager[STRSIZE];
    char line[STRSIZE], str[STRSIZE];

    fflush(stdin);
    fflush(stdout);

    printf("[*] Insert the ID:");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%s", str);
    if (!isNumeric(str)) {
        printf("[!] Invalid ID, it must be a number, try again!!\n");
        return addResourceMenu();
    }
    ID = (int) strtol(str, (char **) NULL, 10);
    temp.ID = ID;

    printf("[*] Insert the Name:");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%[^\n]", name);
    strcpy(temp.name, name);

    printf("[*] Insert the Type:");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%s", type);
    strcpy(temp.type, type);

    printf("[*] Select the Capacity:\n");
    printf("[D] Daily.\n"
           "[M] Monthly.\n"
           "[H] Hourly.\n");
    printf("[*] Select an option:");

    int choice = getchar();
    while (choice == '\n')
        choice = getchar();
    flushStdin();

    if (choice == 'D')
        strcpy(capacity, "Daily");
    else if (choice == 'M')
        strcpy(capacity, "Monthly");
    else if (choice == 'H')
        strcpy(capacity, "Hourly");
    else {
        printf("[!] Invalid option, try again!!\n");
        return addResourceMenu();
    }
    strcpy(temp.capacity, capacity);

    printf("[*] Insert the Amount:");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%s", str);
    if (!isNumeric(str)) {
        printf("[!] Invalid Amount, it must be a number, try again!!\n");
        return addResourceMenu();
    }
    amount = (int) strtol(str, (char **) NULL, 10);
    temp.amount = amount;

    printf("[*] Insert the Manager:");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%[^\n]", manager);
    strcpy(temp.manager, manager);

    insertResource(Res, temp);
    printf("\n[i] Resource Registered!\n");
}

void manageResourcesMenu() {
    printf("\n[*] Resources menu\n");
    printf("[1] Show resources\n");
    printf("[2] Add Resource\n");
    printf("[3] Delete Resource\n");
    printf("[0] Exit\n\n");
    printf("[*] Select an option:");

    int choice = getchar();
    while (choice == '\n')
        choice = getchar();
    printf("\n");
    flushStdin();

    int ID;
    char line[STRSIZE], str[STRSIZE];

    switch (choice) {
        case '1':
            if(isEmptyRList(Res)) {
                printf("[i] There are no Resources yet!!\n");
                return manageResourcesMenu();
            }
            printf("[*] Resources List:\n");
            printResourcesList(Res);
            return manageResourcesMenu();
        case '2':
            addResourceMenu();
            return manageResourcesMenu();
        case '3':
            printf("[*] Deleting Resource\n");
            printf("[*] Insert the Resource ID:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid ID, it must be a number, try again!!\n");
                return manageResourcesMenu();
            }
            ID = (int) strtol(str, (char **) NULL, 10);
            deleteResource(Res, ID);
            return manageResourcesMenu();
        case '0':
            return;
        default:
            printf("[!] Invalid option, try again!!\n");
            return manageResourcesMenu();
    }
}

void menu() {
    printf("\n[*] Main menu\n");
    printf("[1] Project Tasks\n");
    printf("[2] Project Documentation\n");
    printf("[3] Manage Routes\n");
    printf("[4] Manage Resources\n");
    printf("[5] Work Breakdown Instruction\n");
    printf("[6] Recommended Routes\n");
    printf("[0] Exit\n\n");
    printf("[*] Select an option:");

    int choice = getchar();
    while (choice == '\n')
        choice = getchar();
    printf("\n");
    flushStdin();

    char line[STRSIZE], str[STRSIZE];

    switch (choice) {
        case '1':
            projectTasksMenu();
            return menu();
        case '2':
            projectDocumentationMenu();
            return menu();
        case '3':
            manageRoutesMenu();
            return menu();
        case '4':
            manageResourcesMenu();
            return menu();
        case '6':
            printf("[*] Insert the first task:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid ID, it must be a number, try again!!\n");
                return menu();
            }
            int number = (int) strtol(str, (char **) NULL, 10);
            if (!searchTaskID(Graph, number)) {
                printf("[!] Invalid ID, try again!!\n");
                return menu();
            }
            dijkstraAlgorithm(Graph, number);
            return menu();
        case '0':
            return;
        default:
            printf("[!] Invalid option, try again!!\n");
            return menu();
    }
}

int main() {
    Graph = newGraph();
    Res = newResourcesList();
    loadGraph(Graph);
    loadResourcesList(Res);

    menu();

    saveResourcesList(Res);
    saveGraph(Graph);
    freeGraph(Graph);
    return 0;
}
