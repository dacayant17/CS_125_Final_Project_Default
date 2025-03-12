
/*
 * Author: Timothy Dacayanan
 * Course: CS 125
 * Assignment: Final Project- Texas Hold Em
 * Date: 3/11/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Card {
  char suit;
  int rank;
  int inPlay;
} card;

typedef struct Person {
  card c1;
  card c2;
} Player;

void printCard(char suit, char rank) {
  printf("%c", suit);
  switch (rank) {
    case (1):
      printf("A\n");
      break;
    case (11):
      printf("J\n");
      break;
    case (12):
      printf("Q\n");
      break;
    case (13):
      printf("K\n");
      break;
    default:
      printf("%i\n", rank);
      break;
  }
}

//int main(int argc, char *argv[]) {
int main() {
  //int in1 = atoi(argv[1]);
  int in1 = 1000;
  int i;
  char suits[4] = {'D', 'H', 'S', 'C'};
  card deck[52];
  card community[5];

  for (i = 0; i < 13; i++) {
    deck[i].suit = suits[0];
    deck[(i + 13)].suit = suits[1];
    deck[(i + 26)].suit = suits[2];
    deck[(i + 39)].suit = suits[3];
    deck[i].rank = (i + 1);
    deck[(i + 13)].rank = (i + 1);
    deck[(i + 26)].rank = (i + 1);
    deck[(i + 39)].rank = (i + 1);
  }

  for (i = 0; i < 52; i++) {
    deck[i].inPlay = 0;
  }

  
}