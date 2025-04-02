
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
  int fold;
  int 
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
  int largerData = 0;
  int smallerData = 0;
  char suits[5] = {c1.suit, c2.suit, c3.suit, c4.suit, c5.suit};
  int i, j;
  int score = 0;
  
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

  //Pair check
  for (i = 0; i < 5; i++) {
    if (record[i][1] == 2) {
      pairs++;
      if (smallerData > 0) {
        largerData += record[i][0];
      }
      else {
        smallerData += record[i][0];
      }
    }
  }

  //Three of a kind check
  for (i = 0; i < 5; i++) {
    if (record[i][1] == 3) {
      threekind++;
      largerData += record[i][0];
    }
  }

  //Four of a kind check
  for (i = 0; i < 5; i++) {
    if (record[i][1] == 4) {
      fourkind++;
      largerData += record[i][0];
    }
  }

  //Straight Check

  if (record[4][0] != 0) {
    if ((record[4][0] - record[0][0]) == 4) {
      straight++;
    }
  }

  //Royal Check
  if (straight) {
    if (record[4][0] == 14) {
      straight--;
      royal++;
    }
  }

  //Royal Flush
  if (royal && flush) {
    score += 90000;
  }

  //Straight Flush
  if (straight && flush) {
    score += 80000;
    score += (record[4][0] * 100);
  }

  //Four of a Kind
  if (fourkind) {
    score += 70000;
    score += (largerData * 100);
  }

  //Full House
  if (pairs && threekind) {
    score += 60000;
    score += (largerData * 100);
    score += smallerData;
  }

  //Straight

  if (straight && !flush) {
    score += 40000;
    score += (record[4][0] * 100);
  }

  //Three of a Kind
  if (threekind && (pairs == 0)) {
    score += 30000;
    score += (largerData * 100);
  }

  //Two Pair

  if (pairs > 1) {
    score += 20000;
    score += (largerData * 100);
    score += smallerData;
  }

  //Pair
  if ((!(score > 0)) && pairs) {
    score += 10000;
    score += (smallerData * 100);
  }

  if ((!(score > 0)) && flush) {
    score += 50000;
    score += (record[4][0] * 100);
  }

  //High Card
  if (!(score > 0)) {
    score += record[4][0];
  }

  return score;
}

int strongestHand(card c1, card c2, card c3, card c4, card c5, card c6, card c7) {
  card list[7] = {c1, c2, c3, c4, c5, c6, c7};
  int largest = 0;
  int temp = 0;
  int i, j, k, l, m;

  for (i = 0; i < 3; i++) {
    for ((j = i + 1); j < 4; j++) {
      for ((k = j + 1); k < 5; k++) {
        for ((l = k + 1); l < 6; l++) {
          for ((m = l + 1); m < 7; m++) {
            temp = handStrength(list[i], list[j], list[k], list[l], list[m]);
            if (temp > largest) {
              largest = temp;
            }
          }
        }
      }
    }
  }

  return largest;
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

  for (i = 0; i < 13; i++) {
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

  handStrength(deck[9], deck[10], deck[11], deck[12], deck[8]);//Royal Flush
  handStrength(deck[0], deck[1], deck[2], deck[3], deck[4]);//Straight Flush
  handStrength(deck[1], deck[14], deck[27], deck[40], deck[31]);//Four of a Kind
  handStrength(deck[1], deck[14], deck[27], deck[41], deck[28]); //Full House
  handStrength(deck[0], deck[1], deck[2], deck[5], deck[6]);//Flush
  handStrength(deck[0], deck[1], deck[2], deck[3], deck[17]);//Straight
  handStrength(deck[1], deck[14], deck[27], deck[2], deck[32]);//Three of a Kind
  handStrength(deck[1], deck[14], deck[28], deck[41], deck[32]); //Two pair
  handStrength(deck[1], deck[2], deck[15], deck[31], deck[32]); //Pair
  handStrength(deck[1], deck[2], deck[3], deck[31], deck[32]); //High Card

  

  //while (choice) {
    
  //}
}