#include <stdio.h>
#include <stdlib.h>
#include "docsTree.h"

/*
 * Inputs:
 *  - pRoot (treeNode *)
 *  - pID (int)
 * Outputs:
 *  - Returns 1 if there's a document with the same ID as pID in the tree.
 *  - Returns 0 if there is not one.
 * Restrictions:
 *  - pRoot must be a pointer to a treeNode, and pRoot must be != NULL.
 *  - pID must be a 3 digits integer.
 */
int searchDocumentID(treeNode *pRoot, int pID) {
    if (pRoot == NULL)
        return 0;
    if (pRoot->doc.ID == pID)
        return 1;
    if (pID < pRoot->doc.ID)
        searchDocumentID(pRoot->left, pID);
    else
        searchDocumentID(pRoot->right, pID);
}

/*
 * Inputs:
 *  - pRoot (treeNode *)
 *  - pID (int)
 * Outputs:
 *  - Prints the document with the same ID as pID.
 * Restrictions:
 *  - pRoot must be a pointer to a treeNode, and pRoot must be != NULL.
 *  - pID must be a 3 digits integer.
 */
void printDocument(treeNode *pRoot, int pID) {
    if (pRoot == NULL) {
        return;
    }
    if (pRoot->doc.ID == pID) {
        printf("ID              %d\n"
               "Path            %s\n"
               "Desc            %s\n"
               "Type            %s\n\n", pRoot->doc.ID,
               pRoot->doc.path, pRoot->doc.description, pRoot->doc.type);
        return;
    }
    if (pID < pRoot->doc.ID)
        searchDocumentID(pRoot->left, pID);
    else
        searchDocumentID(pRoot->right, pID);
}

/*
 * Inputs:
 *  - pRoot (treeNode *)
 *  - pID (int)
 * Outputs:
 *  - Returns a pointer to the node with the document with the same ID as pID.
 * Restrictions:
 *  - pRoot must be a pointer to a treeNode, and pRoot must be != NULL.
 *  - pID must be a 3 digits integer.
 */
treeNode *getTreeNode(treeNode *pRoot, int pID) {
    if (pRoot == NULL)
        return pRoot;
    if (pRoot->doc.ID == pID)
        return pRoot;
    if (pID < pRoot->doc.ID)
        getTreeNode(pRoot->left, pID);
    else
        getTreeNode(pRoot->right, pID);
}

void printPreOrder(treeNode *pRoot) {
    if (pRoot != NULL) {
        printf("[%d, %s, %s, %s] ", pRoot->doc.ID,
               pRoot->doc.path, pRoot->doc.description, pRoot->doc.type);
        printPreOrder(pRoot->left);
        printPreOrder(pRoot->right);
    }
}

void printInOrder(treeNode *pRoot) {
    if (pRoot != NULL) {
        printInOrder(pRoot->left);
        printf("[%d, %s, %s, %s] ", pRoot->doc.ID,
               pRoot->doc.path, pRoot->doc.description, pRoot->doc.type);
        printInOrder(pRoot->right);
    }
}

/*
 * Inputs:
 *  - pRoot (treeNode *)
 * Outputs:
 *  - Prints each document in the tree.
 * Restrictions:
 *  - pRoot must be a pointer to a treeNode, and pRoot must be != NULL.
 */
void printDocTree(treeNode *pRoot) {
    if (pRoot != NULL) {
        printDocTree(pRoot->left);
        printf("ID.\t\t%d\n"
               "Path\t\t%s\n"
               "Desc\t\t%s\n"
               "Type\t\t%s\n\n", pRoot->doc.ID,
               pRoot->doc.path, pRoot->doc.description, pRoot->doc.type);
        printDocTree(pRoot->right);
    }
}

void printPostOrder(treeNode *pRoot) {
    if (pRoot != NULL) {
        printPostOrder(pRoot->left);
        printPostOrder(pRoot->right);
        printf("[%d, %s, %s, %s] ", pRoot->doc.ID,
               pRoot->doc.path, pRoot->doc.description, pRoot->doc.type);
    }
}

/*
 * Inputs:
 *  - pRoot (treeNode *)
 * Outputs:
 *  - Frees the whole tree.
 * Restrictions:
 *  - pRoot must be a pointer to a treeNode, and pRoot must be != NULL.
 */
void freeTree(treeNode *pRoot) {
    if (pRoot != NULL) {
        freeTree(pRoot->left);
        freeTree(pRoot->right);
        free(pRoot);
    }
}

