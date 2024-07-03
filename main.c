#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

// Function prototypes
void displayScore();
void help();
void writeScore(float score, char playername[20]);

int main() {
    int countq, countr;
    int r, i;
    float score;
    char choice;
    char playername[20];
    time_t initialtime, finaltime;

    srand(time(NULL)); // Seed random number generator

    while (1) {
        system("cls || clear"); // Clear console screen

        printf("\n\t\t WELCOME TO I.Q. TEST PROGRAM\n\n");
        printf("\n\t\t-------------------------------\n");
        printf("\n\t\t Enter 'S' to start game       \n");
        printf("\n\t\t Enter 'V' to view high score  \n");
        printf("\n\t\t Enter 'H' for help            \n");
        printf("\n\t\t Enter 'Q' to quit             \n");
        printf("\n\t\t-------------------------------\n\n\t\t  ");
        choice = toupper(getchar()); // Read user choice

        switch (choice) {
            case 'V':
                displayScore();
                break;

            case 'H':
                help();
                break;

            case 'Q':
                printf("\n\nExiting the program...\n");
                exit(0);

            case 'S':
                system("cls || clear");
                printf("\n\n\n\t\t\tEnter your name...\n");
                printf("\n\t\t\t(only one word)\n\n\t\t\t");
                scanf("%19s", playername); // Limit input to 19 characters

                countq = countr = 0;
                score = 0.0f;
                initialtime = time(NULL);

                for (i = 1; i <= 5; i++) {
                    r = rand() % 23 + 1; // Generate random question number

                    // Display questions based on random number 'r'
                    switch (r) {
                        // Example questions - Replace with your own questions
                        case 1:
                            printf("\n\nWhat is the capital of France?\n");
                            printf("\nA. Paris\tB. London\nC. Berlin\tD. Rome\n");
                            countq++;

                            if (toupper(getchar()) == 'A') {
                                printf("\n\nCorrect!!!\n");
                                countr++;
                            } else {
                                printf("\n\nWrong!!! The correct answer is A. Paris\n");
                            }
                            break;

                        // Add more cases for other questions
                        // Ensure to increment 'countq' and 'countr' based on correct answers
                    }
                }

                finaltime = time(NULL);
                score = (float)countr / countq * 100 - difftime(finaltime, initialtime) / 3;

                if (score < 0) {
                    score = 0;
                }

                printf("\n\n\nYour Score: %.2f\n", score);

                if (score == 100) {
                    printf("\nEXCELLENT!!! KEEP IT UP\n");
                } else if (score >= 80 && score < 100) {
                    printf("\nVERY GOOD!!\n");
                } else if (score >= 60 && score < 80) {
                    printf("\nGOOD! BUT YOU NEED TO KNOW MORE.\n");
                } else if (score >= 40 && score < 60) {
                    printf("\nSATISFACTORY RESULT, BUT THIS MUCH IS MUCH SUFFICIENT.\n");
                } else {
                    printf("\nYOU ARE VERY POOR IN G.K., WORK HARD\n");
                }

                printf("\nNEXT PLAY?(Y/N)\n");

                if (toupper(getchar()) != 'Y') {
                    writeScore(score, playername);
                    break;
                }

                // Fall-through intentional to restart the loop on 'Y'

            default:
                printf("\n\n\t\t  Enter the right key\n\n\t\t  ");
                break;
        }
    }

    return 0;
}

void displayScore() {
    char name[20];
    float highScore;
    FILE *f;

    system("cls || clear");
    f = fopen("score.txt", "r");

    if (f == NULL) {
        printf("\n\nNo scores available yet. Be the first to play!\n");
        return;
    }

    fscanf(f, "%s %f", name, &highScore);
    printf("\n\n\t\t ");
    printf("\n\n\t\t %s has secured the Highest Score %.2f\n", name, highScore);
    printf("\n\n\t\t ");
    fclose(f);
    getchar(); // Wait for user to press Enter
}

void help() {
    system("cls || clear");

    printf("\n\n\n\tThis game is very easy to play. You'll be asked some general");
    printf("\n\n\tknowledge questions and the right answer is to be chosen among");
    printf("\n\n\tthe four options provided. Your score will be calculated at the");
    printf("\n\n\tend. Remember that the quicker you give answer, the higher");
    printf("\n\n\tscore you will secure. If you secure the highest score, your score");
    printf("\n\n\twill be recorded. So BEST OF LUCK.\n\n");

    getchar(); // Wait for user to press Enter
}

void writeScore(float score, char playername[20]) {
    float highScore;
    char name[20];
    FILE *f;

    system("cls || clear");
    f = fopen("score.txt", "r");

    if (f == NULL) {
        // Create new file if it doesn't exist
        f = fopen("score.txt", "w");
        fprintf(f, "%s %.2f", playername, score);
        fclose(f);
        return;
    }

    fscanf(f, "%s %f", name, &highScore);
    if (score >= highScore) {
        fclose(f);
        f = fopen("score.txt", "w");
        fprintf(f, "%s %.2f", playername, score);
    }

    fclose(f);
}
