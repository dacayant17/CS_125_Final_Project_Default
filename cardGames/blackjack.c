#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "blackjack.h"

/*
File: blackjack.c
Author: Michael Higley
Assignment: Group Project
Date: 4/6/25
Refrences: Google (for sprintf)
*/

/*
TODO:
- Maybe implement min/standard bets
  -- Must have a factor of 5 or so
- More comments to explain?
*/


void shuffleDeck(Cards* input) {
  // resets the deck
  int i;
  for (i = 0; i < CARD_NUM; i++) {
    input->count[i] = 4 * DECKS; // fill the count of each card with 4 times the number of decks
    
    // assigning card values
    // is ace
    if (i == 0) {
      input->value[i] = 11;
      input->rank[i] = 'A';
    }
    
    // 10 value cards
    else if (i >= 9) {
      input->value[i] = 10;
      
      if (i == 9) {
        input->rank[i] = 'T';
      }
      
      else if (i == 10) {
        input->rank[i] = 'J';
      }
      
      else if (i == 11) {
        input->rank[i] = 'Q';
      }
      
      else {
        input->rank[i] = 'K';
      }
    }
    
    // numbered cards
    else {
      input->value[i] = i+1; // +1 because the card ranks are 1 ahead of i
      sprintf(&(input->rank[i]), "%d", i+1); // turns an integer into a char/str
    }
  }
}


int drawCard(Cards* deck, int* handVal, int* handAce) {
  int cardDrawn, i = 0;
  do {
    cardDrawn = rand() % CARD_NUM; // draw 1 of 13 cards
    
    // i counts how many times a card has attempted to be drawn, if above 10, then just take whatever card is given even if it has a zero/negative count
    // this is to prevent extended periods of invalid card drawing, which shouldn't be much of an issue, but just in case.
    i++; 
  } while (deck->count[cardDrawn] <= 0 || i > 10); // loop if there is no cards of the value left
  deck->count[cardDrawn]--; // take a card out of the count
  
  *handVal += deck->value[cardDrawn];
  
  if (deck->rank[cardDrawn] == 'A') {
    (*handAce)++; // add ace for overflow
  }
  
  return cardDrawn;
}


void playerTurn(Cards* deck, int* playerVal, int* playerAce, int* dealerVal, int* dealerAce, player* p, int* bet) {
  int cardDrawn, i, playerPlay, playerCardNum, canDouble;
  
  // draw the first dealer card
  cardDrawn = drawCard(deck, dealerVal, dealerAce);
  
  printf("\nThe dealer's face up card is a %c.\n", deck->rank[cardDrawn]); // tell the player the dealer's card
  sleep(1);
  
  // player's cards
  for (i = 0; i < 2; i++) {
    playerCardNum++;
    cardDrawn = drawCard(deck, playerVal, playerAce);
    
    printf("You recieve a %c.\n", deck->rank[cardDrawn]);
    sleep(1);
  }
  
  // check if player drew 2 aces
  if (*playerVal > 21 && *playerAce > 0) {
    *playerVal -= 10; // make an ace valued 1
    (*playerAce)--; // disallow the ace from overflowing again
  }
  
  // if player doesn't have blackjack (10 value and a Ace)
  if (*playerVal < 21) {
    // offer double the first time
    printf("\nYou have a hand value of %d, what would you like to do?\n 1. Hit\n 2. Stand\n 3. Double\n", *playerVal, *playerAce);
  }
  
  // otherwise, tell the player they automatically stand
  else {
    printf("\nYou have blackjack and automatically stand.\n");
  }
  
  while (playerPlay != 2 && playerPlay != 3 && *playerVal < 21) {
    if (scanf("%d", &playerPlay) == 0) {
      while (getchar() != '\n');
      playerPlay = 0;
    }
    
    switch (playerPlay) {
      case 1:
        playerCardNum++;
        cardDrawn = drawCard(deck, playerVal, playerAce);
        
        printf("You recieve a %c.\n", deck->rank[cardDrawn]);
        sleep(1);
        break;
        
      case 2:
        printf("You have chosen to Stand.\n");
        break;
        
      case 3:
        // double checks
        if (playerCardNum > 2) {
          // player tries to double after 1st turn
          printf("Cannot Double now\n");
          playerPlay = 1;
        }
        
        else if (*bet > p->balance) {
          // player doesn't have enough chips to double
          printf("Not enough balance to Double\n");
          playerPlay = 1;
        }
        
        else {
          // player can double
          updateBalance(p, -(*playerBet));
          *bet += *bet;
          
          printf("You have doubled you bet.\n");
          sleep(1);
          
          playerCardNum++;
          
          cardDrawn = drawCard(deck, playerVal, playerAce);
          
          printf("You recieve a %c.\n", deck->rank[cardDrawn]);
          sleep(1);
        }
        break;
        
      default:
        printf("Invalid choice.\n");
        break;
      }
      
      // check for overflow w/ aces
      if (*playerVal > 21 && *playerAce > 0) {
        *playerVal -= 10; // make the ace valued 1
        *playerAce--; // disallow the ace from overflowing again
      }
      
      if (playerPlay != 2 && playerPlay != 3 && *playerVal < 21) 
      {
        // if going to play another round, then display choices w/o double
        printf("\nYou have a hand value of %d, what would you like to do?\n 1. Hit\n 2. Stand\n", *playerVal);
      }
  }
  
  if (*playerVal > 21) {
    printf("\nYou bust with a value of %d.\n", *playerVal);
  }
}


