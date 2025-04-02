#ifndef PLAYER_H  // Include guard to prevent multiple inclusions
#define PLAYER_H  

#define MAX_NAME_LENGTH 50  // Constant for name size

// Define Player struct
typedef struct player {
    char name[MAX_NAME_LENGTH];
    int balance;
} player;

// Function prototypes
void createPlayer(player *p); 
void displayPlayer(const player *p);
void updateBalance(player *p, int amount);

#endif // PLAYER_H