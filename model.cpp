/*
 * MVC example of GTKmm program
 *
 * Model class.  Is responsible keeping track of the deck of cards.  
 * It knows nothing about views or controllers.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include "model.h"
#include <sstream>

Model::Model() : topCard_(-1), gameStatus_(false), seed_(0){
	game_ = NULL;
	for (unsigned int i = 0; i < 4; i++){
		playerTypes_.push_back('h');
	}
}

// Return suit number
Suit Model::suit(int suitNumber) {
  //if (topCard_ == -1) return NOSUIT;
  
  return (Suit) (suitNumber);
}

// Return rank number
Rank Model::rank(int rankNumber) {
  //if (topCard_ == -1) return NORANK;

  return (Rank) (rankNumber);
}

// Returns the player type
char Model::playerType(int player) const{
	return playerTypes_[player];
}

// Checks to see if the game started
bool Model::hasGameStarted() const{
	return gameStatus_;
}

// Checks if the player is a human
bool Model::isHuman(int playerNumber) const{
	if (playerTypes_[playerNumber] == 'h'){
		return true;
	}
	return false;
}

// Shows the winners
std::string Model::showWinners() const{
	return game_->getWinners();
}

// CHeck to see if a winner exists
bool Model::winnerExists() const{
	return game_->winnerExists();
}

// Creates a new game
void Model::newGame(std::string seed)
{
	if (gameStatus_){
		endGame();
	}
	gameStatus_ = true;
	std::stringstream ss;
    ss << seed;
    ss >> seed_;
	game_ = new Game(playerTypes_, seed_);
	std::cout << "newGame" << std::endl;
	setupRound();
}

// Delete the game object
void Model::endGame()
{
	if (game_!=NULL){
		delete game_;
		game_ = NULL;
	}
	gameStatus_ = false;
	std::cout << "endGame" << std::endl;
	notify();
}

// Calls the end game function
std::string Model::endRound(){
	return game_->endRound();
}

// Model's function for when player button clicked
void Model::playerButtonClicked(int playerNumber)
{
	if (hasGameStarted() == false){ //game hasn't started, can still switch player types
		if (playerTypes_[playerNumber] == 'h'){
			playerTypes_[playerNumber] = 'c';
		}
		else{
			playerTypes_[playerNumber] = 'h';	
		}
	}
	else{
		playerTypes_[playerNumber] = 'c';
		game_->ragequit();
	}
	notify();
}

// Model's handbutton clicked function
void Model::handButtonClicked(int cardNumber)
{
	std::cout << cardNumber << std::endl;
	Command command;
	command.card = *game_->getCard(cardNumber);
	if (game_->canPlayCard()) {
		if (game_->isLegalPlay(cardNumber)) {
			command.type = PLAY;
			game_->humanAction(command);
		}
	}
	else{
		command.type = DISCARD;
		game_->humanAction(command);
	}
	
    notify();
}

// Get the tablecard value
std::vector<int> Model::getTableCardValues() const{
	return game_->getTableCardValues();
}

// Sets up the round
void Model::setupRound(){
    if (game_->winnerExists()) {
        gameStatus_ = false;
        //do something with winners here
    }
    else {
    	game_->newRound();
    }
    notify();
}

// Check if the round has started
bool Model::isRoundStatusStart() const{
	if (game_->status() == START){
		return true;
	}
	return false;
}

// Check if the round is active
bool Model::isRoundStatusActive() const{
	if (game_->status() == ACTIVE){
		return true;
	}
	return false;
}

// Check if the round is waiting
bool Model::isRoundStatusWait() const{
	if (game_->status() == WAIT){
		return true;
	}
	return false;
}

// Check if the round has ended
bool Model::isRoundStatusEnd() const{
	if (game_->status() == END){
		return true;
	}
	return false;
}

// Check if the card is a legal move
bool Model::isLegal(int cardNumber) const
{
	return game_->isLegalPlay(cardNumber);
}

// Check if the player can only discard
bool Model::isDiscardOnly() const
{
	return !game_->canPlayCard();
}

// Returns the score
std::vector<int> Model::scores() const {
	return game_->scores();
}

// Return the discards
std::vector<int> Model::discards() const {
	return game_->discards();
}

// Return the current player number
int Model::currentPlayerNumber() const{
	return game_->currentPlayerNumber();
}

// Plays the round
void Model::playRound() {
	game_->playRound();
	notify();
}

// Return the current hand
std::vector<int> Model::currentHand() const{
	return game_->currentHand();
}

// Return the game history
std::string Model::gameHistory() const
{
	return game_->getGameHistory();
}