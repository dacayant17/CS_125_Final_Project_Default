#ifndef PLAYER_H  // Include guard to prevent multiple inclusions
#define PLAYER_H  

#define MAX_NAME_LENGTH 50  // Constant for name size

// Define Player struct
typedef struct {
    char name[MAX_NAME_LENGTH];
    float balance;
} Player;

// Function prototypes
void createPlayer(Player *p); 
void displayPlayer(const Player *p);
void updateBalance(Player *p, float amount);

#endif // PLAYER_H