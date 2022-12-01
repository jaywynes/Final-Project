#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <stdlib.h>
#include <unistd.h>

#define NAME_LENGTH 10 //# char permissible in a player name
#define HAND_SIZE 2 // max cards in hand
#define COMMUNITY_SIZE 5 // max cards dealt to table
//#define ENTER 
#define PLAYER_COUNT 2


typedef struct {
    Card *cards[HAND_SIZE]; //the cards the hand holds
    char cardsInHand; //number of cards in a hand
} Hand;

typedef struct {
    Card *communityCards[COMMUNITY_SIZE]; //Number of cards possible in community
    char cardsOnTable; //number of cards on the table
} CommunityCards;

typedef struct {
    CommunityCards board;
} Table;

typedef struct{
    char name[NAME_LENGTH];
    Hand hand; //array of card "slots" (ptrs), & points
    char selectedCard; //selected card index
    unsigned char balance; //current balance of your bank
} Player;

void playersInit(char *names, int numPlayers, int startingBalance);

#endif
