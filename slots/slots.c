#include <stdio.h>
#include <time.h>
#include "slots.h"


#define SYMBOL_COUNT 8


void spinSlots(int *slots) {
    //spins 3 times for each slot
    for (int i = 0; i < 3; i++) {
        slots[i] = rand() % SYMBOL_COUNT;
    }

}


void displaySlots(int *slots) {
    printf("Slot 1: %d  |  Slot 2: %d  |  Slot 3: %d\n", slots[0], slots[1], slots[2]);
}


void checkWin(int *slots) {
    if (slots[0] == slots[1] && slots[1] == slots[2]) {
        //going to implement more features
        printf("You win! All symbols match: %d\n", slots[0]);
    } else {
        printf("Sorry, you lose. Try again!\n");
    }
}


void displayHelp() {
    printf("Welcome to the Slot Machine!\n");
    printf("The goal is to match all three slot symbols (numbers 0-7).\n");
    printf("Spin and see if you win!\n");
}

void playSlots(Player *p) {

    int slots[3]; 

    int choice;

    do {
        printf("\n===== Slot Machine =====\n");
        printf("1. Spin the slots\n");
        printf("2. Help\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                spinSlots(slots);  
                displaySlots(slots);  
                checkWin(slots);  
                break;
            case 2:
                displayHelp();
                break;
            case 3:
                printf("Thanks for playing! Goodbye.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 3);

    return 0;
}