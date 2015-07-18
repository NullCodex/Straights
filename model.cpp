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

Model::Model() : topCard_(-1), gameStatus_(false), seed_(0) {
	game_ = NULL;
	for (unsigned int i = 0; i < 4; i++){
		playerTypes_.push_back('h');
	}
}

Suit Model::suit(int suitNumber) {
  //if (topCard_ == -1) return NOSUIT;
  
  return (Suit) (suitNumber);
}

Rank Model::rank(int rankNumber) {
  //if (topCard_ == -1) return NORANK;

  return (Rank) (rankNumber);
}

char Model::playerType(int player) const{
	return playerTypes_[player];
}

bool Model::hasGameStarted() const{
	return gameStatus_;
}

void Model::nextCard() {
  if (topCard_ == numCards-1) return;

  topCard_ += 1;
  notify();

}

bool Model::isHuman(int playerNumber) const{
	if (playerTypes_[playerNumber] == 'h'){
		return true;
	}
	return false;
}

void Model::resetCards() {
  topCard_ = -1;
  notify();
}

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

void Model::endGame()
{
	if (game_!=NULL){
		delete game_;
		game_ = NULL;
	}
	gameStatus_ = false;
	// probably call the rage quit function
	std::cout << "endGame" << std::endl;
	notify();
}

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
		//ragequit
	}
	notify();
}

void Model::handButtonClicked(int cardNumber)
{
	std::cout << cardNumber << std::endl;
	if (game_->isLegalPlay(cardNumber)) {
        Command command;
        command.card = *game_->getCard(cardNumber);
        if (game_->canPlayCard()) {
            command.type = PLAY;
        }
        else {
            command.type = DISCARD;
        }
       	game_->humanAction(command);
    }
    notify();
}

std::vector<int> Model::getTableCardValues() const{
	return game_->getTableCardValues();
}

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

bool Model::isRoundStatusStart() const{
	if (game_->status() == START){
		return true;
	}
	return false;
}

bool Model::isRoundStatusActive() const{
	if (game_->status() == ACTIVE){
		return true;
	}
	return false;
}

bool Model::isRoundStatusWait() const{
	if (game_->status() == WAIT){
		return true;
	}
	return false;
}

bool Model::isRoundStatusEnd() const{
	if (game_->status() == END){
		return true;
	}
	return false;
}

std::vector<int> Model::scores() const {
	return game_->scores();
}

std::vector<int> Model::discards() const {
	return game_->discards();
}

int Model::currentPlayerNumber() const{
	return game_->currentPlayerNumber();
}

void Model::playRound() {
	game_->playRound();
	notify();
}

std::vector<int> Model::currentHand() const{
	return game_->currentHand();
}