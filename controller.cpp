/*
 * MVC example of GTKmm program
 *
 * Controller class.  Is responsible for translating UI events (from the View)
 * into method calls to the Model.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include "controller.h"
#include "model.h"


Controller::Controller(Model *m) : model_(m) {}

// Calls the model's new game function
void Controller::newGame(std::string seed)
{
	model_->newGame(seed);
}

// Calls the model's end game function
void Controller::endGame()
{
	model_->endGame();
}

// Calls the model's playbutton clicked function
void Controller::playerButtonClicked(int playerNumber)
{
	model_->playerButtonClicked(playerNumber);
}

// Calls the model's handbuttonclicked function
void Controller::handButtonClicked(int cardNumber)
{
	model_->handButtonClicked(cardNumber);
}

// Calls the model to set up a new round
void Controller::newRound(){
	model_->setupRound();
}

// Calls the model's playround function
void Controller::playRound(){
	model_->playRound();
}