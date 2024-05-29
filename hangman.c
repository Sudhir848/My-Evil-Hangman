#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "vector.h"
#include "hangman.h"

// Function to read words from a file and insert into AVL tree
void readWordsFromFile(const char *filename, AVLNode **root) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        *root = insert(*root, word);
    }

    fclose(file);
}

// Function to find words of specific length and push into a vector
void findWordsOfLength(AVLNode *root, int length, Vector *vector) {
    if (!root) return;
    if (strlen(root->word) == length)
        pushVector(vector, root->word);
    findWordsOfLength(root->left, length, vector);
    findWordsOfLength(root->right, length, vector);
}

// Function to update the current pattern based on the guessed letter
void updatePattern(char *currentPattern, const char *chosenWord, char guessedLetter) {
    for (int i = 0; i < strlen(chosenWord); i++) {
        if (chosenWord[i] == guessedLetter) {
            currentPattern[i] = guessedLetter;
        }
    }
}

// Function to check if the game is won
int isGameWon(const char *currentPattern) {
    for (int i = 0; i < strlen(currentPattern); i++) {
        if (currentPattern[i] == '_') {
            return 0;
        }
    }
    return 1;
}

// Function to filter words based on the guessed letter and current pattern
int filterWords(Vector *vector, char guessedLetter, char *currentPattern) {
    Vector newVector;
    initVector(&newVector);
    int letterFound = 0;

    for (int i = 0; i < vector->size; i++) {
        int matchesPattern = 1;
        int containsGuessedLetter = 0;

        for (int j = 0; j < strlen(vector->data[i]); j++) {
            if (currentPattern[j] != '_' && currentPattern[j] != vector->data[i][j]) {
                matchesPattern = 0;
                break;
            }
            if (vector->data[i][j] == guessedLetter) {
                containsGuessedLetter = 1;
            }
        }

        if (matchesPattern) {
            pushVector(&newVector, vector->data[i]);
        }

        if (containsGuessedLetter) {
            letterFound = 1;
        }
    }

    freeVector(vector);
    *vector = newVector;

    return letterFound;
}
