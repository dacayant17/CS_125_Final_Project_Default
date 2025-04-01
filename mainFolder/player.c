#include <stdio.h>
#include <time.h>


#define MAX_NAME_LENGTH 50


typedef struct {
    char name[MAX_NAME_LENGTH];
    int balance;
} player;


void createPlayer(player *p) {
    printf("Enter player name: ");
    scanf("%49s", p->name);  // Read player name (prevent buffer overflow)

    printf("Enter initial balance: ");
    scanf("%f", &p->balance);  // Read player's balance
}


void displayPlayer(const player *p) {
    printf("\nPlayer Info:\n");
    printf("Name: %s\n", p->name);
    printf("Balance: $%.2f\n", p->balance);
}


void updateBalance(player *p, float amount) {
    p->balance += amount;
}