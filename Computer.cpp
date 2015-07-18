#include "Computer.h"
#include <iostream>
#include <vector>
#include <algorithm>

//Computer Constructor, takes no arguments
// Use player constructor to set score
Computer::Computer():Player() {
	lastCardPlayed_ = NULL;
}

//Constructor takes a player pointer and creates a computer
//Used to convert a human to a computer for ragequit
Computer::Computer(Player* player) : Player(*player){
	lastCardPlayed_ = NULL;	
}

//The main function that takes care of a computer player's action
//Input parameter unordered_set of cards that keeps track of possible plays
//The computer player's possible plays are a subset of the set of possible cards that can be played
//Initially, cards only contains 7S
void Computer::legalPlays(std::unordered_set <Card*> cards){
	if (cards.size() == 1){	//checks if only 7S is the possible play
		std::cout << "plays 7S.\n";
		for (int i = 0; i < hand_.size(); i++){
			if (*hand_[i] == Card(SPADE, SEVEN)){
				lastCardPlayed_ = hand_[i];	//set last card played to be added to the table later
				playCard(hand_[i]);
				return;
			}
			
		}
	}
	for (int i = 0; i < hand_.size(); i++){
		if (cards.find(hand_[i]) != cards.end()){
			std::cout << "plays " << *hand_[i] << ".\n";
			lastCardPlayed_ = hand_[i]; //set last card played to be added to the table later
			playCard(hand_[i]);
			return;
		}
	}
	std::cout << "discards " << *hand_[0] << ".\n";	//if no possible plays, discard card
	discardCard(hand_[0]);
	return;
}

//returns last card played and then sets value to null
//This function is used by game to add the card played to the table
Card* Computer::getLastCardPlayed(){
	Card* temp = lastCardPlayed_;
	lastCardPlayed_ = NULL;
	return temp;
}

//Simulates playing a card, just remove the card from the hand
void Computer::playCard(Card* card){
	std::vector<Card *>::iterator it = std::find(hand_.begin(), hand_.end(), card);
	hand_.erase(it);
}

bool Computer::isLegalPlay(int cardNumber, std::unordered_set<Card*> cards){
	return true;
}