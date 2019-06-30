// i/o example
// ********************************
// Title: Coding Assignment to implement a command-line blackjack game using C++
// Author: Saad Sadiq
// Date: June 28th, 2019
// *********************************


#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include <numeric>

using namespace std;

// Initialize the deck at start of every game
vector<int> init_deck(){
	//All Aces start with 11, but if the player/ dealer hits in a sum of over 21, the Ace converts to 1.
	int A = 11;
	int J = 10;
  	int Q = 10; 
  	int K = 10;
    
	// Since there is no importance of the shape, thus I created 4 of each card in the deck.
  	static const int arr[] = {A,2,3,4,5,6,7,8,9,10,J,Q,K,
	         				A,2,3,4,5,6,7,8,9,10,J,Q,K,
	     				    A,2,3,4,5,6,7,8,9,10,J,Q,K,
	     				    A,2,3,4,5,6,7,8,9,10,J,Q,K };

  	cout << " --- New Deck initialized --- " << endl;
	vector<int> deck (arr, arr + sizeof(arr) / sizeof(arr[0]) );
  
    // Randomly shuffle the deck; this is done after every 6th round
  	srand((unsigned)time(0));
	for (int i = 0; i < 52; i++) 
		swap(deck[i], deck[rand() % 52]);
  	return deck;
}

// Used to get a card from the deck and add it in the player's hand. 
int getCard(vector<int>* currDeck) {
	int card=currDeck->front();

	// The card is removed from the deck after being pulled 
	currDeck->erase(currDeck->begin());
	return card;
}

// used to count the cards in a player's / dealer's hand and return the sum
int countHand(vector<int>* hand){

	return accumulate(hand->begin(), hand->end(), 0);
}

// After the first two hands are dealt, this method checks if the player/dealer hits BlackJack
// I assume that both the dealer and player look at their cards to check for BlackJack
char isBlackJack(vector<int>* playerHand, vector<int>* dealerHand, bool& newRound) {

	char blackJack=' ';
	
	if(countHand(playerHand) == 21 && countHand(dealerHand) == 21){
		cout << "\n Hand is pushed, nobody wins" << endl;
		blackJack='h';
		newRound = true;
	}
	else if(countHand(playerHand) == 21 && countHand(dealerHand) < 21){
		cout << "\n Player hits BlackJack and Wins ! Game Ended" << endl;
		blackJack='p';
		newRound = true;
	}
	else if(countHand(playerHand) < 21 && countHand(dealerHand) == 21){
		cout << "\n Dealer hits BlackJack and Wins ! Game Ended" << endl;
		blackJack='d';
		newRound = true;
	}
	
	return blackJack;
}

// The player makes the first move, this method has all the steps that a user can make
// The user can only either Hit or Stand. The user cannot double down, nor split his cards
void playersMove(vector<int>* playerHand, vector<int>& currDeck, bool& play, bool& newRound){

	char keyPress = ' ';

	// The newRound Variable is used as an Abort flag, that is set 
	// in cases of BlackJack or Bust, the method will not start
	while(!newRound){
		cout << "Player's Turn, sum = " << countHand(playerHand)  << endl;
		if (countHand(playerHand) <= 21) {
			cout << "Press 'h' to draw a card, press 's' to stand, 'q' to quit game" << endl;
			cin >> keyPress;
			if (keyPress == 'h') {

				// If the player chooses to hit, a card is pulled from the deck 
				playerHand->push_back (getCard(&currDeck));
				continue;
			}
			else if (keyPress == 's'){

				// If the player chooses to stand, the turn is given to the dealer
				cout << "Player Stands" << endl;
				break;
			}
			else if (keyPress == 'q'){
				// If the user chooses to quit, the program exits 
				cout << " \n Quitting game " << endl;
				exit(0);
			}
			else 
				cout << "Invalid input, try again." << endl;
		}
		else if (countHand(playerHand) > 21) {
			// If at any point, the player's hand goes over the sum of 21,
			// we first check if an ace was present in the hands,			
			// if so, make it a 1

			int key = 11; // Since only Aces are values at 11, we search for 11 in the player's hand
			vector<int>::iterator itr = find(playerHand->begin(), playerHand->end(), key);
			
			// Print to show the before values of the hand
			cout << "Before" << countHand(playerHand) << endl;

			// If we find the number 11 in the player's hand
			if (itr != playerHand->cend()) {
				cout << "Converting ACE from 11 to 1 " << endl; 

				// Make the player's Hand at that index to be 1
				playerHand->at(distance(playerHand->begin(), itr)) = 1;  

				//Print to show the after values of the hand
				cout << "After" << countHand(playerHand) << endl;
				break;
			}
			else {
				// but if there are no Aces and the player still goes over 21, its a bust
				cout << "\n Player Busts ! Game ended." << endl ;
				newRound = true;
				break;
			} 
		}

	} 
}