void dealerTurn(Cards* deck, int* dealerVal, int* dealerAce) {
  int cardDrawn;
  
  // generate dealer's hidden card
  cardDrawn = drawCard(deck, dealerVal, dealerAce);
  
  printf("\nThe dealer flips over their hidden card to show a %c, for a total value of %d\n", deck->rank[cardDrawn], *dealerVal);
  sleep(2);
  
  // check for dealer double aces
  if (*dealerVal > 21 && *dealerAce > 0) {
    *dealerVal -= 10; // make the ace valued 1
    *dealerAce--; // disallow the ace from overflowing again
  }
  
  // if dealer has less than 17, hit
  while (*dealerVal < 17) {
    cardDrawn = drawCard(deck, dealerVal, dealerAce);
    
    printf("\nThe dealer takes another card and draws a %c.\n", deck->rank[cardDrawn]);
    sleep(1);
    
    // overflow for dealer aces
    if (*dealerVal > 21 && *dealerAce > 0) {
      *dealerVal -= 10; // make the ace valued 1
      *dealerAce--; // disallow the ace from overflowing again
    }
  }
  
  if (*dealerVal <= 21) {
    printf("\nDealer stands with a value of %d.\n", *dealerVal);
  }
  else {
    printf("\nDealer busts with a value of %d.\n", *dealerVal);
  }
  
  sleep(1);
}


void resolve(int* playerVal, int* dealerVal, int* chips, int* bet) {
  /* 
  various checks for wins/loss/ties
  win - player recieves double bet
  loss - no change in balance, already removed bet
  tie - player recieves bet back
  */
  
  // double bust, tie 
  if (*playerVal > 21 && *dealerVal > 21) {
    printf("\nDealer and player bust. Bet returns to player.\n");
    
    *chips += *bet;
  }
  
  // dealer bust, win
  else if (*dealerVal > 21) {
    printf("\nDealer bust. Player wins.\n");
    
    // double the bet
    *bet += *bet;
     
    // give back to the player
    updateBalance(p, *playerBet); 
  }
  
  // player bust, loss
  else if (*playerVal > 21) {
    printf("\nPlayer bust. Dealer wins.\n");
  }
  
  // dealer has higher value, loss
  else if (*playerVal < *dealerVal) {
    printf("\nDealer has higher value. Dealer wins.\n");
  }
  
  // player has higher value, win
  else if (*playerVal > *dealerVal) {
    printf("\nPlayer has higher value. Player wins.\n");
    *bet += *bet;
    
    updateBalance(p, *playerBet);
  }
  
  // same value, tie
  else if (*playerVal == *dealerVal) {
    printf("\nDealer and player tie. Bet returns to player.\n");
    
    updateBalance(p, *playerBet);;
  }
  
  // backup check, shouldn't trigger, considered a tie
  else {
    printf("\nCannot resolve. Bet returns to player.\n");
    
    updateBalance(p, *playerBet);
  }
  
  sleep(1);
}


