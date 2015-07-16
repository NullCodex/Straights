#ifndef _CARD_
#define _CARD_

#include <ostream>
#include <istream>
#include <vector>

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

class Card{
	friend std::istream &operator>>(std::istream &, Card &);	//overriding output operator

public:
	Card(Suit, Rank);	//creates a card given a suit and rank
	Suit getSuit() const;	//Accessor: returns suit_
	Rank getRank() const;	//Accessor: returns rank_
	static int const CARD_COUNT = 52;	//Keeps track of number of possible cards (combinations of suit and rank)
private:
	Suit suit_;
	Rank rank_;
};

bool operator==(const Card &, const Card &);	//overriding equality operator, cards are equal if their suit and rank values are equal

//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const Card &);
std::istream &operator>>(std::istream &, Card &);

#endif
