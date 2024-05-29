#ifndef HANGMAN_H
#define HANGMAN_H

#define MAX_WORD_LENGTH 50

#include "avl.h"
#include "vector.h"

void readWordsFromFile(const char *filename, AVLNode **root);
void findWordsOfLength(AVLNode *root, int length, Vector *vector);
void updatePattern(char *currentPattern, const char *chosenWord, char guessedLetter);
int isGameWon(const char *currentPattern);
int filterWords(Vector *vector, char guessedLetter, char *currentPattern);  // Update return type to int

#endif // HANGMAN_H
