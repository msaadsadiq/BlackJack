# BlackJack
Black Jack implemented in C++

# Basic Overview 
The program implements the game BlackJack. In this game, the dealer deals a Single Deck that is shuffled after every 6th game. The code plays as the dealer, and the user play through the command line against the dealer. All the player decisions are taken by the user and not the program. The program keeps the score for the player wins and player win percentage.

# Assumptions, Rules and Shortcomings
1. The program doesn't offer any betting or reward system. Thus there is no option to double down. 
2. Also, there is no option for players to split cards. 
3. Since there was no importance of the card suits (hearts, diamonds, spades, clubs), I created multiples of 4 of each card in the deck. 
4. I start with all Aces to be always 11, but if the player or dealer hits and results in a sum of over 21, then the program converts the Ace into a 1. 
5. The Dealer always hits on values less than and equals to 17. 
6. The assumption of starting with Ace=11 and to hit on less than and equal to 17, covers the requirement for the dealer to always hit on soft 17 as well. 
7. The program is implemented in a purely deterministic fashion and the dealer rules as coded as conditions. There is no probabilistic inferencing to determine dealer's actions. 

# Third Party Resources
I didn't have prior knowledge of the game BlackJack and I don't know C++. So I used the following third party websites to learn about BlackJack and C++. 
 
BlackJack
https://www.arkadium.com/games/blackjack/
C++
https://www.geeksforgeeks.org/
C++ implementation of BlackJack that I studied 
https://github.com/fengvyi/Blackjack

# To Run
Locate the file on command line then run the following

$ g++ 21.cpp
$ ./a.out  
