#include <stdio.h>
#include "player.h"

int main() {
    Player player;
    
    createPlayer(&player);
    displayPlayer(&player);

    return 0;
}