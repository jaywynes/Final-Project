#include <stdio.h>
#include <string.h>
#include <locale.h> //unicode
#include <wchar.h> //unicode
#include "player.h"
#include "handTester.h"




int compHands(Player *opp, Table tbl) {
    CardPool pool;
    for (int i = 0; i < sizeof(opp); i++) {
        for (int j = 0; j < opp[i].hand.cardsInHand; j++) {
            pool.availableCards[j] = opp[i].hand.cards[i];
        }
        for (int j = 0; j < tbl.board.numCardsOnTable; j++) {
            pool.availableCards[j+2] = tbl.board.communityCards[j];
        }
        bestHandCalc(&pool, &opp, i);
    }
}

void bestHandCalc(CardPool *available, Player **play, int currentPlayer) {
    CardPool pool = *available;
    Player *opp = *play;
    TempCards bestTemp;
    if (evalFlush(&pool , &opp, currentPlayer, &bestTemp)) {

        evalStraight(&pool , &opp, currentPlayer, &bestTemp);

    } else if (opp[currentPlayer].bHandType = High) {
        evalStraight(&pool , &opp, currentPlayer, &bestTemp);
        
    } else {
        matchTester(&pool, &opp, currentPlayer, &bestTemp);
        
    }

}

bool evalFlush(CardPool *available, Player **play, int currentPlayer, TempCards *tempCards) {
    CardPool pool = *available;
    Player *opp = *play;
    TempCards bestTemp = *tempCards;
    int suitTracker[] = {0, 0, 0, 0}; //To keep track of number of each suit present in hand
    //CommunityCards bestHandTemp[];

    for (int i = 0; i < sizeof(opp); i++) {
        int j = pool.availableCards[i]->suit; //Take int value from suit enum
        int k = suitTracker[j]; // Take current val of suitTracker array into k
        k = 1+k; //increment k by 1 to indicate another of that suit is present 
        suitTracker[j] = k; //restore suitTracker val
    }

    for (int i = 0; i < sizeof(suitTracker); i++) {
        if (suitTracker[i] < 5) { //if there is not a flush potential in this suit
            opp[currentPlayer].bHandType = High; //Sets hand type to High as a default
            break;
            //continue;
        } else if (suitTracker[i] == 5) { //If there are only 5 cards with the same suit
            int flushSuit = suitTracker[i];

            opp[currentPlayer].bHandType = Flush; //Sets hand type to flush
            int k = 0;
            for (int j = 0; j < sizeof(pool); j++) {
                if(pool.availableCards[j]->suit == flushSuit) {
                    opp[currentPlayer].bestHand.communityCards[(j-k)] = pool.availableCards[j];
                } else {
                    k++;
                }
                
            }
            handSorter(&opp[currentPlayer].bestHand.communityCards);
            break;
        } else {
            int flushSuit = suitTracker[i];
            opp[currentPlayer].bHandType = Flush; //Sets hand type to flush
            bestTemp.tempCards = (Card*)malloc(sizeof(Card)*suitTracker[i]);
            int k=0;
            for (int j = 0; j < sizeof(pool); j++) {
                if(pool.availableCards[j]->suit == flushSuit) {
                    bestTemp.tempCards[(j-k)] = pool.availableCards[j];
                } else {
                    k++;
                }
            }
            handSorter(&(bestTemp.tempCards));
            bestTemp.numTempCards = sizeof(bestTemp.tempCards);
            break;
        }
    }

    return opp[currentPlayer].bHandType == Flush;
}


void evalStraight(CardPool *available, Player **play, int currentPlayer, TempCards *tempCards) {
    CardPool pool = *available;
    Player *opp = *play;
    TempCards bestTemp = *tempCards;
    

    if (opp[currentPlayer].bHandType == Flush) {
        if (bestTemp.numTempCards > 0) {
            int streak = 0;
            for (int i = 0; i < bestTemp.numTempCards; i++) {
                if (bestTemp.tempCards[i]->value = bestTemp.tempCards[i+1]->value) {
                    streak++;
                    if (streak == 5) {
                        opp[currentPlayer].bHandType = StraightFlush;
                        break;
                    }
                } else {
                    streak = 0;
                }
            }

            if (opp[currentPlayer].bHandType != StraightFlush) {
            
                bool goodAce = false, goodKing = false, goodQueen = false, goodJack = false, goodTen = false;
                for (int i = 0; i < opp[currentPlayer].bestHand.numCardsOnTable; i++) {
                    if (opp[currentPlayer].bestHand.communityCards[i]->value = 13) {
                        goodKing = true;
                    } else if (opp[currentPlayer].bestHand.communityCards[i]->value = 12) {
                        goodQueen = true;
                    } else if (opp[currentPlayer].bestHand.communityCards[i]->value = 11) {
                        goodJack = true;
                    } else if (opp[currentPlayer].bestHand.communityCards[i]->value = 10) {
                        goodTen = true;
                    } else if (opp[currentPlayer].bestHand.communityCards[i]->value = 1) {
                        goodAce = true;
                    }
                }
                if (goodAce && goodKing && goodQueen && goodJack && goodTen) {
                    opp[currentPlayer].bHandType == RoyalFlush;
                }
            }
        }
        


    } else {
        handSorter(&pool.availableCards);
        int streak = 0;
            for (int i = 0; i < bestTemp.numTempCards; i++) {
                if (bestTemp.tempCards[i]->value = bestTemp.tempCards[i+1]->value) {
                    streak++;
                    if (streak == 5) {
                        opp[currentPlayer].bHandType = Straight;
                        break;
                    } else {
                        streak = 0;
                    }
                }
            }
                        if (opp[currentPlayer].bHandType != Straight) {
            
                bool goodAce = false, goodKing = false, goodQueen = false, goodJack = false, goodTen = false;
                for (int i = 0; i < opp[currentPlayer].bestHand.numCardsOnTable; i++) {
                    if (opp[currentPlayer].bestHand.communityCards[i]->value = 13) {
                        goodKing = true;
                    } else if (opp[currentPlayer].bestHand.communityCards[i]->value = 12) {
                        goodQueen = true;
                    } else if (opp[currentPlayer].bestHand.communityCards[i]->value = 11) {
                        goodJack = true;
                    } else if (opp[currentPlayer].bestHand.communityCards[i]->value = 10) {
                        goodTen = true;
                    } else if (opp[currentPlayer].bestHand.communityCards[i]->value = 1) {
                        goodAce = true;
                    }
                }
                if (goodAce && goodKing && goodQueen && goodJack && goodTen) {
                    opp[currentPlayer].bHandType == Straight;
                }
            }
        }
    bestTemp.tempCards = [];
}

