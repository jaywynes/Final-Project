#ifndef ACTION_H
#define ACTION_H

typedef enum action {
  CHECK,
  BET,
  CALL,
  RAISE,
  FOLD
} action;

typedef struct turn_action {
  action action;
  int bet;
} turn_action;

turn_action *actionOnTurn(int bet);

#endif //ACTION_H
