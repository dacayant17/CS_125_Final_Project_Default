/*
Authors: Preston
Reference: CS125, Google
Todo: Error checking
*/


#ifndef ROULETT_H
#define ROULETT_H

#include "../mainFolder/player.h"  // Correct path to import Player struct
#include "../mainFolder/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct spinres{
    int numres;
    char colorres[5];
}spinres;

void printTable();
int betamount(int totbal,int bettimes,int *bet, int *run);
spinres spin();
void playRoulette(player *p);
void spinTable();
#endif
