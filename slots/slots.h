/*
Authors: Preston
Reference: CS125, Google
Todo: Error checking
*/


#ifndef SLOTS_H
#define SLOTS_H

#include "../mainFolder/player.h"  // Correct path to import Player struct
#include "../mainFolder/main.h"

#define SYMBOL_COUNT 8

// Function prototype for slot machine
void playSlots(player *p);
void displaySlots(int *slots);
void checkWin(int *slots, player *p, int *bet);
void displayHelp();

#endif // SLOTS_H