void matchTester(CardPool *available, Player **play, int currentPlayer, TempCards *tempCards) {
    
    CardPool pool = *available;
    Player *opp = *play;
    TempCards bestTemp = *tempCards;
    handSorter(&pool.availableCards);



    Card *pairs[6];
    int *trips[6];
    int *quads[4];
    int j2 = 0;
    int k2 = 0;
    int l2 = 0;

    for (int i = 0; i < sizeof(pool.availableCards); i++) {
        if (pool.availableCards[i]->value == pool.availableCards[i+1]->value) { //Pair Testing
            if(pool.availableCards[i]->value == pool.availableCards[i+2]->value) { //Trip testing
                if (pool.availableCards[i]->value == pool.availableCards[i+3]->value) { //Quad Testing
                    
                    for (int l = i; l < sizeof(pool.availableCards); l++) {
                        opp[currentPlayer].bestHand.communityCards[l2]=pool.availableCards[l];
                        quads[l2] = l;
                        l2++;
                    }
                    opp[currentPlayer].bHandType = Quads;
                    l2++;
                    i = i+3;
                    break;

                }  else {// If it is a trip but not a quad

                    for (int k = i; k < sizeof(pool.availableCards); k++) {
                        opp[currentPlayer].bestHand.communityCards[k2] = pool.availableCards[k];
                        trips[k2] = k;
                        k2++;
                    }

                    i = i+2;
                    if (k2 == 6) {
                        break;
                    }
                }
            } else { // If it is a pair but not a trip or quad:
                    for (int j = i; j < sizeof(pool.availableCards); j++) {
                        opp[currentPlayer].bestHand.communityCards[j2] = pool.availableCards[j];
                        pairs[j2] = j;
                        j2++;
                    }
                i++;
            }
        }
    }
    int numExtra = 0;
    int leftover = 0;

    if (opp[currentPlayer].bHandType == Quads) {
        numExtra = 1;
        leftover = 3;
        int k = 0;
        for (int i = 0; i < sizeof(pool.availableCards); i++) {
            if (quads[0] != i && quads[1] != i && quads[2] != i && quads[3] != i) {
                bestTemp.tempCards[k] = pool.availableCards[i];
                k++;
            }
        }
        opp[currentPlayer].bestHand.communityCards[l2] = findHighest(bestTemp.tempCards, numExtra);
    } else if (j2 > 0) {
        opp[currentPlayer].bHandType = Pair;
        for (int i = j2; i < sizeof(pool.availableCards); i++) {
            opp[currentPlayer].bestHand.communityCards[i] = pool.availableCards[i];
        }
        
    } else if (k2 > 0) {
        opp[currentPlayer].bHandType = Trips;
        for (int i = k2; i < sizeof(pool.availableCards); i++) {
            opp[currentPlayer].bestHand.communityCards[i] = pool.availableCards[i];
        }
    }

}

Card *findHighest(Card **leftover, int numExtra) {
    Card *leftoverCards = *leftover;
    Card returnCards[numExtra];
    handSorter(&leftoverCards);

    for (int i = 0; i < numExtra; i++) {
        returnCards[i] = leftoverCards[i];
    }

    return returnCards;

}


void handSorter(Card **cardsToSort) {
    Card *tempCards = *cardsToSort;
    for (int i = 0; i < sizeof(tempCards)-1; i++) {
        for (int j =0; j < sizeof(tempCards)-i-1; j++) {
            if (tempCards[j].value < tempCards[(j+1)].value) {
                swap(&tempCards[j], &tempCards[j+1]);
            }
        }
        
    }
}

void swap(Card *first, Card *second) {
    Card temp = *first;
    *first = *second;
    *second = temp;
}
