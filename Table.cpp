#include "Table.h"
#include <string>
#include <iostream>
// Place the desired card onto the table, separating based on suit
void Table::placeCard(Card* card){
	cardsOnTable_.push_back(card);
	if (card->getSuit() == CLUB){
		clubs_.insert(card->getRank() + 1);
	}
	else if (card->getSuit() == SPADE){
		spades_.insert(card->getRank() + 1);
	}
	else if (card->getSuit() == HEART){
		hearts_.insert(card->getRank() + 1);
	}
	else{
		diamonds_.insert(card->getRank() + 1);
	}
}

// Find what was the last card played
Card* Table::lastCardPlayed(){
	if (cardsOnTable_.size() == 0){
		return NULL;
	}
	return cardsOnTable_[cardsOnTable_.size() - 1];
}

// Wipes the table used for a new round
void Table::clear(){
	cardsOnTable_.clear();
	hearts_.clear();
	diamonds_.clear();
	spades_.clear();
	clubs_.clear();
}

// Overloaded the ostream operator to print the current table
std::ostream &operator<<(std::ostream & sout, const Table& deck){
	sout << "Clubs:";
	for (std::set<int>::iterator it = deck.clubs_.begin(); it != deck.clubs_.end(); ++it){
		sout << " " << *it;
	}
	sout << "\n";
	sout << "Diamonds:";
	for (std::set<int>::iterator it = deck.diamonds_.begin(); it != deck.diamonds_.end(); ++it){
		sout << " " << *it;
	}
	sout << "\n";
	sout << "Hearts:";
	for (std::set<int>::iterator it = deck.hearts_.begin(); it != deck.hearts_.end(); ++it){
		sout << " " << *it;
	}
	sout << "\n";
	sout << "Spades:";
	for (std::set<int>::iterator it = deck.spades_.begin(); it != deck.spades_.end(); ++it){
		sout << " " << *it;
	}
	sout << "\n";
	return sout;
}

// Grabs the cards on table
std::vector <Card*> Table::cardsOnTable() const{
	return cardsOnTable_;
}
