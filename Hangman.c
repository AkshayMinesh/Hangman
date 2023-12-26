#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRIES 6
#define MAX_WORD_LENGTH 20

void drawHangman(int tries);
void printWord(char word[], char guessed[]);

int main() {
    char words[][MAX_WORD_LENGTH] = {"hangman", "programming", "computer", "science", "algorithm", "keyboard"};
    srand(time(NULL));

    // Random word slection
    int randomIndex = rand() % (sizeof(words) / sizeof(words[0]));
    char chosenWord[MAX_WORD_LENGTH];
    strcpy(chosenWord, words[randomIndex]);
  
    int wordLength = strlen(chosenWord);
    char guessed[wordLength];
    memset(guessed, '_', wordLength);
    int tries = 0;
    char guess;

    printf("Welcome to Hangman!\n");

    while (tries < MAX_TRIES) {
        printf("\n");
        drawHangman(tries);
        printWord(chosenWord, guessed);

        // Get user input
        printf("\nEnter a letter: ");
        scanf(" %c", &guess);

        // Check if guessed letter is in the word
        int found = 0;
        for (int i = 0; i < wordLength; i++) {
            if (chosenWord[i] == guess) {
                guessed[i] = guess;
                found = 1;
            }
        }

        // check if game is won
        if (strcmp(chosenWord, guessed) == 0) {
            printf("\nCongratulations! You guessed the word: %s\n", chosenWord);
            break;
        }

        // if guessed letter not in the word, increment tries
        if (!found) {
            tries++;
        }
    }

    // Check if the game is lost
    if (tries == MAX_TRIES) {
        printf("\nSorry, you ran out of tries. The correct word was: %s\n", chosenWord);
    }

    return 0;
}

void drawHangman(int tries) {
    printf("  ____\n");
    printf(" |    |\n");

    switch (tries) {
        case 0:
            printf(" |\n |\n |\n |\n");
            break;
        case 1:
            printf(" |    O\n |\n |\n |\n");
            break;
        case 2:
            printf(" |    O\n |    |\n |\n |\n");
            break;
        case 3:
            printf(" |    O\n |   /|\n |\n |\n");
            break;
        case 4:
            printf(" |    O\n |   /|\\\n |\n |\n");
            break;
        case 5:
            printf(" |    O\n |   /|\\\n |   /\n |\n");
            break;
        case 6:
            printf(" |    O\n |   /|\\\n |   / \\\n |\n");
            break;
    }

    printf(" |\n");
    printf("_______\n");
}

void printWord(char word[], char guessed[]) {
    printf("Word: ");
    for (int i = 0; i < strlen(word); i++) {
        printf("%c ", guessed[i]);
    }
    printf("\n");
}
