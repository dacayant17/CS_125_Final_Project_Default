/*
 * File: main.c
 * Author: Preston
 * Course: CS 125
 * Assignment: Group Project
 * Date: 4/6/25
 * Refrences: CS125, Google
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