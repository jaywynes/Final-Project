#include <stdio.h>
#include <string.h>
#include <locale.h> //unicode
#include <wchar.h> //unicode
#include "player.h"




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
    CommunityCards bestTemp;
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

    Card *pairs[6];
    Card *trips[6];
    Card *quads[4];

    for (int i = 0; i < sizeof(pool.availableCards); i++) {
        for (int j = 0; j < sizeof(pool.availableCards)-i-1; j++) {
            if (pool.availableCards[i] == pool.availableCards[j+1] && pool.availableCards[j+1] == pool.availableCards[j+2] && pool.availableCards[i] == pool.availableCards[j+3]) {
                quads[0] = pool.availableCards[i];
                quads[1] = pool.availableCards[j+1];
                quads[2] = pool.availableCards[j+2];
                quads[3] = pool.availableCards[j+3];                
            } else if (pool.availableCards[i] == pool.availableCards[j+1] && pool.availableCards[j+1] == pool.availableCards[j+2]) {
                trips[0] = pool.availableCards[i];
                trips[1] = pool.availableCards[j+1];
                trips[2] = pool.availableCards[j+2];                
            } else if (pool.availableCards[i] == pool.availableCards[j+1]) {
                pairs
            }
        }
    }

    int cardRankTracker[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int numPairs = 0;
    int numTrips = 0;
    int quadIndex = 0;
    int fullHouseTri = 0;
    int fullHouseDob = 0;
    int numLeftoverSlots = 0;
    handSorter(&pool.availableCards);

    for (int i = 0; i < sizeof(pool.availableCards); i++) {
        int j = pool.availableCards[i]->value;
        int k = cardRankTracker[j];
        k = k++;
        cardRankTracker[j] = k;
    }

    for (int i = 0; i < sizeof(pool.availableCards); i++) {
        if (cardRankTracker[i] == 2) {
            numPairs++;
            fullHouseDob = i;
        } else if (cardRankTracker[i] == 3) {
            numTrips++;
            fullHouseTri = i;
        } else if (cardRankTracker[i] == 4) {
            opp[currentPlayer].bHandType = Quads;
            quadIndex = i;
        }
    }

    if (numPairs == 1 && numTrips == 0 && opp[currentPlayer].bHandType != Quads) {
        opp[currentPlayer].bHandType = Pair;
        numLeftoverSlots = 3;
        for (int i = 0; i < sizeof(pool.availableCards); i++) {

        }
    }else if (numPairs == 2 && numTrips == 0 && opp[currentPlayer].bHandType != Quads) {
        opp[currentPlayer].bHandType = TwoPair;
        numLeftoverSlots = 1;
    } else if (numPairs == 0 && numTrips == 1 && opp[currentPlayer].bHandType != Quads) {
        opp[currentPlayer].bHandType = Trips;
        numLeftoverSlots = 2;

    } else if (opp[currentPlayer].bHandType == Quads) {
        int k = 0;
        for (int i = 0; i < sizeof(pool.availableCards); i++) {
            if (pool.availableCards[i]->value != quadIndex) {
                bestTemp.tempCards[i-k] = pool.availableCards[i];
            }
        }
        numLeftoverSlots = 1;
    } else if (numPairs == 1 && numTrips == 1 && opp[currentPlayer].bHandType != Quads) {
        opp[currentPlayer].bHandType = FullHouse;
        numLeftoverSlots = 0;
    } else if (numPairs == 2 && numTrips == 1 && opp[currentPlayer].bHandType != Quads) {
        
    }
    bestTemp.tempCards = [];
}

void highCardExamine (CardPool *available, Player **play, int currentPlayer, TempCards *tempCards, int leftover) {
    CardPool pool = *available;
    Player *opp = *play;
    TempCards bestTemp = *tempCards;

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
