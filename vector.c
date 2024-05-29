#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

// Function to initialize a vector
void initVector(Vector *vector) {
    vector->data = (char **)malloc(10 * sizeof(char *));
    vector->size = 0;
    vector->capacity = 10;
}

// Function to push a word into the vector
void pushVector(Vector *vector, char *word) {
    if (vector->size == vector->capacity) {
        vector->capacity *= 2;
        vector->data = (char **)realloc(vector->data, vector->capacity * sizeof(char *));
    }
    vector->data[vector->size] = strdup(word);
    vector->size++;
}

// Function to free the vector
void freeVector(Vector *vector) {
    for (int i = 0; i < vector->size; i++) {
        free(vector->data[i]);
    }
    free(vector->data);
}
