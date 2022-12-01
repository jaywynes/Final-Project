#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>
#include "action.h"

turn_action *actionOnTurn(int bet) {
  turn_action *turn = malloc(sizeof(turn_action));
  int *actionNum = 0;
  int *auxillary = 0;
  bool cont = true;

  while (cont) {
    if (bet != 0) {
      printf("It's your turn! Would you like to call(1), raise(2), or fold(3)?");
      scanf("%d", actionNum);
      if (*actionNum == 1) {
        turn -> action = CALL;
        turn -> bet = bet;
        cont = false;
      } else if (*actionNum == 2) {
        bool validRaise = false;
        while (!validRaise) {
          turn -> action = RAISE;
          printf("How much would you like to add to the bet to raise it by?");
          scanf("%d", auxillary);
          if (auxillary > 0) {
            turn -> bet = bet + *auxillary;
            validRaise = true;
          } else {
            printf("Invalid number to raise. Please enter a valid number.");
          }
        }
        cont = false;
      } else if (*actionNum == 3) {
        turn -> action = FOLD;
        printf("You've decided to fold. You have lost this round and cannot get any of your previous bets you've put into the pot for this round back.");
        turn -> bet = 0;
        cont = false;
      } else {
        printf("Invalid action, please enter a correct turn input.");
      }
    } else { //if bet == 0
      printf("It's your turn! Would you like to check(1) or bet(2) or fold(3)?\n");
      scanf("%d", actionNum);
      if (*actionNum == 1) {
        turn -> action = CHECK;
        turn -> bet = 0;
        cont = false;
      } else if (*actionNum == 2) {
        bool validBet = false;
        while (!validBet) {
          turn -> action = BET;
          printf("How much you would like to bet?\n");
          scanf("%d", auxillary);
          if (*auxillary > 0) {
            turn -> bet = *auxillary;
            validBet = true;
          } else {
            printf("Invalid number to bet. Please enter a valid number.");
          }
        }
        cont = false;
      } else if (*actionNum == 3) {
        turn -> action = FOLD;
        printf("You've decided to fold. You have lost this round and cannot get any of your previous bets you've put into the pot for this round back.");
        turn -> bet = 0; 
        cont = false;
        } else {
        printf("Invalid action, please enter a correct turn input.");
      }
    }
  }
  return turn;
}
