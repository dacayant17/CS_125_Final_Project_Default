/*
 * File: main.c
 * Author: Preston
 * Course: CS 125
 * Assignment: Group Project
 * Date: 4/6/25
 * Refrences: CS125, Google
*/

 #include <stdio.h>
 #include "player.h"
 #include "main.h"
 #include "../slots/slots.h"
 #include "../roulette/roulette.h"
 #include "../cardGames/blackjack.h"
 #include "../cardGames/texas.h"
 
 /**
  * @brief Prompts the user for a valid integer input.
  *
  * Continuously asks the user to input a valid integer until it receives one.
  * Clears the input buffer to avoid leftover characters.
  *
  * @param prompt The message to display to the user before requesting input.
  * @return A valid integer entered by the user.
  */
 int getValidInt(const char *prompt) {
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
 
 /**
  * @brief Displays the main menu of the casino game and handles user choices.
  *
  * This function shows the main game options, allowing the player to select
  * different games or perform actions such as saving data or exiting the game.
  * The menu repeats until the player chooses to exit or runs out of balance.
  *
  * @param p A pointer to the player struct containing their information (e.g., balance).
  */
 void mainMenu(player *p) {
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
         printf("4. Play Black jack\n");
         printf("5. Play Roulette\n");
         printf("6. Save data\n");
         printf("7. Exit\n");
 
         choice = getValidInt("Enter your choice: ");
 
         // Switch statement for menu options
         switch (choice) {
             case 1:
                 displayPlayer(p);  // Display player information
                 break;
             case 2:
                 playSlots(p);  // Call the playSlots function to play slots
                 break;
             case 3:
                 // Play Texas Hold'em game (passing player's balance and name)
                 p->balance = playTexasHoldEm(p->balance, p->name);
                 break;
             case 4:
                 playBlackjack(p);  // Call the blackjack game function
                 break;
             case 5:
                 playRoulette(p);  // Call the roulette game function
                 break;
             case 6:
                 saveData(p);  // Save player data
                 break;
             case 7:
                 printf("Thanks for playing! Goodbye.\n");
                 return;  // Exit the game
             default:
                 printf("Invalid choice. Please try again.\n");
         }
     }
 
     // If the player has zero balance, notify them
     if (p->balance == 0) {
         printf("Your balance is zero. You cannot continue playing.\n");
     }
 }
 
 /**
  * @brief Displays the player setup menu and handles user choices for loading or creating a player.
  *
  * Prompts the user to either load existing player data or create a new player.
  * Allows one of the two actions and exits once the player setup is complete.
  *
  * @param p A pointer to the player struct that will be initialized or loaded.
  */
 void playerMenu(player *p) {
     int choice;
 
     while (1) {
         printf("1. Load player information\n");
         printf("2. Create Player\n");
 
         choice = getValidInt("Enter your choice: ");
 
         // Switch statement for player setup actions
         switch (choice) {
             case 1:
                 loadData(p);  // Load player data from file
                 break;
             case 2:
                 createPlayer(p);  // Create a new player
                 break;
             default:
                 printf("Invalid choice. Please try again.\n");
                 continue;
         }
 
         // Exit loop after a valid choice
         break;
     }
 
     // Print confirmation of player setup completion
     printf("Player setup complete.\n");
 }
 
 /**
  * @brief Main function for the program.
  *
  * This is the entry point of the program. It initializes a player, sets up
  * the player information through the `playerMenu` function, and then shows
  * the main game menu using the `mainMenu` function.
  *
  * @return 0 on successful execution.
  */
 int main() {
     /* Declaring the player variable */
     player player1;
     
     // Set up the player
     playerMenu(&player1);
     // Start the main game menu
     mainMenu(&player1);
 
     return 0;
 }
 
