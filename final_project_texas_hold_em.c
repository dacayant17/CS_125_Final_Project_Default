
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
  int bal;
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

int handStrength(card c1, card c2, card c3, card c4, card c5) {
  int flush = 0;
  int pairs = 0;
  int threekind = 0;
  int fourkind = 0;
  int straight = 0;
  int nums[5] = {c1.rank, c2.rank, c3.rank, c4.rank, c5.rank};
  int i, j, temp;
  
  //Sort nums
  for (i = 0; i < 5; i++) {
    temp = nums[i];
    for (j = i; j < 5; j++) {
      if (nums[j] > temp) {

      } 
    }
  }

}

//int main(int argc, char *argv[]) {
int main() {
  //int balance = atoi(argv[1]);
  int balance = 1000;
  int i, choice = 1;
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
  
  while (choice) {
    
  }
}