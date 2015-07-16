#ifndef _DECK_
#define _DECK_
#include "Card.h"
#include <vector>
#include <random>

class Deck{
public:
	friend std::ostream &operator<< (std::ostream &, const Deck &);	//override output oprator to output deck
	void shuffle();	//randomizes the order of the pointers in cards_
	Deck(int);	//Constructor that takes an integer used as the seed for random operations
	~Deck(); //delete Card pointers
	Card* getCard(int);	//Returns a card pointer given index in the vector
private:
	std::vector <Card*> cards_;	
	int seed_;	//used for shuffle()
};

std::ostream &operator<< (std::ostream &, const Deck &);

#endif