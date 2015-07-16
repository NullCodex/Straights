#include "Card.h"
#include <string>
#include <cassert>
using namespace std;

//Constructor: Creates a Card given a suit and rank
Card::Card(Suit s, Rank r){
	suit_ = s;
	rank_ = r;
}

//Accessor: returns enum value suit_ of the card object
Suit Card::getSuit() const{
	return suit_;
}

//Accessor: returns enum value rank_ of the card object
Rank Card::getRank() const{
	return rank_;
}

//Overriding equality operator, 2 cards are equal if they have the same suit and rank.
bool operator==(const Card &a, const Card &b){
	return a.getSuit() == b.getSuit() && a.getRank() == b.getRank();
}

//Overriding output for cards, will output <rank><suit>
ostream &operator<<(ostream &out, const Card &c){
	string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
		
	out << ranks[c.getRank()] << suits[c.getSuit()];
	
	return out;
}

istream &operator>>(istream &in, Card &c){
	string suits = "CDHS", ranks = "A234567891JQK";
	
	string str;
	in >> str;
	assert ( !in.fail() );
	
	//Read in the rank, make sure it's valid
	c.rank_ = (Rank)ranks.find( str.at(0) );
	assert ( c.rank_ != string::npos );
	
	//If it's a 10, make sure the 2nd character is a 0
	if ( c.rank_ == TEN ){
		assert(str.at(1) == '0');
		str.at(1) = str.at(2);
	}
	
	//Read in the suit, make sure it's valid
	c.suit_ = (Suit)suits.find( str.at(1) );
	assert ( c.suit_ != string::npos );
	
	return in;
}
