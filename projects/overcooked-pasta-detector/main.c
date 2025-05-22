#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

int main(void) {
    char menuInput;
    int troubleCounter = 0;
    bool timerIsSet = false;
    bool waterIsBoiledAway = false;
    bool pastaIsMushy = false;
    bool smokeIsComing = false;

    printf("Hey, Welcome!\n");
    printf("Shall we start? (Y/N)");
    scanf(" %c", &menuInput);

    if (toupper(menuInput) == 'Y') {
        // Timer set?
        printf("Is timer set? (Y/N): ");
        scanf(" %c", &menuInput);
        if (toupper(menuInput) == 'Y') {
            timerIsSet = true;
        } else if (toupper(menuInput) == 'N') {
            timerIsSet = false;
            troubleCounter++;
        } else {
            printf("Invalid input!\n");
        }

        // Water boiled away?
        printf("Is water boiled away? (Y/N): ");
        scanf(" %c", &menuInput);
        if (toupper(menuInput) == 'Y') {
            waterIsBoiledAway = true;
            troubleCounter++;
        } else if (toupper(menuInput) == 'N') {
            waterIsBoiledAway = false;
        } else {
            printf("Invalid input!\n");
        }

        // Pasta mushy?
        printf("Is pasta gone mushy? (Y/N): ");
        scanf(" %c", &menuInput);
        if (toupper(menuInput) == 'Y') {
            pastaIsMushy = true;
            troubleCounter++;
        } else if (toupper(menuInput) == 'N') {
            pastaIsMushy = false;
        } else {
            printf("Invalid input!\n");
        }

        // Smoke?
        printf("Is any smoke coming from the stove? (Y/N): ");
        scanf(" %c", &menuInput);
        if (toupper(menuInput) == 'Y') {
            smokeIsComing = true;
            troubleCounter++;
        } else if (toupper(menuInput) == 'N') {
            smokeIsComing = false;
        } else {
            printf("Invalid input!\n");
        }

        if (troubleCounter >= 2) {
            printf("OVERCOOKED PASTA EMERGENCY!!!\n");
        } else {
            printf("Congratulations! You held it together in the kitchen and made the perfect pasta! Enjoy it!!!\n");
        }
    } else if (toupper(menuInput) == 'N') {
        printf("Alright, maybe next time!\n");
    } else {
        printf("Invalid input!\n");
    }

    return 0;
}
