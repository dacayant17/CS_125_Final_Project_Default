/*
Authors: Preston
Reference: CS125, Google
Todo: Error checking
*/


#include <stdio.h>
#include <time.h>
#include "player.h"


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