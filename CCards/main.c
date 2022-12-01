#include <stdio.h>
#include <string.h>
#include <locale.h> //unicode
#include <wchar.h> //unicode
#include "deck.h"
#include "card.h"
#include "player.h"
#include "action.h"

#define PLAYER_COUNT 2

// For now player.c defines players, and main accesses it
// Future - update playersInit to have parameters
extern Player players[PLAYER_COUNT]; //initialize players
extern Table table; // initializes the table

const static char *RESET_COLOR = "\x1b[36m";

Card deck[DECK_SIZE];
Card *shuffled[DECK_SIZE];

int main(int argc, char **argv) {

    int pot = 0;
    int ante = 10;
    char names[2];
    char name;
    int startingBal;
    bool cont = true;
    bool P1canAdvance = false;
    bool P2canAdvance = false;


    printf("Welcome to Texas Holdem! \n \n");
    sleep(5);
    printf("Let's get into the game! \n");
    printf("%s",RESET_COLOR); //default color
    initCard(); // set up unicode printing
    initDeck(deck);
    shuffleDeck(shuffled, deck);
    Card *c = cutDeck(shuffled);
    system("clear"); //clear the console
    
    for (int i = 0; i<PLAYER_COUNT; i++) {
    printf("Player %d, what is your name? \n", i);
    scanf("%s", name);
    names[i] = name;
    printf("\n");
    }
    sleep(2);
    printf("What is the starting balance for each player? \n");
    scanf("%d", startingBal);
    printf("\n");
    playersInit(*names, PLAYER_COUNT, startingBal);
    sleep(2);

    printf("Let's get into the game!");

    while(cont) {
            restart:
            deal(shuffled, &players[0].hand, &players[1].hand, 2);
            printf("It is time to ante up! \n");
            players[0].balance = players[0].balance-ante;
            players[1].balance = players[1].balance-ante;
            pot = pot+20;
            printf("There is currently %d in the pot \n", pot);
            sleep(3);

            preflop:
            for (int i = 0; i < PLAYER_COUNT; i++) {

            printf("Please pass the laptop to Player %d \n", i+1);
            sleep(5);
            printf("Your current bank size is: %d \n", players[i].balance);
            sleep(3);
            printf("Dealing! \n");
            printCards(players[i].hand.cards, 0, 2);
            sleep(2);
            printf("The current pot size is %d \n", pot);

            turn_action decision = &actionOnTurn(0);
            if (decision.action == BET || decision.action == RAISE) {
                pot = pot + decision.bet;
                players[i].balance = players[i].balance - decision.bet;
            } else if (decision.action == FOLD) {
                goto restart;
            } else if (decision.action == CALL) {
                pot = pot + decision.bet;
                if (i == 0) {
                    P1canAdvance = true;
                } else {
                    P2canAdvance = true;
                }
            }
            system("clear");
            
            if (P1canAdvance && P2canAdvance) {
                goto flop;
            } else {
                goto preflop;
            }
        }

        flop:
        P1canAdvance = false;
        P2canAdvance = false;
        sleep(3);
        printf("The current pot is %d, now onto the flop! \n", pot);
        sleep(3);
        dealToTable(shuffled, table.board.communityCards, 3);
        printCards(table.board.communityCards, 0, 3);
        printf("Now, let the next street begin!");

        for (int i = 0; i < PLAYER_COUNT; i++) {
            printf("Please pass the laptop to Player %d \n", i+1);
            sleep(5);
            printf("Your current bank size is: %d \n", players[i].balance);
            sleep(3);
            printCards(players[i].hand.cards, 0, 2);
            sleep(2);
            printf("The current pot size is %d \n", pot);

            turn_action decision = &actionOnTurn(0);
            if (decision.action == BET || decision.action == RAISE) {
                pot = pot + decision.bet;
                players[i].balance = players[i].balance - decision.bet;
            } else if (decision.action == FOLD) {
                goto restart;
            } else if (decision.action == CALL) {
                pot = pot + decision.bet;
                if (i == 0) {
                    P1canAdvance = true;
                } else {
                    P2canAdvance = true;
                }
            } else if (decision.action = CHECK) {
                if (i == 0) {
                    P1canAdvance = true;
                } else {
                    P2canAdvance = true;
                }
            }
            system("clear");
                    
            if (P1canAdvance && P2canAdvance) {
                goto turn;
            } else {
                goto flop;
            }
        }
        turn:
        P1canAdvance = false;
        P2canAdvance = false;
        sleep(3);
        printf("The current pot is %d, now onto the turn! \n", pot);
        sleep(3);
        dealToTable(shuffled, table.board.communityCards, 3);
        printCards(table.board.communityCards, 0, 3);
        printf("Now, let the next street begin!");

        for (int i = 0; i < PLAYER_COUNT; i++) {
            printf("Please pass the laptop to Player %d \n", i+1);
            sleep(5);
            printf("Your current bank size is: %d \n", players[i].balance);
            sleep(3);
            printCards(players[i].hand.cards, 0, 2);
            sleep(2);
            printf("The current pot size is %d \n", pot);

            turn_action decision = &actionOnTurn(0);
            if (decision.action == BET || decision.action == RAISE) {
                pot = pot + decision.bet;
                players[i].balance = players[i].balance - decision.bet;
            } else if (decision.action == FOLD) {
                goto restart;
            } else if (decision.action == CALL) {
                pot = pot + decision.bet;
                if (i == 0) {
                    P1canAdvance = true;
                } else {
                    P2canAdvance = true;
                }
            } else if (decision.action = CHECK) {
                if (i == 0) {
                    P1canAdvance = true;
                } else {
                    P2canAdvance = true;
                }
            }
            system("clear");
                    
            if (P1canAdvance && P2canAdvance) {
                goto river;
            } else {
                goto turn;
            }
        }

            river:
        P1canAdvance = false;
        P2canAdvance = false;
        sleep(3);
        printf("The current pot is %d, now onto the river! \n", pot);
        sleep(3);
        dealToTable(shuffled, table.board.communityCards, 3);
        printCards(table.board.communityCards, 0, 3);
        printf("Now, let the next street begin!");

        for (int i = 0; i < PLAYER_COUNT; i++) {
            printf("Please pass the laptop to Player %d \n", i+1);
            sleep(5);
            printf("Your current bank size is: %d \n", players[0].balance);
            sleep(3);
            printCards(players[i].hand.cards, 0, 2);
            sleep(2);
            printf("The current pot size is %d \n", pot);

            turn_action decision = &actionOnTurn(0);
            if (decision.action == BET || decision.action == RAISE) {
                pot = pot + decision.bet;
                players[i].balance = players[i].balance - decision.bet;
            } else if (decision.action == FOLD) {
                goto restart;
            } else if (decision.action == CALL) {
                pot = pot + decision.bet;
                if (i == 0) {
                    P1canAdvance = true;
                } else {
                    P2canAdvance = true;
                }
            } else if (decision.action = CHECK) {
                if (i == 0) {
                    P1canAdvance = true;
                } else {
                    P2canAdvance = true;
                }
            }
            system("clear");
                    
            if (P1canAdvance && P2canAdvance) {
                goto showdown;
            } else {
                goto river;
            }
        }


            showdown:
        P1canAdvance = false;
        P2canAdvance = false;
        sleep(3);
        printf("Wecome to the showdown!!! \n");
        printf("This will be the last chance to place bets before you reveal your hand \n");
        printf("The current pot is %d \n", pot);
        sleep(3);
        dealToTable(shuffled, table.board.communityCards, 3);
        printCards(table.board.communityCards, 0, 3);
        sleep(2);

        for (int i = 0; i < PLAYER_COUNT; i++) {
            printf("Please pass the laptop to Player %d \n", i+1);
            sleep(5);
            printf("Your current bank size is: %d \n", players[0].balance);
            sleep(3);
            printCards(players[i].hand.cards, 0, 2);
            sleep(2);
            printf("The current pot size is %d \n", pot);

            turn_action decision = &actionOnTurn(0);
            if (decision.action == BET || decision.action == RAISE) {
                pot = pot + decision.bet;
                players[i].balance = players[i].balance - decision.bet;
            } else if (decision.action == FOLD) {
                goto restart;
            } else if (decision.action == CALL) {
                pot = pot + decision.bet;
                if (i == 0) {
                    P1canAdvance = true;
                } else {
                    P2canAdvance = true;
                }
            } else if (decision.action = CHECK) {
                if (i == 0) {
                    P1canAdvance = true;
                } else {
                    P2canAdvance = true;
                }
            }
            system("clear");
                    
            if (P1canAdvance && P2canAdvance) {
                goto reveal;
            } else {
                goto showdown;
            }
        }

        reveal:



    }

 /*
    printf("suit: %d, type: %d\n", c->suit, c->type);
    system("clear"); //clear console
    printf("Cut Card.\n");
    //c->hidden = 1;   // hidden==1 shows ???
    c->selected = 1; // changes card border color, 1 is red, 0 is green
    printCard(c, "\n");
    c->selected = 0; // make green for rest of deck
    printf("Deck before dealing:\n");
    printRestOfDeck(shuffled); // Printing the deck makes the cards visible
    
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
*/
}

