#ifndef _COMPUTER_
#define _COMPUTER_
#include "Player.h"
#include <unordered_set>

class Computer : public Player{
public:
	Computer();	//Constructor, creates a Computer with null lastCardPlayed_
	Computer(Player*); //Takes a player pointer to create a Computer (used to convert a Human to a computer for ragequit)
	~Computer();	//Destructor, using default
	void legalPlays(std::unordered_set <Card*>);	//Main action function for Computer
	Card* getLastCardPlayed();	//Returns the last Card played and sets it to null
	bool isLegalPlay(int, std::unordered_set<Card*>);
private:
	Card* lastCardPlayed_;	//Keeps track of last card played, if value is null then the last action was a discard or no action (at start of game)
	void playCard(Card*);	//Computer plays a card
};

#endif