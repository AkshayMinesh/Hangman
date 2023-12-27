#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

#define MAX_ATTEMPTS 6
#define MAX_WORDS 5
#define MAX_WORD_LENGTH 20

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
    time_t start_time, current_time;

    printf("Welcome to\n\n _\n| |\n| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __\n| '_  / _` | '_  / _` | '_ ` _  / _` | '_  \n| | | | (_| | | | | (_| | | | | | | (_| | | | |\n|_| |_| __,_|_| |_| __, |_| |_| |_| __,_|_| |_|\n                    __/ |\n                   |___/\nTry to guess the word with the given hint.");
    printf("\nHint: %s\n", hintOfWord);

    while (1) {
        clearScreen();
        printHangman(attempts);
        printWordStatus(wordToGuess, guessedLetters);

        printf("\nEnter your guess (you have 1 minute): ");

        // Start the timer
        time_t start_time, current_time;
        time(&start_time);

        // Loop until a valid input or 1 minute elapses
        while (1) {
            // Check the timer
            time(&current_time);
            double elapsed_time = difftime(current_time, start_time);
            if (elapsed_time >= 60.0) {
                printf("\nTime out! You lost the game.\n");
                return 0;  // exit the program
            }

            // Prompt for user input
            printf("Enter your guess: ");
            if (scanf(" %c", &guess) == 1) {
                guess = tolower(guess);
                break; // Exit the loop if a valid input is received
            }

            // Sleep for a short duration to avoid high CPU usage
            usleep(100000); // Sleep for 0.1 seconds (100,000 microseconds)
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
    system("clear");
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

void printWordStatus(const char word[], const int guessedLetters[]) {
    printf("Word: ");
    for (int i = 0; i < strlen(word); i++) {
        if (guessedLetters[i]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}
