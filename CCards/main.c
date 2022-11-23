#include <stdio.h>
#include <string.h>
#include <locale.h> //unicode
#include <wchar.h> //unicode
#include "deck.h"
#include "card.h"
#include "player.h"

#define PLAYER_COUNT 2

// For now player.c defines players, and main accesses it
// Future - update playersInit to have parameters
extern Player players[PLAYER_COUNT]; //initialize players

const static char *RESET_COLOR = "\x1b[36m";

Card deck[DECK_SIZE];
Card *shuffled[DECK_SIZE];

int main(int argc, char **argv) {
    printf("%s",RESET_COLOR); //default color
    initCard(); // set up unicode printing
    initDeck(deck);
    shuffleDeck(shuffled, deck);
    Card *c = cutDeck(shuffled);
    printf("suit: %d, type: %d\n", c->suit, c->type);
    system("clear"); //clear console
    printf("Cut Card.\n");
    //c->hidden = 1;   // hidden==1 shows ???
    c->selected = 1; // changes card border color, 1 is red, 0 is green
    printCard(c, "\n");
    c->selected = 0; // make green for rest of deck
    printf("Deck before dealing:\n");
    printRestOfDeck(shuffled); // Printing the deck makes the cards visible
    playersInit();
    deal(shuffled, &players[0].hand,&players[1].hand,5);
    printf("%s Hand:\n", players[0].name);
    printCards(players[0].hand.cards, 0, 5);
    printf("%s Hand:\n", players[1].name);
    printCards(players[1].hand.cards, 0, 5);
    printf("Rest of deck:\n");
    printRestOfDeck(shuffled);
    printf("Draw top card from deck\n");
    printCard(draw(shuffled), "\n");
    printf("Rest of deck after draw:\n");
    printRestOfDeck(shuffled);

    printf("Some more Unicode characters\n\n");
    setlocale(LC_ALL, ""); //set up unicode printing
    int lets[] = { 0x461, 0x488, 0x489, 0x4ea, 0x4ec, 0x58d, 0x2ee3, 0x2ee4, 0x0 };
    for (int i = 0; i < sizeof(lets)/sizeof(int); i++)
        printf("%lc ", lets[i]);
    printf("\n");
    printf("%ls\n\n", lets);

    printf("War - %s vs %s \n", players[0].name, players[1].name);

    for(int i = players[0].hand.cardsInHand; i <= 7; i++) {
        players[0].hand.cards[i] = draw(shuffled);
        printf("%s draws a card from shuffled and adds it to their hand. \n", players[0].name);
        players[1].hand.cards[i] = draw(shuffled);
        printf("%s draws a card from shuffled and adds it to their hand. \n", players[1].name);

    }

    Card *battling[PLAYER_COUNT];
    printf("Lets Battle! \n \n \n");
    
    for (int i = 0; i < 7; i++) {
        battling[0] = players[0].hand.cards[i];
        battling[1] = players[1].hand.cards[i];
        printCards(battling, 0, 2);
        if (battling[0]->value > battling[1]->value) {
            printf("%s wins!\n", players[0].name);
        } else if (battling[0]->value < battling[1]->value) {
            printf("%s wins!\n", players[1].name);
        } else if (battling[0]->type > battling[1]->type){
            printf("%s wins!\n", players[0].name);
        } else if (battling[0]->type < battling[1]->type) {
            printf("%s wins!\n", players[1].name);
        } else {
            printf("Its a draw!\n");
            continue;
        }
        
    }

}
