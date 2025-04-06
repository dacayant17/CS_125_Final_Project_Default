/*
 * File: main.c
 * Author: Preston
 * Course: CS 125
 * Assignment: Group Project
 * Date: 4/6/25
 * Refrences: CS125, Google
*/


#include <stdio.h>
#include <stdlib.h>
#include "slots.h"


/*
 * spinSlots - Simulates spinning the slot machine by randomly assigning values to each of the three slots.
 * 
 * This function uses the rand() function to generate a random number between 0 and SYMBOL_COUNT-1 
 * for each of the three slots. The values are stored in the provided array `slots`.
 *
 * @param slots: An array of 3 integers where the results of the slot machine spin will be stored.
*/
void spinSlots(int *slots) {
    //spins 3 times for each slot
    int i;
    for (i = 0; i < 3; i++) {
        slots[i] = rand() % SYMBOL_COUNT;
    }

}


/*
 * displaySlots - Displays the results of the slot machine spin.
 * 
 * This function prints the values stored in the `slots` array, showing the values of each of the 3 slots.
 *
 * @param slots: An array of 3 integers that holds the values of the slot machine after spinning.
*/
void displaySlots(int *slots) {
    printf("\nSlot 1: %d  |  Slot 2: %d  |  Slot 3: %d\n", slots[0], slots[1], slots[2]);
}


/*
 * checkWin - Checks whether the player has won by comparing the values of the three slots.
 * 
 * If all three slots have the same value, the player wins. Otherwise, the player loses.
 *
 * @param slots: An array of 3 integers that holds the values of the slot machine after spinning.
 */
void checkWin(int *slots, player *p, int *bet) {
    if (slots[0] == slots[1] && slots[1] == slots[2]) {
        printf("You win! All symbols match: %d\n", slots[0]);
        updateBalance(p, (*bet * (slots[0] + 1)));
        displayPlayer(p);
    } else {
        printf("\nSorry, you lose. Try again!\n");
    }
}


/*
 * displayHelp - Displays a help message explaining the objective of the game.
 * 
 * Provides a brief description of the game, explaining the goal to match three slot symbols.
 */
void displayHelp() {
    printf("\n----------------Welcome to the Slot Machine!---------------\n");
    printf("The goal is to match all three slot symbols (numbered 0-7).\n");
    printf("---------------------------Legend---------------------------\n");
    
    // Prints out multiplier value for each number
    int i = 0;
    for (i; i < SYMBOL_COUNT; i++) {
        printf("All (%ds): %dx multiplier\n", i, i + 1);
    }
    printf("\nSpin and good luck! \n");
}


/**
 * playSlots - Manages the slot machine game, allowing the player to interact
 *             with the game through a menu
 * 
 * This function provides a menu with 3 choices:
 * 1. Spin the slots: Calls spinSlots() to generate random values for the slots, displays the results, 
 *    and checks if the player won using checkWin().
 * 2. Help: Displays a help message using displayHelp().
 * 3. Exit: Ends the game with a farewell message.
 *
 * @param p: A pointer to the player struct, representing the player involved in the game.
 */
void playSlots(player *p) {

    int slots[3]; 
    int betAmnt;
    int choice;

    do {
        printf("\n===== Slot Machine =====\n");
        printf("1. Spin the slots\n");
        printf("2. Help\n");
        printf("3. Exit\n");
        choice = getValidInt("Enter your choice: ");

        switch(choice) {
            case 1:
                betAmnt = validateBet(p);
                updateBalance(p, -(betAmnt));
                spinSlots(slots);  
                displaySlots(slots);  
                checkWin(slots, p, &betAmnt);  
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
        return;
}