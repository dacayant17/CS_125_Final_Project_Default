/*
 * File: texas.c
 * Author: Timothy Dacayanan
 * Course: CS 125
 * Assignment: Final Project- Texas Hold Em
 * Date: 4/6/25
 * Refrences: 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "texas.h"


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

int playTexasHoldEm(int balance, char name[50]) {
  char nameList[20][10] = {"Amy", "Bernard", "Chris", "Dan", "Ed", "Fred", "George", "Han", "James",
                           "Kyle", "Liam", "Mary", "Noah", "Owen", "Phil", "Ryan", "Sam", "Tom", 
                           "Wayne", "Zach"};
  int bigBlind = (balance / 50);
  int smallBlind = (bigBlind / 2);
  int currentPlayer;
  int pot = 0;
  int currentBet = 0;
  int num;
  int raised = 1;
  int choice = 1;
  int i, check, odds, temp, action;
  char suits[4] = {'D', 'H', 'S', 'C'};
  card deck[52];
  card comCards[5];
  Player players[5];
  srand(time(NULL));

  //Create deck
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
    deck[i].count = 1;
  }

  //Create Other Players
  for (i = 0; i < 4; i++) {
    odds = 15;
    strcpy(((players[i]).name), ((nameList[(rand() % 20)])));
    players[i].betChance = (rand() % (odds + 1));
    players[i].foldChance = (rand() % (odds + 1));
    players[i].callChance = (100 - (players[i].betChance + players[i].foldChance) );
    players[i].isPlayer = 0;
    players[i].isFolded = 0;
    players[i].commitedBal = 0;
    players[i].bal = 0;
    players[i].isAllIn = 0;
  }

  //Create Player
  strcpy(((players[4]).name), (name));
  players[4].bal = balance;
  players[4].isPlayer = 1;
  players[4].isFolded = 0;
  players[4].commitedBal = 0;
  players[4].isAllIn = 0;

  //Begin Game
  printf("Welcome to Texas Hold Em\n");
  printf("The goal of the game is to have the highest ranking hand\n");
  printf("The game begins now\n");

  while (choice) {
    //Game Set Up
    pot = 0;
    for (i = 0; i < 5; i++) {
      players[i].isFolded = 0;
      players[i].commitedBal = 0;
      players[i].isAllIn = 0;
    }
    //Small Blind
    players[0].commitedBal = smallBlind;
    printf("%s bets %i\n", players[0].name, smallBlind);
    //Big Blind
    players[1].commitedBal = bigBlind;
    printf("%s bets %i\n", players[1].name,bigBlind);

    //Assign Cards
    for (i = 0; i < 5; i++) {
      num = (rand() % 52);
      temp = 1;
      while (temp) {
        if (deck[num].count) {
          players[i].c1.suit = deck[num].suit;
          players[i].c1.rank = deck[num].rank;
          deck[num].count--;
          temp = 0;
        } else {
          num = (rand() % 52);
        }
      }
      num = (rand() % 52);
      temp = 1;
      while (temp) {
        if (deck[num].count) {
          (((players[i]).c2).suit) = ((deck[num]).suit);
          (((players[i]).c2).rank) = ((deck[num]).rank);
          deck[num].count--;
          temp = 0;
        } else {
          num = (rand() % 52);
        }
      }
    }

    for (i = 0; i < 5; i++) {
      num = (rand() % 52);
      temp = 1;
      while (temp) {
        if (deck[num].count) {
          (comCards[i].suit) = ((deck[num]).suit);
          (comCards[i].rank) = ((deck[num]).rank);
          deck[num].count--;
          temp = 0;
        } else {
          num = (rand() % 52);
        }
      }
    }


    //Cards are Passed Out
    //Set Up
    currentPlayer = 2;
    currentBet = bigBlind;

    //Display Player's Cards
    printf("Hello %s, you were dealt: \n", name);
    printCard(players[4].c1.suit, players[4].c1.rank);
    printCard(players[4].c2.suit, players[4].c2.rank);
    printf("Your balance: %i\n", players[4].bal);

    //Begin Play
    while (raised != currentPlayer) {
      printf("\n");
      if (!(players[currentPlayer].isFolded)) {
        if (players[currentPlayer].isPlayer) {
          if (!(players[currentPlayer].isAllIn)) {
            //Select Player Action
            action = 4;
            while ((action > 2) || (action < 0)) {
              action = getValidInt("Please Select an Option:\n(0) Bet\n(1) Call\n(2) Fold\n");
            }
          } else {
            action = 3;
          }
        } else {
          action = 4;
          //Select AI Action
          temp = (rand() % 100 + 1);
          if (players[currentPlayer].commitedBal > (bigBlind * 8)) {
            action = 1;
          } else if (temp < players[currentPlayer].betChance) {
            action = 0;
          } else if ((temp - players[currentPlayer].betChance) < players[currentPlayer].foldChance) {
            action = 2;
          } else {
            action = 1;
          }
        }

        //Perform Action
        switch (action) {
          case (0):
            //Bet
            if (players[currentPlayer].isPlayer) {
              if (!(players[currentPlayer].isAllIn)) {
                //Player Bet
                temp = 0;
                while ((temp < (currentBet * 2)) || (temp == 0)) {
                  temp = getValidInt("Please Enter Your Bet: ");
                }
                if (temp > players[currentPlayer].bal) {
                  printf("%s is all in\n", players[currentPlayer].name);
                  players[currentPlayer].isAllIn = 1;
                  currentBet = players[currentPlayer].bal;
                  players[currentPlayer].commitedBal = currentBet;
                  raised = currentPlayer;
                } else {
                  currentBet = temp;
                  players[currentPlayer].commitedBal = currentBet;
                  raised = currentPlayer;
                  printf("%s bet %i\n", players[currentPlayer].name, currentBet);
                }
              }
            } else {
              //AI Bet
              temp = (bigBlind + (((rand() % 2) + 1) * currentBet));
              currentBet = temp;
              raised = currentPlayer;
              players[currentPlayer].commitedBal = currentBet;
              printf("%s bet %i\n", players[currentPlayer].name, currentBet);
            }
            break;
          case (1):
            //Call
            if (players[currentPlayer].isPlayer) {
              if (players[currentPlayer].bal < currentBet) {
                players[currentPlayer].commitedBal = players[currentPlayer].bal;
                printf("%s is all in\n", players[currentPlayer].name);
                players[currentPlayer].isAllIn = 1;
              } else {
                players[currentPlayer].commitedBal = currentBet;
                printf("%s called\n", players[currentPlayer].name);
              }
            } else {
              players[currentPlayer].commitedBal = currentBet;
              printf("%s called\n", players[currentPlayer].name);
            }
            break;
          case (2):
            //Fold
            players[currentPlayer].isFolded = 1;
            printf("%s folded\n", players[currentPlayer].name);
            break;
          case (3):
            printf("%s is all in\n", players[currentPlayer].name);
            break;
          default:
            break;
        }
      }
      if (currentPlayer < 5) {
        currentPlayer++;
      } else {
        currentPlayer = 0;
      }
    }
    
    //First Round Final Actions
    printf("\n");
    for (i = 0; i < 5; i++) {
      if (players[i].isPlayer) {
        players[i].bal -= players[i].commitedBal;
      }
      pot += players[i].commitedBal;
      players[i].commitedBal = 0;
    }
    printf("\n");

    //The Flop
    //First 3 Community Cards are Shown
    printf("Community Cards: \n");
    for (i = 0; i < 3; i++) {
      printCard(comCards[i].suit, comCards[i].rank);
    }
    printf("\n");

    //Display Own Cards Again
    printf("Your Cards:\n", name);
    printCard(players[4].c1.suit, players[4].c1.rank);
    printCard(players[4].c2.suit, players[4].c2.rank);
    printf("Your balance: %i\n", players[4].bal);
    printf("\n");

    //Set Up
    currentBet = 0;
    raised = 0;
    currentPlayer = 0;
    check = 0;

    //Begin Flop
    while ((raised != currentPlayer) || (!check)) {
      printf("\n");
      check = 1;
      if (!(players[currentPlayer].isFolded)) {
        if (players[currentPlayer].isPlayer) {
          if (!(players[currentPlayer].isAllIn)) {
            //Select Player Action
            action = 4;
            while ((action > 2) || (action < 0)) {
              action = getValidInt("Please Select an Option:\n(0) Bet\n(1) Call\n(2) Fold\n");
            }
          } else {
            action = 3;
          }
        } else {
          action = 4;
          //Select AI Action
          temp = (rand() % 100 + 1);
          if (players[currentPlayer].commitedBal > (bigBlind * 8)) {
            action = 1;
          } else if (temp < players[currentPlayer].betChance) {
            action = 0;
          } else if ((temp - players[currentPlayer].betChance) < players[currentPlayer].foldChance) {
            action = 2;
          } else {
            action = 1;
          }
        }

        //Perform Action
        switch (action) {
          case (0):
            //Bet
            if (players[currentPlayer].isPlayer) {
              if (!(players[currentPlayer].isAllIn)) {
                //Player Bet
                temp = 0;
                while ((temp < (currentBet * 2)) || (temp == 0)) {
                  temp = getValidInt("Please Enter Your Bet: ");
                }
                if (temp > players[currentPlayer].bal) {
                  printf("%s is all in\n", players[currentPlayer].name);
                  players[currentPlayer].isAllIn = 1;
                  currentBet = players[currentPlayer].bal;
                  players[currentPlayer].commitedBal = currentBet;
                  raised = currentPlayer;
                } else {
                  currentBet = temp;
                  players[currentPlayer].commitedBal = currentBet;
                  raised = currentPlayer;
                  printf("%s bet %i\n", players[currentPlayer].name, currentBet);
                }
              }
            } else {
              //AI Bet
              temp = (bigBlind + (((rand() % 2) + 1) * currentBet));
              currentBet = temp;
              raised = currentPlayer;
              players[currentPlayer].commitedBal = currentBet;
              printf("%s bet %i\n", players[currentPlayer].name, currentBet);
            }
            break;
          case (1):
            //Call
            if (players[currentPlayer].isPlayer) {
              if (players[currentPlayer].bal < currentBet) {
                players[currentPlayer].commitedBal = players[currentPlayer].bal;
                printf("%s is all in\n", players[currentPlayer].name);
                players[currentPlayer].isAllIn = 1;
              } else {
                players[currentPlayer].commitedBal = currentBet;
                printf("%s called\n", players[currentPlayer].name);
              }
            } else {
              players[currentPlayer].commitedBal = currentBet;
              printf("%s called\n", players[currentPlayer].name);
            }
            break;
          case (2):
            //Fold
            players[currentPlayer].isFolded = 1;
            printf("%s folded\n", players[currentPlayer].name);
            break;
          case (3):
            printf("%s is all in\n", players[currentPlayer].name);
            break;
          default:
            break;
        }
      }
      if (currentPlayer < 5) {
        currentPlayer++;
      } else {
        currentPlayer = 0;
      }
    }

    //Flop Final Actions
    printf("\n");
    for (i = 0; i < 5; i++) {
      if (players[i].isPlayer) {
        players[i].bal -= players[i].commitedBal;
      }
      pot += players[i].commitedBal;
      players[i].commitedBal = 0;
    }
    printf("The current pot is: %i\n", pot);
    printf("\n");


    //The Turn
    //First 4 Community Cards are Shown
    printf("Community Cards: \n");
    for (i = 0; i < 4; i++) {
      printCard(comCards[i].suit, comCards[i].rank);
    }
    printf("\n");

    //Display Own Cards Again
    printf("Your Cards:\n", name);
    printCard(players[4].c1.suit, players[4].c1.rank);
    printCard(players[4].c2.suit, players[4].c2.rank);
    printf("Your balance: %i\n", players[4].bal);
    printf("\n");

    //Set Up
    currentBet = 0;
    raised = 0;
    currentPlayer = 0;
    check = 0;

    //Begin Turn
    while ((raised != currentPlayer) || (!check)) {
      printf("\n");
      check = 1;
      if (!(players[currentPlayer].isFolded)) {
        if (players[currentPlayer].isPlayer) {
          if (!(players[currentPlayer].isAllIn)) {
            //Select Player Action
            action = 4;
            while ((action > 2) || (action < 0)) {
              action = getValidInt("Please Select an Option:\n(0) Bet\n(1) Call\n(2) Fold\n");
            }
          } else {
            action = 3;
          }
        } else {
          action = 4;
          //Select AI Action
          temp = (rand() % 100 + 1);
          if (players[currentPlayer].commitedBal > (bigBlind * 8)) {
            action = 1;
          } else if (temp < players[currentPlayer].betChance) {
            action = 0;
          } else if ((temp - players[currentPlayer].betChance) < players[currentPlayer].foldChance) {
            action = 2;
          } else {
            action = 1;
          }
        }

        //Perform Action
        switch (action) {
          case (0):
            //Bet
            if (players[currentPlayer].isPlayer) {
              if (!(players[currentPlayer].isAllIn)) {
                //Player Bet
                temp = 0;
                while ((temp < (currentBet * 2)) || (temp == 0)) {
                  temp = getValidInt("Please Enter Your Bet: ");
                }
                if (temp > players[currentPlayer].bal) {
                  printf("%s is all in\n", players[currentPlayer].name);
                  players[currentPlayer].isAllIn = 1;
                  currentBet = players[currentPlayer].bal;
                  players[currentPlayer].commitedBal = currentBet;
                  raised = currentPlayer;
                } else {
                  currentBet = temp;
                  players[currentPlayer].commitedBal = currentBet;
                  raised = currentPlayer;
                  printf("%s bet %i\n", players[currentPlayer].name, currentBet);
                }
              }
            } else {
              //AI Bet
              temp = (bigBlind + (((rand() % 2) + 1) * currentBet));
              currentBet = temp;
              raised = currentPlayer;
              players[currentPlayer].commitedBal = currentBet;
              printf("%s bet %i\n", players[currentPlayer].name, currentBet);
            }
            break;
          case (1):
            //Call
            if (players[currentPlayer].isPlayer) {
              if (players[currentPlayer].bal < currentBet) {
                players[currentPlayer].commitedBal = players[currentPlayer].bal;
                printf("%s is all in\n", players[currentPlayer].name);
                players[currentPlayer].isAllIn = 1;
              } else {
                players[currentPlayer].commitedBal = currentBet;
                printf("%s called\n", players[currentPlayer].name);
              }
            } else {
              players[currentPlayer].commitedBal = currentBet;
              printf("%s called\n", players[currentPlayer].name);
            }
            break;
          case (2):
            //Fold
            players[currentPlayer].isFolded = 1;
            printf("%s folded\n", players[currentPlayer].name);
            break;
          case (3):
            printf("%s is all in\n", players[currentPlayer].name);
            break;
          default:
            break;
        }
      }
      if (currentPlayer < 5) {
        currentPlayer++;
      } else {
        currentPlayer = 0;
      }
    }

    //Turn Final Actions
    printf("\n");
    for (i = 0; i < 5; i++) {
      if (players[i].isPlayer) {
        players[i].bal -= players[i].commitedBal;
      }
      pot += players[i].commitedBal;
      players[i].commitedBal = 0;
    }
    printf("The current pot is: %i\n", pot);
    printf("\n");


    //The River
    //All Community Cards are Shown
    printf("Community Cards: \n");
    for (i = 0; i < 5; i++) {
      printCard(comCards[i].suit, comCards[i].rank);
    }
    printf("\n");

    //Display Own Cards Again
    printf("Your Cards:\n", name);
    printCard(players[4].c1.suit, players[4].c1.rank);
    printCard(players[4].c2.suit, players[4].c2.rank);
    printf("Your balance: %i\n", players[4].bal);
    printf("\n");

    //Set Up
    currentBet = 0;
    raised = 0;
    currentPlayer = 0;
    check = 0;

    //Begin River
    while ((raised != currentPlayer) || (!check)) {
      printf("\n");
      check = 1;
      if (!(players[currentPlayer].isFolded)) {
        if (players[currentPlayer].isPlayer) {
          if (!(players[currentPlayer].isAllIn)) {
            //Select Player Action
            action = 4;
            while ((action > 2) || (action < 0)) {
              action = getValidInt("Please Select an Option:\n(0) Bet\n(1) Call\n(2) Fold\n");
            }
          } else {
            action = 3;
          }
        } else {
          action = 4;
          //Select AI Action
          temp = (rand() % 100 + 1);
          if (players[currentPlayer].commitedBal > (bigBlind * 8)) {
            action = 1;
          } else if (temp < players[currentPlayer].betChance) {
            action = 0;
          } else if ((temp - players[currentPlayer].betChance) < players[currentPlayer].foldChance) {
            action = 2;
          } else {
            action = 1;
          }
        }

        //Perform Action
        switch (action) {
          case (0):
            //Bet
            if (players[currentPlayer].isPlayer) {
              if (!(players[currentPlayer].isAllIn)) {
                //Player Bet
                temp = 0;
                while ((temp < (currentBet * 2)) || (temp == 0)) {
                  temp = getValidInt("Please Enter Your Bet: ");
                }
                if (temp > players[currentPlayer].bal) {
                  printf("%s is all in\n", players[currentPlayer].name);
                  players[currentPlayer].isAllIn = 1;
                  currentBet = players[currentPlayer].bal;
                  players[currentPlayer].commitedBal = currentBet;
                  raised = currentPlayer;
                } else {
                  currentBet = temp;
                  players[currentPlayer].commitedBal = currentBet;
                  raised = currentPlayer;
                  printf("%s bet %i\n", players[currentPlayer].name, currentBet);
                }
              }
            } else {
              //AI Bet
              temp =  (bigBlind + (((rand() % 2) + 1) * currentBet));
              currentBet = temp;
              raised = currentPlayer;
              players[currentPlayer].commitedBal = currentBet;
              printf("%s bet %i\n", players[currentPlayer].name, currentBet);
            }
            break;
          case (1):
            //Call
            if (players[currentPlayer].isPlayer) {
              if (players[currentPlayer].bal < currentBet) {
                players[currentPlayer].commitedBal = players[currentPlayer].bal;
                printf("%s is all in\n", players[currentPlayer].name);
                players[currentPlayer].isAllIn = 1;
              } else {
                players[currentPlayer].commitedBal = currentBet;
                printf("%s called\n", players[currentPlayer].name);
              }
            } else {
              players[currentPlayer].commitedBal = currentBet;
              printf("%s called\n", players[currentPlayer].name);
            }
            break;
          case (2):
            //Fold
            players[currentPlayer].isFolded = 1;
            printf("%s folded\n", players[currentPlayer].name);
            break;
          case (3):
            printf("%s is all in\n", players[currentPlayer].name);
            break;
          default:
            break;
        }
      }
      if (currentPlayer < 5) {
        currentPlayer++;
      } else {
        currentPlayer = 0;
      }
    }

    //River Final Actions
    printf("\n");
    for (i = 0; i < 5; i++) {
      if (players[i].isPlayer) {
        players[i].bal -= players[i].commitedBal;
      }
      pot += players[i].commitedBal;
      players[i].commitedBal = 0;
    }
    printf("The current pot is: %i\n", pot);
    printf("\n");

    //Showdown
    //All Cards Shown
    printf("Community Cards: \n");
    for (i = 0; i < 5; i++) {
      printCard(comCards[i].suit, comCards[i].rank);
    }
    printf("\n");

    for (i = 0; i < 5; i++) {
      printf("%s:\n", players[i].name);
      printCard(players[i].c1.suit, players[i].c1.rank);
      printCard(players[i].c2.suit, players[i].c2.rank);
    }
    printf("\n");

    //Winner is calulated
    temp = 0;
    raised = 0;
    int winner = 0;
    for (i = 0; i < 5; i++) {
      if (!(players[i].isFolded)) {
        temp = strongestHand(comCards[0], comCards[1], comCards[2], comCards[3], comCards[4], 
                             players[i].c1, players[i].c2);
        if (temp > raised) {
          raised = temp;
          winner = i;
        }
      } 
    }
    printf("\n");

    printf("%s wins!\n", players[winner].name);
    if (players[winner].isPlayer) {
      players[winner].bal += pot;
    }
    printf("\n");
    printf("Your current balance: %i\n", players[4].bal);
    printf("\n");

    //End of Game
    if (players[4].bal == 0) {
      choice = 0;
    } else {
      num = 2;
      while ((num > 1) || (num < 0)) {
        num = getValidInt("Would you like to continue?\n (1) Yes\n (0) No\n");
      }
      if (num == 1) {
        choice = 1;
      }
      else {
        choice = 0;
      }
     printf("\n");
    }
  }
  return (players[4].bal);
}