void playBlackjack(player p*) {
  Cards deck;
  shuffleDeck(&deck); // create and populate the deck
  
  int i, run, totalCards;
  int menuChoice = 0;
  
  int playerValue;
  int playerAces;
  int playerBet;
  
  int dealerValue;
  int dealerAces;
  
  srand(time(0));
  
  while (menuChoice != 3) {
    printf("\nWelcome. You have %d balance. \nWhat would you like to do?\n 1 to play \n 2 to see instructions \n 3 to exit \n", p->balance);
    
    if (scanf("%d", &menuChoice) == 0) {
      while (getchar() != '\n');
      menuChoice = 0;
    }
    
    switch(menuChoice) {
      case 1:
        printf("Starting game\n");
        run = 1;
        while (run == 1) {
          // reset game stats
          playerValue = 0;
          playerAces = 0;
          dealerValue = 0;
          dealerAces = 0;
          totalCards = 0;
          
          // if there are less than 50 cards, shuffle the deck
          for (i = 0; i < CARD_NUM; i++) {
            totalCards += deck.count[i];
          }
          
          if (totalCards < 50) {
            printf("\nThe deck has been shuffled.\n");
            shuffleDeck(&deck);
          }
          
          // if player has chips, go as usual
          if (playerChips > 0) {
            // checks the players bet
            playerBet = validateBet(p);
            updateBalance(p, -(playerBet));
            
            playerTurn(&deck, &playerValue, &playerAces, &dealerValue, &dealerAces, p, &playerBet); 
            
            dealerTurn(&deck, &dealerValue, &dealerAces);
            
            resolve(&playerValue, &dealerValue, p, &playerBet);
            
            // if player has balance, allow to play again
            if (playerChips > 0) {
              printf("\nYou have %d chips. Do you want to play again? \n(1 for yes, 2 for no)\n", playerChips);
              if (scanf("%d", &run) == 0) {
                while (getchar() != '\n');
                run = 0;
                // leaving it so that 1 is NEEDED to be typed to play just to prevent edge cases of infinite play loops
              } 
            }
          }
          
          // shouldn't reach here, but automatically exits run loops if out of chips
          if (playerChips <= 0) {
            printf("You don't have enough chips to play.\n");
            run = 0;
          }
        }
        break;
      
      case 2:
        printf(" --- Instructions for Blackjack ---\n");
        printf("The goal of the game is to make the closest value hand to 21 as possible without going over. If the player or dealer goes over, they \"bust\" and immediatly lose.\n");
        printf("Cards are valued as follows. 2 - 10 are their face value. Face cards (J, Q, K) are worth 10. Ace (A) is worth 11 or 1 (whichever allows for a higher score without going over).\n");
        printf("The game starts with the player and dealer being dealt a hand of two cards each. The player can see both of their cards and one of the dealer's cards.\n");
        printf("The player has three choices.\n - \"Hit\" to recieve another card.\n - \"Stand\" to end their turn.\n");
        printf(" - \"Double\" to double their bet, recieve another card, and end their turn. (You cannot Double after Hitting)\n");
        printf("The dealer with take their turn after the player stands or busts. The dealer will always hit until reaching 17 or above and then stand.\n");
        printf("Whoever has the higher score wins. If the player wins, they recieve double their bet back. If the dealer wins, the player loses their bet. If there is a tie (same value or both bust), then the player keeps their bet.\n");
        sleep(5);
        break;
      
      case 3:
        printf("Goodbye!\n");
        sleep(1);
        break;
      
      default:
        printf("Invalid choice\n");
        break;
    }
  }
}