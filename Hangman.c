#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_ATTEMPTS 6
#define MAX_WORDS 5
#define MAX_WORD_LENGTH 20
#define TIMEOUT_SECONDS 60

void clearScreen();
void printHangman(int attempts);
void printWordStatus(const char word[], const int guessedLetters[]);

int main() {
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {"apple", "banana", "orange", "strawberry", "mango"};
    char hints[MAX_WORDS][MAX_WORD_LENGTH] = {"Gravity discovery", "Minions favourite","A citrus fruit","A sweet red fruit","The king of fruits"};
    int hintsUsed[MAX_WORDS] = {0};

    srand(time(NULL));
    int randomIndex = rand() % MAX_WORDS;

    char wordToGuess[MAX_WORD_LENGTH];
    char hintOfWord[MAX_WORD_LENGTH];
    strcpy(wordToGuess, words[randomIndex]);
    strcpy(hintOfWord, hints[randomIndex]);
    hintsUsed[randomIndex] = 1;

    int wordLength = strlen(wordToGuess);
    int guessedLetters[wordLength];
    memset(guessedLetters, 0, sizeof(guessedLetters));

    int attempts = 0;
    char guess;

    printf("Welcome to\n\n _\n| |\n| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __\n| '_  / _` | '_  / _` | '_ ` _  / _` | '_  \n| | | | (_| | | | | (_| | | | | | | (_| | | | |\n|_| |_| __,_|_| |_| __, |_| |_| |_| __,_|_| |_|\n                    __/ |\n                   |___/\nTry to guess the word with the given hint.");
    printf("\nHint: %s\n", hintOfWord);

    int timerOption;
    printf("\nSelect an option:\n1. Without Timer\n2. With Timer\n");
    scanf("%d", &timerOption);

    if (timerOption == 2) {
        printf("\nYou have 60 seconds to input each letter. Game will end if no input within the time limit.\n");
    }

    clock_t startTime, currentTime;

    while (1) {
        clearScreen();
        printHangman(attempts);
        printWordStatus(wordToGuess, guessedLetters);

        printf("\nEnter your guess: ");

        if (timerOption == 2) {
            startTime = clock();
        }

        scanf(" %c", &guess);
        guess = tolower(guess);

        if (timerOption == 2) {
            currentTime = clock();
            double elapsedSeconds = ((double)(currentTime - startTime)) / CLOCKS_PER_SEC;
            if (elapsedSeconds > TIMEOUT_SECONDS) {
                clearScreen();
                printHangman(attempts);
                printWordStatus(wordToGuess, guessedLetters, wordLength);
                printf("\nGame ended due to timeout. You did not input a letter within the time limit.\n");
                break;
            }
        }

        int found = 0;
        for (int i = 0; i < wordLength; i++) {
            if (wordToGuess[i] == guess) {
                guessedLetters[i] = 1;
                found = 1;
            }
        }

        if (!found) {
            attempts++;
        }

        int solved = 1;
        for (int i = 0; i < wordLength; i++) {
            if (!guessedLetters[i]) {
                solved = 0;
                break;
            }
        }

        if (solved) {
            clearScreen();
            printHangman(attempts);
            printWordStatus(wordToGuess, guessedLetters);
            printf("\nCongratulations! You guessed the word correctly.\n");
            break;
        }

        if (attempts >= MAX_ATTEMPTS) {
            clearScreen();
            printHangman(attempts);
            printWordStatus(wordToGuess, guessedLetters);
            printf("\nSorry, you have run out of attempts. The word was '%s'.\n", wordToGuess);
            break;
        }
    }

    printf("\nThanks for playing Hangman!\n");
    char user_input;
    printf("Enter any key to exit: ");
    scanf(" %c", &user_input);

    return 0;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHangman(int attempts) {
    switch (attempts) {
        case 0:
            printf(" -----\n");
            printf(" |   |\n");
            printf("     |\n");
            printf("     |\n");
            printf("     |\n");
            printf("     |\n");
            printf("-------\n");
            break;
        case 1:
            printf(" -----\n");
            printf(" |   |\n");
            printf(" O   |\n");
            printf("     |\n");
            printf("     |\n");
            printf("     |\n");
            printf("-------\n");
            break;
        case 2:
            printf(" -----\n");
            printf(" |   |\n");
            printf(" O   |\n");
            printf(" |   |\n");
            printf("     |\n");
            printf("     |\n");
            printf("-------\n");
            break;
        case 3:
            printf(" -----\n");
            printf(" |   |\n");
            printf(" O   |\n");
            printf("/|   |\n");
            printf("     |\n");
            printf("     |\n");
            printf("-------\n");
            break;
        case 4:
            printf(" -----\n");
            printf(" |   |\n");
            printf(" O   |\n");
            printf("/|\\ |\n");
            printf("     |\n");
            printf("     |\n");
            printf("-------\n");
            break;
        case 5:
            printf(" -----\n");
            printf(" |   |\n");
            printf(" O   |\n");
            printf("/|\\ |\n");
            printf("/    |\n");
            printf("     |\n");
            printf("-------\n");
            break;
        case 6:
            printf(" -----\n");
            printf(" |   |\n");
            printf(" O   |\n");
            printf("/|\\ |\n");
            printf("/ \\ |\n");
            printf("     |\n");
            printf("-------\n");
            break;
    }
}

void printWordStatus(const char word[], const int guessedLetters[], int wordLength) {
    printf("Word: ");
    for (int i = 0; i < wordLength; i++) {
        if (guessedLetters[i]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}
