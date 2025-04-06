/*
Authors: Preston
Reference: CS125, Google
Todo: Error checking
*/


#include <stdio.h>
#include <stdlib.h>
#include "player.h"

const char* INPUT_FORMAT = " %d, %49[^\n]";


/*
 * createPlayer - Initializes a new player by setting their name and balance.
 * 
 * Prompts the user to input the player's name and balance, then
 * stores them in the player struct.
 *
 * @param p: A pointer to a player struct where the player's information will be stored.
*/
void createPlayer(player *p) {
    printf("Enter player name: ");
    scanf("%49s", p->name);  // Reads player name

    printf("Enter initial balance: ");
    scanf("%d", &p->balance);  // Reads player's balance
}


/*
 * displayPlayer - Displays the player's name and current balance.
 * 
 * Prints the player's information (name and balance) to the console.
 *
 * @param p: A pointer to the player struct.
*/
void displayPlayer(const player *p) {
    printf("\nPlayer Info:\n");
    printf("Name: %s\n", p->name);
    printf("Balance: $%d\n", p->balance);
}


/*
 * updateBalance - Updates the player's balance by a given amount.
 * 
 * Modifies the player's balance by adding the specified amount.
 *
 * @param p: A pointer to the player struct whose balance will be updated.
 * @param amount: The amount to be added to the player's balance (can be positive or negative).
*/
void updateBalance(player *p, int amount) {
    p->balance += amount;
}


/*
 * validateBet - Validates the bet amount entered by the player.
 * 
 * This function ensures that the player has enough money to place the bet,
 * and that the bet is a positive number.
 *
 * @param p: A pointer to the player struct that holds the player's balance.
 * @return: The validated bet amount.
 */
int validateBet(player *p) {
    int bet;

    // Loop until a valid bet is entered
    do {
        // Use the getValidInt function to get a valid input
        bet = getValidInt("Enter bet amount: ");

        if (p->balance == 0) {
            printf("Your balance is zero. You cannot continue playing.\n");
            exit(0);
        }

        // Check if the bet is valid (greater than 0 and not more than the current balance)
        if (bet <= 0) {
            printf("Bet amount must be greater than 0. Please try again.\n");
        } else if (bet > p->balance) {
            printf("You cannot bet more than your balance of $%d. Please try again.\n", p->balance);
        } else {
            break;  // Valid bet
        }

    } while (bet <= 0 || bet > p->balance);

    return bet;  // Return the valid bet amount
}


void loadData(player *p) {
    FILE* file = fopen("saved_data.txt", "r");
    if (file == NULL)
    {
        printf("No saved data found.\n");
        createPlayer(p); // Function that initializes a new player
        return;
    }

    if (fscanf(file, INPUT_FORMAT, &p->balance, p->name) != 2)
    {
        printf("Saved data is corrupted or unreadable.\n");
        createPlayer(p);
    }
    else
    {
        printf("Welcome back, %s! Your balance is $%d.\n", p->name, p->balance);
    }

    fclose(file);
}


void saveData(player *p) {
    FILE* file = fopen("saved_data.txt", "w");
    if (file == NULL)
    {
        printf("Error: Could not save data.\n");
        return;
    }

    // Write balance and name in the same format used in load_data
    fprintf(file, "%d, %s\n", p->balance, p->name);

    fclose(file);
    printf("Game data saved for %s with balance $%d.\n", p->name, p->balance);
}
