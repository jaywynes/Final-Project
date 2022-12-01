# This is a to do list for the project

## Core Requirements

*Betting System*
Must have a System in place for betting, including tracking the balances of each player, betting, antes, small and big blinds, etc.


*Game Phases*
Poker games run through phases, called Streets. They are listed as follows

Preflop
Flop
Turn
River/Showdown

Betting occurs during each Street, and there are different dealing amounts


*Hand Calculation*
Need to have a calculation done at the end of a hand to caculate the best hand everyoe posesses from their own 2 card hand to the 5 on the "table", must use Number and Suit for comparison, and must test for the following hands, lowest strength to highest:

High Card: 5 Unmatched Cards, highest Value card of 5
One Pair: 2 Cards of same Rank
Two Pair: 2 different Pairs
Three of a Kind (Trips): 3 Cards of the same Rank
Straight: Any 5 Cards in consecutive Rank (12345)
Flush: Any 5 Cards of the same Suit
Full House: Trips combined with one Pair
Four of a Kind (Quads): 4 Cards of the same Rank
Straight Flush: 5 Cards of same Suit, consecutively Ranked
Royal Flush: 5 Cards of same Suit, with Ranks 10, J, Q, K, A

*Player Action System*
CHeck, Call, Raise, Fold, etc



### Other Stuff to be added later


*Button Passing*
Play has 3 "roles", the button, the small blind, and the big blind
Button is passed around, 1 seat to the left after every round. One seat to buttons left is small blind, 2 seats is big blind, they must bet required ammounts

*Hand percentage System*
Shows player outs, potential ranges, etc