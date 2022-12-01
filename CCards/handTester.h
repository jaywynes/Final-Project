#ifndef HANDTESTER_H
#define HANDTESTER_H
#include "player.h"


int compHands(Player *opp, Table tbl);
void bestHandCalc(CardPool *available, Player **play, int currentPlayer);
bool evalFlush(CardPool *available, Player **play, int currentPlayer, TempCards *tempCards);
void evalStraight(CardPool *available, Player **play, int currentPlayer, TempCards *tempCards);
void matchTester(CardPool *available, Player **play, int currentPlayer, TempCards *tempCards);
Card *findHighest(Card **leftover, int numExtra);
void handSorter(Card **cardsToSort);
void swap(Card *first, Card *second);

#endif //HANDTESTER_H