// The dealer makes its move after the player, this method has all the steps that a dealer takes to evaluate the situation
// and make the decision. The dealer only either Hits or Stands. 
void dealersMove(vector<int>* playerHand, vector<int>* dealerHand, vector<int>& currDeck, bool& newRound){

	// Dealer can evaluate the case in every loop and decide on either to Hit 'h' or Stand 's'
	char dealersChoice = ' ';

	// The newRound Variable is used as an Abort flag, that is set 
	// in cases of BlackJack or Bust, the method will not start
	while(!newRound){
		cout << "Dealer's Turn. sum= " << countHand(dealerHand)  << endl;
		if (countHand(dealerHand) <= 21) {
			// if count goes > 21, and if 11, then make 11 -> 1
			if (countHand(dealerHand) <= 17) {
				// if the sum <= 17, dealer must hit,
				// initially I set A=11, so soft 17 is covered with this
				cout << "Dealer chose to Hit" << endl;
				dealerHand->push_back (getCard(&currDeck));
				continue;
			}
			else if (countHand(dealerHand) > 17){
				cout << "Dealer chose to Stand" << endl;
				break;
			}
		}
		else if (countHand(dealerHand) > 21) {
			// Similar to the player's case; if at any point, the dealer's hand goes over the sum of 21,
			// we first check if an ace was present in the hands,			
			// if so, make it a 1

			int key = 11;
			vector<int>::iterator itr = find(dealerHand->begin(), dealerHand->end(), key);

			// Print to show the before values of the hand
			cout << "Before" << countHand(dealerHand) << endl;

			// If we find the number 11 in the player's hand
			if (itr != dealerHand->cend()) {
				cout << "Converting ACE from 11 to 1 " << endl; 

				// Make the player's Hand at that index to be 1	
				dealerHand->at(distance(dealerHand->begin(), itr)) =1;

				//Print to show the after values of the hand
				cout << "After" << countHand(dealerHand) << endl;
				break;
			}
			else {
				// but if there are no Aces and the dealer still goes over 21, its a bust
				cout << "\n Dealer Busts ! Game ended." << endl ;
				newRound = true;
				break; 
			}
		}

	} 
}

// This method prints the hands of both (dealer, player) on the command line
void showHand(vector<int>* dealerHand, vector<int>* playerHand, bool& playerTurn){

	// In the start, until the player's turn has not ended, the player doesn't see the dealer's cards
	cout << "\n Dealer's Hand: " << endl;
	if(playerTurn){
		cout << dealerHand->at(0) << "   *** " << endl; ;
	}
	else {
		// if the player's turn has ended the player can see the dealers hand
		for(int i=0; i<dealerHand->size(); i++)
			cout << dealerHand->at(i) << "   " ;
	}

	cout << "\n Player's Hand : " << endl;

	for(int i=0; i<playerHand->size(); i++){
				cout << playerHand->at(i) << "   " ;

	}
}

// This method sets up a new round the clearing up the vectors for player's and dealer's hands,
// then deals two new cards to each. 
void setupNewRound(vector<int>* playerHand, vector<int>* dealerHand, vector<int>* currDeck, bool& newRound){
	cout << "Flushing hands" << endl;
	playerHand->clear();
    dealerHand->clear();
    // Step 2. Deal Dealer Cards
	dealerHand->push_back (getCard(currDeck));
	dealerHand->push_back (getCard(currDeck));

	// Step 3. Deal Player Cards 
	playerHand->push_back (getCard(currDeck));
	playerHand->push_back (getCard(currDeck));

	newRound = false;
}

// This is the final method that evaluates the came conditions and assigns a winnder

void decideWinner(vector<int>* playerHand, vector<int>* dealerHand, int& playerWins, float& pWinPercent, int& round, char& blackJack){

	// We check conditions in a hierarchical manner. We first check for blackjack,
	// then if the opponent busts, then for Push and finally for the winner by closest to 21.  
	if (blackJack == 'h'){
		if(blackJack == 'p'){
			cout << " Player! hits BlackJack" << endl;
			playerWins++;
		} 
		else {
			cout << " Dealer! hits BlackJack" << endl;
		}
	}
	else if(countHand(playerHand) > 21){
		cout << "Dealer ! , because the Player Bust" << endl;
	}
	else if (countHand(dealerHand) > 21 ){
		cout << "Player !  because the Dealer Bust" << endl;
		playerWins++;
	}
	else if(countHand(playerHand) == countHand(dealerHand)){
		cout << "Push" << endl;
	}
	else if(countHand(playerHand) > countHand(dealerHand)){
		cout << "Player! " << endl;
		playerWins++;
	}
	else if(countHand(playerHand) < countHand(dealerHand)){
		cout << "Dealer! " << endl;
	}
	
	// we calculate the player's win percentage
	pWinPercent = playerWins * 100 /round;
	cout << "Player Win Percentage is: " << pWinPercent << endl;
	round++;
}

// This is the main method
int main() {

	int round=1;
	int playerWins=0;
	float pWinPercent = 0.0;
	char blackJack = ' ';
	vector<int> currDeck;
	vector<int> playerHand;
	vector<int> dealerHand;

	bool playerTurn = true; 
	bool play = true;
	bool newRound = true;
	// Initialize game

	
	cout << " Welcome to a game of BlackJack, I am your Dealer. Lets Start! " << endl;
	
	
	while(play){
		
		cout << "Round: " << round << endl;

		// Step 1. Create a fresh deck and setup a new round
	 	if(round == 1 || round%7 == 0)
		 	currDeck = init_deck();
	 	setupNewRound(&playerHand, &dealerHand, &currDeck, newRound);

	 	// Step 2. Print the current hands of dealer and the player
	 	playerTurn = true;
		showHand(&dealerHand, &playerHand, playerTurn);
		
		// Step 3. Check if someone hits blackjack, continue otherwise
		blackJack = isBlackJack(&playerHand, &dealerHand, newRound);
					
		// Step 4. Start Turns; Player goes first
		playersMove(&playerHand, currDeck, play, newRound);
		playerTurn= false;
		showHand(&dealerHand, &playerHand, playerTurn);
		
		// Step 5. Dealer plays after the player
		dealersMove(&playerHand, &dealerHand, currDeck, newRound);
		showHand(&dealerHand, &playerHand, playerTurn);
		
		// Step 6. Evaluate the winner of the game
		cout << "The Winner is : " << endl;
		decideWinner(&playerHand, &dealerHand, playerWins, pWinPercent, round, blackJack);
	}
  	return 0;
}



 // return deck.empty();