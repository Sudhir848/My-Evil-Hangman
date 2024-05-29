#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

// Function to create a new AVL node
AVLNode* createNode(char *word) {
    AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));
    node->word = strdup(word);
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// Function to get the height of a node
int height(AVLNode *node) {
    return node ? node->height : 0;
}

// Function to get the balance factor of a node
int getBalance(AVLNode *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Function to right rotate a subtree rooted with y
AVLNode* rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// Function to left rotate a subtree rooted with x
AVLNode* leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

// Function to insert a word into the AVL tree
AVLNode* insert(AVLNode *node, char *word) {
    if (!node) return createNode(word);

    if (strcmp(word, node->word) < 0)
        node->left = insert(node->left, word);
    else if (strcmp(word, node->word) > 0)
        node->right = insert(node->right, word);
    else
        return node;

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && strcmp(word, node->left->word) < 0)
        return rightRotate(node);

    if (balance < -1 && strcmp(word, node->right->word) > 0)
        return leftRotate(node);

    if (balance > 1 && strcmp(word, node->left->word) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && strcmp(word, node->right->word) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to find the minimum value node in the tree
AVLNode* minValueNode(AVLNode *node) {
    AVLNode *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node from the AVL tree
AVLNode* deleteNode(AVLNode *root, char *word) {
    if (!root) return root;

    if (strcmp(word, root->word) < 0)
        root->left = deleteNode(root->left, word);
    else if (strcmp(word, root->word) > 0)
        root->right = deleteNode(root->right, word);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode *temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp->word);
            free(temp);
        } else {
            AVLNode *temp = minValueNode(root->right);

            free(root->word);
            root->word = strdup(temp->word);

            root->right = deleteNode(root->right, temp->word);
        }
    }

    if (!root) return root;

    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to do in-order traversal of the AVL tree
void inOrderTraversal(AVLNode *root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%s ", root->word);
        inOrderTraversal(root->right);
    }
}

// Function to free the AVL tree
void freeAVLTree(AVLNode *root) {
    if (root != NULL) {
        freeAVLTree(root->left);
        freeAVLTree(root->right);
        free(root->word);
        free(root);
    }
}
