#define STRSIZE 100

#ifndef PP2_ARBOL_H
#define PP2_ARBOL_H

typedef struct treeNode treeNode;
typedef struct document document;

struct document {
    int ID; //must be a 6 digit integer
    char path[STRSIZE];
    char description[STRSIZE];
    char type[STRSIZE];
};

struct treeNode {
    document doc;
    struct treeNode *left;
    struct treeNode *right;
};

int searchDocument(treeNode *pRoot, int pID);

treeNode *getFileNode(treeNode *pRoot, int pID);

void printInOrder(treeNode *pRoot);

void freeTree(treeNode *pRoot);

int isEmpty(treeNode *pRoot);

int isLeaf(treeNode *currentNode);

treeNode *insertTree(treeNode *pRoot, document pFile);

treeNode *deleteTreeNode(treeNode *pRoot, int pID);

void writeTreeToFile(char filename[], treeNode *pRoot);

//pRoot must be passed by reference readFileToTree("string", &root)
void readFileToTree(char filename[], treeNode **pRoot);

void printDocTree(treeNode *pRoot);

#endif //PP2_ARBOL_H
