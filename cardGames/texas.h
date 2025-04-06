/*
 * File: texas.c
 * Author: Timothy Dacayanan
 * Course: CS 125
 * Assignment: Final Project- Texas Hold Em
 * Date: 4/6/25
 * Refrences: 
*/


#ifndef TEXAS_H
#define TEXAS_H

#include "../mainFolder/player.h"  // correct path to import player struct
#include "../mainFolder/main.h"

//Structs
typedef struct Card {
  char suit;
  int rank;
  int count;
} card;

typedef struct Person {
  card c1;
  card c2;
  int bal;
  int commitedBal;
  int foldChance;
  int betChance;
  int callChance;
  char name[50];
  int isPlayer;
  int isFolded;
  int isAllIn;
} Player;


// Function Prototypes
void printCard(char suit, char rank);
int ascending(const void* a,const void* b);
int handStrength(card c1, card c2, card c3, card c4, card c5);
int strongestHand(card c1, card c2, card c3, card c4, card c5, card c6, card c7);
int playTexasHoldEm(int balance, char name[50]);
#endif 
