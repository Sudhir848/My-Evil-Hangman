#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    char **data;
    int size;
    int capacity;
} Vector;

void initVector(Vector *vector);
void pushVector(Vector *vector, char *word);
void freeVector(Vector *vector);

#endif // VECTOR_H
