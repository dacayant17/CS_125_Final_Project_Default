
/*
 * Author: Timothy Dacayanan
 * Course: CS 125
 * Assignment: Final Project- Texas Hold Em
 * Date: 3/11/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Card {
  char suit;
  int rank;
  int count;
} card;

typedef struct Person {
  card c1;
  card c2;
  int bal;
} Player;

void printCard(char suit, char rank) {
  printf("%c", suit);
  switch (rank) {
    case (14):
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

int ascending(const void* a,const void* b) {
  return *(int*)a - *(int*)b;
}


int handStrength(card c1, card c2, card c3, card c4, card c5) {
  int flush = 1;
  int pairs = 0;
  int threekind = 0;
  int fourkind = 0;
  int straight = 0;
  int royal = 0;
  int nums[5] = {c1.rank, c2.rank, c3.rank, c4.rank, c5.rank};
  int record[5][2] = {0};
  char suits[5] = {c1.suit, c2.suit, c3.suit, c4.suit, c5.suit};
  int i, j;
  
  //Sort values
  qsort(nums, 5, sizeof(int), ascending);

  //Flush check
  char check = suits[0];
  for (i = 1; i < 5; i++) {
    if (check != suits[i]) {
      flush = 0;
    }
  }
  //0 = not a flush, 1 = is a flush

  //Create record of number of times a rank is repeated.
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if (record[j][0] == nums[i]) {
        record[j][1]++;
        break;
      }
      else if (record[j][0] == 0) {
        record[j][0] = nums[i];
        record[j][1]++;
        break;
      }
    }
  }

  printf("%i %i %i %i %i \n", record[0][0], record[1][0], record[2][0], record[3][0], record[4][0]);
  printf("%i %i %i %i %i \n", record[0][1], record[1][1], record[2][1], record[3][1], record[4][1]);

  //Pair check
  for (i = 0; i < 5; i++) {
    if (record[i][1] == 2) {
      pairs++;
    }
  }

  //Three of a kind check
  for (i = 0; i < 5; i++) {
    if (record[i][1] == 3) {
      threekind++;
    }
  }

  //Four of a kind check
  for (i = 0; i < 5; i++) {
    if (record[i][1] == 4) {
      fourkind++;
    }
  }

  //Straight Check

  if (record[4][0] != 0) {
    if ((record[4][0] - record[0][0]) == 4) {
      straight++;
    }
  }

  //Royal Check

}

//int main(int argc, char *argv[]) {
int main() {
  //int balance = atoi(argv[1]);
  //char name[50] = atoi(argv[2]);
  int balance = 1000;
  int i, choice = 1;
  char suits[4] = {'D', 'H', 'S', 'C'};
  card deck[52];
  card community[5];
  srand(time(NULL));

  for (i = 1; i < 13; i++) {
    deck[i].suit = suits[0];
    deck[(i + 13)].suit = suits[1];
    deck[(i + 26)].suit = suits[2];
    deck[(i + 39)].suit = suits[3];
    deck[i].rank = (i + 2);
    deck[(i + 13)].rank = (i + 2);
    deck[(i + 26)].rank = (i + 2);
    deck[(i + 39)].rank = (i + 2);
  }

  for (i = 0; i < 52; i++) {
    deck[i].count = 0;
  }
  
  handStrength(deck[1], deck[14], deck[27], deck[40], deck[31]);



  //while (choice) {
    
  //}
}