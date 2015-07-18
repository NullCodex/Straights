#ifndef _HUMAN_
#define _HUMAN_
#include "Player.h"
#include <unordered_set>

class Human : public Player{
public:
	Human(); // Human constructor takes no argument
	~Human(); // Human destructor, no memory cleaning is needed
	void legalPlays(std::unordered_set <Card*>); // legalPlays function
	void playCard(Card*, std::unordered_set<Card*>); // Play a card from the hand
	bool isLegalPlay(int, std::unordered_set<Card*>);
private:

};

#endif
