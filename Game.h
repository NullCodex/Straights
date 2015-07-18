#ifndef _GAME_
#define _GAME_

#include <vector>
#include <unordered_set>
#include "Card.h"
#include "Deck.h"
#include "Computer.h"
#include "Human.h"
#include "Table.h"
#include "Command.h"

enum RoundStatus {START, ACTIVE, WAIT, END};

class Game{
public:
	Game(std::vector<char>, int);	//Constructor, takes vector of chars denoting human/computer players and an int representing a random value to build the deck
	~Game();	//Destructor, deletes player pointers
	void newRound();	//Method that deals with new round operations
	void nextTurn();	//Deals with next Turn operations
	void outputCurrentTable() const;	//Outputs the table for human players
	void currentScore() const;	//Outputs the score
	bool winnerExists() const;	//Returns if a player has over 80 points
	bool hasQuit() const;	//Returns if a player has quit
	void endRound();	//Handles actions at the end of a round
	void outputWinners() const;	//Outputs the winners
	void updatePossiblePlays();	//Updates unordered set of possible plays the set of all cards that can be played
	void nextPlayer();
	bool isLegalPlay(int) const;
	bool canPlayCard() const;
	Card* getCard(int) const;
	RoundStatus status() const;
	std::vector<int> scores() const;
    std::vector<int> discards() const;
    int currentPlayerNumber() const;
    void playRound();
    std::vector<int> currentHand() const;
    std::vector<int> getTableCardValues() const;
    void humanAction(Command);
    bool isRoundOver() const;
private:
	Card* getCardReference(Card);	//Given a card, returns the pointer in the deck to the card
	void determineFirstPlayer();	//Determines which player has seven of spades
	int firstPlayer_;	//Keeps track of the index of the first player
	int currentPlayer_;
	Deck deck_;	//Holds the deck for the game
	std::vector <Player*> players_;	//Keeps track of the players
	std::vector <char> playerTypes_;	//Keeps track of human and computer players
	std::unordered_set<Card *> possiblePlays_;	//Keeps track of the set of cards that can be played
	Table table_;	//Keeps track of the cards on the table
	bool quit_;	//Keeps track of if a player has quit the game
	RoundStatus status_;
};


#endif