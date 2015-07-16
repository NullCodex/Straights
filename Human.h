#ifndef _HUMAN_
#define _HUMAN_
#include "Player.h"
#include <unordered_set>

class Human : public Player{
public:
	class InvalidCardException{
	public:
		InvalidCardException(Card* card) : card_(*card){}
		Card card() const{ return card_; }
	private:
		Card card_;
	}; // Exception class to catch invalid cards
	class CanPlayCardException{
	public:
		CanPlayCardException(Card* card) : card_(*card){}
		Card card() const{ return card_; }
	private:
		Card card_;
	};
	Human(); // Human constructor takes no argument
	~Human(); // Human destructor, no memory cleaning is needed
	void legalPlays(std::unordered_set <Card*>); // legalPlays function
	void discardCard(Card*, std::unordered_set<Card*>); // Discard the card from the hand
	void playCard(Card*, std::unordered_set<Card*>); // Play a card from the hand
private:

};

#endif