int isEmpty(treeNode *pRoot) {
    return pRoot == NULL;
}

/*
 * Inputs:
 *  - currentNode (treeNode *)
 * Outputs:
 *  - Returns 1 if the currentNode is a leaf node.
 * Restrictions:
 *  - currentNode must be a pointer to a treeNode, and currentNode must be != NULL.
 */
int isLeaf(treeNode *currentNode) {
    return (currentNode->left == NULL && currentNode->right == NULL);
}

/*
 * Inputs:
 *  - pRoot (treeNode *)
 *  - pFile (document)
 * Outputs:
 *  - Inserts a node with the pFile (document) to the tree.
 * Restrictions:
 *  - pRoot must be a pointer to a treeNode, and pRoot must be != NULL.
 *  - pFile must be document type struct.
 */
treeNode *insertTree(treeNode *pRoot, document pFile) {
    if (pRoot == NULL) {
        treeNode *n = malloc(sizeof(treeNode));
        n->doc = pFile;
        n->left = NULL;
        n->right = NULL;
        return n;
    }
    if (pFile.ID < pRoot->doc.ID)
        pRoot->left = insertTree(pRoot->left, pFile);

    else
        pRoot->right = insertTree(pRoot->right, pFile);

    return pRoot;
}

/*
 * Inputs:
 *  - currentNode (treeNode *)
 * Outputs:
 *  - Gets the node that is furthest to the left
 * Restrictions:
 *  - currentNode must be a pointer to a treeNode, and currentNode must be != NULL.
 */
treeNode *getMinNode(treeNode *currentNode) {
    if (currentNode == NULL || currentNode->left == NULL)
        return currentNode;
    else
        getMinNode(currentNode->left);
}

/*
 * root = deleteTreeNode()
 *
 * Function doesn't work when there's only one node
 * if(isLeaf(root) == 1)
 *      root = NULL;
 */
treeNode *deleteTreeNode(treeNode *pRoot, int pID) {
    if (pRoot == NULL)
        return pRoot;

    if (pID < pRoot->doc.ID)
        pRoot->left = deleteTreeNode(pRoot->left, pID);

    else if (pID > pRoot->doc.ID)
        pRoot->right = deleteTreeNode(pRoot->right, pID);

    else {

        if (pRoot->left == NULL) {
            treeNode *temp = pRoot->right;
            free(pRoot);
            return temp;
        } else if (pRoot->right == NULL) {
            treeNode *temp = pRoot->left;
            free(pRoot);
            return temp;
        }

        treeNode *temp = getMinNode(pRoot->right);

        pRoot->doc.ID = temp->doc.ID;

        pRoot->right = deleteTreeNode(pRoot->right, temp->doc.ID);
    }
    return pRoot;
}

void storeNodes(FILE *pFile, treeNode *pRoot) {
    if (pRoot != NULL) {
        fwrite(pRoot, sizeof(treeNode), 1, pFile);
        storeNodes(pFile, pRoot->left);
        storeNodes(pFile, pRoot->right);
    }
}

/*
 * Inputs:
 *  - filename (char [])
 *  - pRoot (treeNode *)
 * Outputs:
 *  - Saves all the nodes in the tree pRoot in to the file with the name filename.
 * Restrictions:
 *  - pRoot must be a pointer to a treeNode, and pRoot must be != NULL.
 *  - filename must be a string.
 */
void writeTreeToFile(char filename[], treeNode *pRoot) {
    FILE *file;
    file = fopen(filename, "wb");
    storeNodes(file, pRoot);
    fclose(file);
}

/*
 * Inputs:
 *  - filename (char [])
 *  - pRoot (treeNode *)
 * Outputs:
 *  - Saves all the nodes in the tree pRoot in to the file with the name filename.
 * Restrictions:
 *  - pRoot must be a pointer to a treeNode, and pRoot must be != NULL.
 *  - filename must be a string.
 */
//pRoot must be passed by reference readFileToTree("string", &root)
void readFileToTree(char filename[], treeNode **pRoot) {
    treeNode *temp = (treeNode *) malloc(sizeof(treeNode));
    FILE *file;
    file = fopen(filename, "rb");

    if (file == NULL)
        return;

    while (fread(temp, sizeof(treeNode), 1, file)) {
        *pRoot = insertTree(*pRoot, temp->doc);
    }

    free(temp);
    fclose(file);
}