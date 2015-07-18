#ifndef _PLAYER_
#define _PLAYER_
#include "Deck.h"
#include <vector>
#include <iostream>
#include <unordered_set>

class Player{
public:
	Player(); // Use player's constructor to set score
	~Player();
	bool contains(Suit, Rank) const;
	//default destructor is fine, deck will take care of deleting card*
	friend std::ostream &operator<<(std::ostream &, Player&);
	virtual void legalPlays(std::unordered_set <Card*>) = 0; // Pure virtual function that's left to the child class to implement
	void discardCard(Card*); // Discard a card
	void outputDiscardList() const; // Prints the discarded list
	void discardHand(); // Wipes the hand
	Card* findCard(Suit, Rank); // Find a specific card
	void newHand(int, Deck&); // Grabs a new set of cards for the player
	int getScore() const; // Return the score
	int valueOfDiscarded() const; // Function to help tabulating the score
	void updateScore(); // Update the player's score
	int numDiscards() const;
	std::vector<int> currentHand() const;
protected:
	std::vector <Card*> hand_; //should only point to cards created by Deck
	int score_; // Each player should have a score variable to keep track of the current scoring
	std::vector <Card*> discarded_; // A vector of discarded cards
};

#endif
