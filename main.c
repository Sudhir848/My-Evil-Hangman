#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "avl.h"
#include "vector.h"
#include "hangman.h"

int main() {
    AVLNode *root = NULL;
    readWordsFromFile("dictionary.txt", &root);

    int wordLength = 0;
    printf("Enter the length of the word: ");
    scanf("%d", &wordLength);

    Vector wordVector;
    initVector(&wordVector);
    findWordsOfLength(root, wordLength, &wordVector);

    if (wordVector.size == 0) {
        printf("No words of the specified length found.\n");
        freeAVLTree(root);
        return 1;
    }

    char currentPattern[MAX_WORD_LENGTH];
    for (int i = 0; i < wordLength; i++) {
        currentPattern[i] = '_';
    }
    currentPattern[wordLength] = '\0';

    int guessesRemaining = 7;
    char guessedLetters[26];
    int guessedCount = 0;

    while (guessesRemaining > 0) {
        printf("Current pattern: %s\n", currentPattern);
        printf("Guesses remaining: %d\n", guessesRemaining);
        printf("Guessed letters: ");
        for (int i = 0; i < guessedCount; i++) {
            printf("%c ", guessedLetters[i]);
        }
        printf("\n");

        char guess;
        printf("Enter a letter to guess: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (!isalpha(guess)) {
            printf("Invalid input. Please enter a letter.\n");
            continue;
        }

        int alreadyGuessed = 0;
        for (int i = 0; i < guessedCount; i++) {
            if (guessedLetters[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }

        if (alreadyGuessed) {
            printf("You already guessed that letter. Try again.\n");
            continue;
        }

        guessedLetters[guessedCount] = guess;
        guessedCount++;

        printf("Guessed letter is '%c'\n", guess);

        int letterFound = filterWords(&wordVector, guess, currentPattern);

        if (!letterFound) {
            printf("Hangman perspective: Letter '%c' not found in any word.\n", guess);
            guessesRemaining--;
        } else {
            printf("Hangman perspective: Letter '%c' found in one or more words.\n", guess);
        }

        updatePattern(currentPattern, wordVector.data[0], guess);

        if (isGameWon(currentPattern)) {
            printf("Congratulations! :) You guessed the word: %s\n", currentPattern);
            break;
        }
    }

    if (guessesRemaining == 0) {
        printf("Sorry! :( You ran out of guesses. The right word was: %s\n", wordVector.data[0]);
    }

    freeVector(&wordVector);
    freeAVLTree(root);

    return 0;
}
