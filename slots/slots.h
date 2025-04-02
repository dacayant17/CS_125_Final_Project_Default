#ifndef SLOTS_H
#define SLOTS_H

#include "../mainFolder/player.h"  // Correct path to import Player struct

// Function prototype for slot machine
void playSlots(player *p);
void displaySlots(int *slots);
void checkWin(int *slots, player *p);
void displayHelp();

#endif // SLOTS_H