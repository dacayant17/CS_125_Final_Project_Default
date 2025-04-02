/*
Authors: Preston
Reference: CS125, Google
Todo: Error checking
*/


#include <stdio.h>
#include "player.h"
#include "main.h"
#include "../slots/slots.h"

int main() {
    /* Declaring the player variable */
    player player1;
    
    createPlayer(&player1);
    displayPlayer(&player1);

    /* Test Game */
    playSlots(&player1);

    return 0;
}