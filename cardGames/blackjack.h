#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "../mainFolder/player.h"  // correct path to import player struct
#include "../mainFolder/main.h"

// global defines
#define CARD_NUM 13 // number of unique cards in a deck
#define DECKS 3 // number of decks in play

// structs
typedef struct cards {
  char rank[CARD_NUM]; // the rank of the card (A, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K)
  int value[CARD_NUM]; // the value of the card (A is 11, 2-10 is card value, face cards are 10)
  int count[CARD_NUM]; // how many of the card is left
}Cards;

// function prototypes
void playBlackjack(player *p);
void shuffleDeck(Cards* input);
int drawCard(Cards* deck, int* handVal, int* handAce);
void playerTurn(Cards* deck, int* playerVal, int* playerAce, int* dealerVal, int* dealerAce, player* p, int* bet);
void dealerTurn(Cards* deck, int* dealerVal, int* dealerAce);
void resolve(int* playerVal, int* dealerVal, player* p, int* bet);

#endif 
