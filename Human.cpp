#include "Human.h"
#include <iostream>
#include <math.h>
#include <algorithm>

// Constructor
Human::Human():Player(){}
// Destructor
Human::~Human(){}

// prints the legal plays of a human player
void Human::legalPlays(std::unordered_set <Card*> cards){
	if (cards.size() == 1){
		std::cout << " 7S";
		return;
	}
	for (unsigned int i = 0; i < (unsigned)hand_.size(); i++){
		if (cards.find(hand_[i]) != cards.end()){
			std::cout << " " << *hand_[i];
		}
	}
}

// Play the card and decrease the hand
void Human::playCard(Card* card, std::unordered_set<Card*> cards){
	std::vector<Card *>::iterator it = std::find(hand_.begin(), hand_.end(), card);
	hand_.erase(it); //remove card from hand
}

bool Human::isLegalPlay(int cardNumber, std::unordered_set<Card*> cards){
	if (cards.find(hand_[cardNumber]) == cards.end()){
		return false;
	}
	return true;
}