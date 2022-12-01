#include <string.h>
#include "player.h"

const char *const COMPUTER_NAME = "Computer";
char *const PLAYER_NAME = "Player";
Player players[PLAYER_COUNT]; //initialize players
Table table; //Initializes the table

//makes all cards visible
void revealCards(Hand* hand ) {
    for (char i = 0; i < hand->cardsInHand; i++) {
        hand->cards[i]->hidden = false;
    }
}

//makes all cards in hand hidden
void hideCards(Hand* hand ) {
    for (char i = 0; i < hand->cardsInHand; i++) {
        hand->cards[i]->hidden = true;
    }
}

void playersInit(char *names, int numPlayers, int startingBalance) {
    for (int i = 0; i < numPlayers; i++) {
        players[i].balance = startingBalance;
        strcpy(players[i].name, names);
    }
}
