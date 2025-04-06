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
#include "player.h"

const char* INPUT_FORMAT = " %d, %49[^\n]";


/*
 * createPlayer - Prompts the user to enter a player's name and initial balance.
 * 
 * This function initializes a new player by reading their name and starting
 * balance from the user and storing it in the player struct.
 *
 * @param p: A pointer to a player struct where the player's information will be stored.
 */
void createPlayer(player *p) {
    printf("Enter player name: ");
    scanf("%49s", p->name);  // Reads player name (up to 49 characters)

    printf("Enter initial balance: ");
    scanf("%d", &p->balance);  // Reads player's balance
}

/*
 * displayPlayer - Displays the player's information.
 * 
 * Prints the player's name and current balance to the console.
 *
 * @param p: A pointer to the player struct.
 */
void displayPlayer(const player *p) {
    printf("\nPlayer Info:\n");
    printf("Name: %s\n", p->name);
    printf("Balance: $%d\n", p->balance);
}

/*
 * updateBalance - Modifies the player's balance by a specified amount.
 * 
 * This function adds or subtracts an amount from the player's balance.
 *
 * @param p: A pointer to the player struct.
 * @param amount: The amount to update the balance by (can be positive or negative).
 */
void updateBalance(player *p, int amount) {
    p->balance += amount;
}

/*
 * validateBet - Validates the player's bet amount.
 * 
 * Prompts the player for a bet, ensures it is a valid positive number and
 * does not exceed their current balance.
 *
 * @param p: A pointer to the player struct containing balance information.
 * @return: The validated bet amount.
 */
int validateBet(player *p) {
    int bet;

    do {
        bet = getValidInt("Enter bet amount: ");

        if (p->balance == 0) {
            printf("Your balance is zero. You cannot continue playing.\n");
            exit(0);
        }

        if (bet <= 0) {
            printf("Bet amount must be greater than 0. Please try again.\n");
        } else if (bet > p->balance) {
            printf("You cannot bet more than your balance of $%d. Please try again.\n", p->balance);
        } else {
            break;
        }

    } while (bet <= 0 || bet > p->balance);

    return bet;
}

/*
 * loadData - Loads player data from a file if available.
 * 
 * Attempts to read saved player data from "saved_data.txt". If no file exists or
 * the data is corrupted, it falls back to creating a new player.
 *
 * @param p: A pointer to the player struct where the loaded data will be stored.
 */
void loadData(player *p) {
    FILE* file = fopen("saved_data.txt", "r");
    if (file == NULL) {
        printf("No saved data found.\n");
        createPlayer(p); // Prompt user for new player info
        return;
    }

    if (fscanf(file, INPUT_FORMAT, &p->balance, p->name) != 2) {
        printf("Saved data is corrupted or unreadable.\n");
        createPlayer(p);
    } else {
        printf("Welcome back, %s! Your balance is $%d.\n", p->name, p->balance);
    }

    fclose(file);
}

/*
 * saveData - Saves the current player data to a file.
 * 
 * Writes the player's balance and name to "saved_data.txt" to preserve progress
 * between game sessions.
 *
 * @param p: A pointer to the player struct containing the data to be saved.
 */
void saveData(player *p) {
    FILE* file = fopen("saved_data.txt", "w");
    if (file == NULL) {
        printf("Error: Could not save data.\n");
        return;
    }

    fprintf(file, "%d, %s\n", p->balance, p->name);
    fclose(file);

    printf("Game data saved for %s with balance $%d.\n", p->name, p->balance);
}