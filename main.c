#include <stdio.h>
#include "FilesTree.h"
#include "TasksGraph.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 50

graph *Graph = NULL;

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

void register_Task_Menu(int pID) {
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
        return register_Task_Menu(pID);
    }
    strcpy(temp.type, tType);

    printf("[*] Insert the Effort (1 - 10):");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%s", str);
    if (!isNumeric(str)) {
        printf("[!] Invalid Effort, try again!!\n");
        return register_Task_Menu(pID);
    }
    tEffort = (int) strtol(str, (char **) NULL, 10);
    if (tEffort < 1 || tEffort > 10) {
        printf("[!] Invalid Effort, try again!!\n");
        return register_Task_Menu(pID);
    }
    temp.effort = tEffort;

    printf("[*] Insert the Time:");
    fgets(line, STRSIZE, stdin);
    sscanf(line, "%s", str);
    if (!isNumeric(str)) {
        printf("[!] Invalid Time, try again!!\n");
        return register_Task_Menu(pID);
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

void modify_Task_Menu(int pID) {
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
            return modify_Task_Menu(pID);
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
                return modify_Task_Menu(pID);
            }
            strcpy(temp.type, tType);
            node->task = temp;
            return modify_Task_Menu(pID);
        case '3':
            printf("[*] New Effort (1 - 10):");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid Effort, try again!!\n");
                return modify_Task_Menu(pID);
            }
            tEffort = (int) strtol(str, (char **) NULL, 10);
            if (tEffort < 1 || tEffort > 10) {
                printf("[!] Invalid Effort, try again!!\n");
                return modify_Task_Menu(pID);
            }
            temp.effort = tEffort;
            node->task = temp;
            return modify_Task_Menu(pID);
        case '4':
            printf("[*] New Time:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid Time, try again!!\n");
                return modify_Task_Menu(pID);
            }
            tTime = (int) strtol(str, (char **) NULL, 10);
            temp.time = tTime;
            node->task = temp;
            return modify_Task_Menu(pID);
        case '5':
            printf("[*] New Manager Name:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%[^\n]", tManager);
            strcpy(temp.manager, tManager);
            node->task = temp;
            return modify_Task_Menu(pID);
        case '0':
            printf("\n[i] Task Modified!\n");
            return;
        default:
            printf("[!] Invalid option, try again!!\n");
            return modify_Task_Menu(pID);
    }
}

void project_Tasks_Menu() {
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
            return project_Tasks_Menu();
        case '2':
            printf("[*] New Task:\n");
            printf("[*] Insert the ID:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid ID, it must be a number, try again!!\n");
                return project_Tasks_Menu();
            }
            number = (int) strtol(str, (char **) NULL, 10);
            if (countDigits(number) != 6) {
                printf("[!] Invalid ID, it must be a 6 digit number, try again!!\n");
                return project_Tasks_Menu();
            }
            if (searchID(Graph, number)) {
                printf("[!] Invalid ID, it's already being used, try again!!\n");
                return project_Tasks_Menu();
            }
            register_Task_Menu(number);
            return project_Tasks_Menu();
        case '3':
            printf("[*] Modify Task:\n");
            printf("[*] Insert the ID:");
            fgets(line, STRSIZE, stdin);
            sscanf(line, "%s", str);
            if (!isNumeric(str)) {
                printf("[!] Invalid ID, it must be a number, try again!!\n");
                return project_Tasks_Menu();
            }
            number = (int) strtol(str, (char **) NULL, 10);
            if (!linearSearchTask(Graph, number)){
                printf("[!] Invalid ID, try again!!\n");
                return project_Tasks_Menu();
            }
            modify_Task_Menu(number);
            updateEdges(Graph);
            return project_Tasks_Menu();
        case '0':
            return;
        default:
            printf("[!] Invalid option, try again!!\n");
            return project_Tasks_Menu();
    }
}

void menu() {
    printf("\n[*] Main menu\n");
    printf("[1] Project Tasks\n");
    printf("[2] Project Documentation\n");
    printf("[3] Manage Routes\n");
    printf("[3] Manage Resources\n");
    printf("[5] Work Breakdown Instruction\n");
    printf("[6] Recommended Route\n");
    printf("[0] Exit\n\n");
    printf("[*] Select an option:");

    int choice = getchar();
    while (choice == '\n')
        choice = getchar();
    printf("\n");
    flushStdin();

    switch (choice) {
        case '1':
            project_Tasks_Menu();
            return menu();
        case '2':
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
    loadGraph(Graph);

    menu();

    saveGraph(Graph);
    freeGraph(Graph);
    return 0;
}