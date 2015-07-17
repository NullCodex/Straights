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


Model::Model() : topCard_(-1), NUMPLAYERS(4) {
	game_ = NULL;
	for (unsigned int i = 0; i < NUMPLAYERS; i++){
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

void Model::nextCard() {
  if (topCard_ == numCards-1) return;

  topCard_ += 1;
  notify();

}


void Model::resetCards() {
  topCard_ = -1;
  notify();
}

void Model::newGame(std::string seed)
{
	std::stringstream ss;
	ss << seed;
	// take the value and move it into our seed variable
	std::cout << "newGame" << std::endl;
}

void Model::endGame()
{
	// probably call the rage quit function
	std::cout << "endGame" << std::endl;
	notify();
}

void Model::playerButtonClicked(int playerNumber)
{
	if (game_ == NULL){ //game hasn't started, can still switch player types
		if (playerTypes_[playerNumber] == 'h'){
			playerTypes_[playerNumber] = 'c';
		}
		else{
			playerTypes_[playerNumber] = 'h';	
		}
		//update view
	}
	// can replace with computer here

}

void Model::handButtonClicked(int cardNumber)
{
	std::cout << cardNumber << std::endl;

}