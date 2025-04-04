/*
Authors: Preston
Reference: CS125, Google
Todo: Error checking
*/


#include <stdio.h>
#include "player.h"
#include "main.h"
#include "../slots/slots.h"


int get_valid_int(const char *prompt) {
    int num;
    int result;

    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &num);

        // Clear any extra input from the buffer
        while (getchar() != '\n');

        if (result == 1) {
            return num; // Valid input, return it
        } else {
            printf("Invalid input. Please enter a valid integer.\n");
        }
    }
}


void main_menu(player *p) {
    int choice;

    while (1 && p->balance != 0) {

        // Checking if player's balance is 0
        if (p->balance <= 0) {
            printf("Your balance is zero. You cannot play anymore.\n");
            printf("Thanks for playing! Goodbye.\n");
            return;  // Exit the program
        }

        // Main Menu
        printf("\n------------------Casino Game------------------\n");
        printf("This is a casino that contains many games\n");
        printf("1. Display player information\n");
        printf("2. Play Slots\n");
        printf("3. Play Texas Hold'em\n");
        printf("4. Exit\n");

        choice = get_valid_int("Enter your choice: ");

        switch (choice) {
            case 1:
                displayPlayer(p);  // Display player information
                break;
            case 2:
                playSlots(p);  // Call the playSlots function to play slots
                break;
            case 3:
                // You can implement the Texas Hold'em game here
                printf("Texas Hold'em functionality is coming soon!\n");
                break;
            case 4:
                printf("Thanks for playing! Goodbye.\n");
                return;  // Exit the game
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    if (p->balance == 0) {
        printf("Your balance is zero. You cannot continue playing.\n");
    }
}

int main() {
    /* Declaring the player variable */
    player player1;
    
    createPlayer(&player1);
    displayPlayer(&player1);

    main_menu(&player1);

    return 0;
}