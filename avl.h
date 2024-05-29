#ifndef AVL_H
#define AVL_H

typedef struct AVLNode {
    char *word;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

AVLNode* createNode(char *word);
AVLNode* insert(AVLNode *node, char *word);
AVLNode* deleteNode(AVLNode *root, char *word);
void inOrderTraversal(AVLNode *root);
void freeAVLTree(AVLNode *root);

#endif // AVL_H
