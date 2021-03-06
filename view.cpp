/*
 * MVC example of GTKmm program
 *
 * View class.  Is responsible for buttons (that user clicks) and for displaying
 * the top card of the deck.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include "DeckGUI.h"
#include "GameDialog.h"
#include <iostream>
#include <string>

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c),  startButton("Start new game with seed:"), endButton("End current game"), historyButton("Display history"){

	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.null();

	// Sets some properties of the window.
    set_title( "Straights" );
	set_border_width( 10 );
	
	add(rootWindow);

	// Setup the top row for starting and ending
	seedField.set_text("0");
	startEndRow.add(startButton);
	startEndRow.add(seedField);
	startEndRow.add(endButton);
	startEndRow.add(historyButton);
	rootWindow.add(startEndRow);

	// Bind start end and history button
	startButton.signal_clicked().connect(sigc::mem_fun(*this, &View::newGame));
	endButton.signal_clicked().connect(sigc::mem_fun(*this, &View::endGame));
	historyButton.signal_clicked().connect(sigc::mem_fun(*this, &View::displayHistory));

	// Setup the table of cards
	tableFrame.set_label("Cards on the table");
	tableFrame.add(tableContainer);
	rootWindow.add(tableFrame);

	// Initialize the playing field
	for (unsigned int y = 0; y < 4; y++) {
		for (unsigned int i = 0; i < 13; i++ ) {
			Glib::RefPtr<Gdk::Pixbuf> temp = deck.image(model_->rank(i), model_->suit(y));
			card[y][i] = Gtk::manage(new Gtk::Image( temp ));
			tableCardFrames[y][i].add(*card[y][i]);
			cardRows[y].add( tableCardFrames[y][i] );
		}
		tableContainer.add( cardRows[y] );
	}

		// Setup the players
	for (unsigned int x = 0; x < 4; x++) {
		std::stringstream ss;
		ss << x + 1;
		if (m->playerType(x) == 'h'){
			playerButtons[x].set_label("Human");
		}
		else{
			playerButtons[x].set_label("Computer");
		}
		playerButtons[x].signal_clicked().connect( sigc::bind<int>( sigc::mem_fun(*this, &View::playerButtonClicked), x));
		playerFrames[x].set_label("Player " + ss.str());
		playerFrames[x].add(playerColumn[x]);
		nameLabels[x].set_text("0 points");
		discardLabels[x].set_text("0 discards");
		playerColumn[x].add(playerButtons[x]);
		playerColumn[x].add(nameLabels[x]);
		playerColumn[x].add(discardLabels[x]);
		playerRow.add(playerFrames[x]);
	}
	rootWindow.add(playerRow);


	// Setup the hand row
	for (unsigned int y = 0; y < 13; y++) {
		Glib::RefPtr<Gdk::Pixbuf> temp = deck.image(model_->rank(y), model_->suit(0));
		handImages[y] = Gtk::manage(new Gtk::Image( temp));
		handButtons[y] = Gtk::manage(new Gtk::Button());
		handButtons[y]->set_image(*handImages[y]);
		handButtons[y]->set_sensitive(false);
		handButtons[y]->signal_clicked().connect( sigc::bind<int>( sigc::mem_fun(*this, &View::handButtonClicked), y));
		handRow.add(*handButtons[y]);
	}
	handFrame.set_label("Your hand");
	handFrame.add(handRow);
	rootWindow.add(handFrame);

	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);
	clearTable();
	clearHand();

} // View::View

View::~View() {}


// View update function
void View::update() {
	if (model_->hasGameStarted()){
		if (model_->isRoundStatusStart()){
			startRound();
		}
		else if (model_->isRoundStatusWait()){
			enableRageOption();
			updateDiscards(); // Update discards
			displayHand(); //show hand
		}
		else if (model_->isRoundStatusEnd()){
			endRound();
		}
		else{ //Active
			updateTable();
			nextTurn();
		}
	}
	//createDialog("Winner");
}

// endRound function creates the dialog 
void View::endRound() {
	createDialog(model_->endRound());
	endRoundDialogClicked();
}

// Calls the end game function
void View::endRoundDialogClicked(){
	if (model_->winnerExists()){
		createDialog(model_->showWinners());
		endGameDialogClicked();
	}
	else{
		controller_->newRound();	
	}
	
}

// Ends the current game
void View::endGameDialogClicked(){
	endGame();
}

// Update the current player's hand
void View::displayHand(){
	std::vector<int> hand = model_->currentHand();
	for (unsigned int i = 0; i < 13; i++) {
		if (i < hand.size()) {
			handImages[i]->set(deck.image((Rank)(hand[i] % 13), (Suit)(hand[i] / 13)));
			if(!model_->isDiscardOnly())
			{
				if(model_->isLegal(i))
				{
					handButtons[i]->set_sensitive(true);
				}
				else
				{
					handButtons[i]->set_sensitive(false);
				}
			}
			else
			{
				handButtons[i]->set_sensitive(true);
			}
			
		}
		else {
			handButtons[i]->set_sensitive(false);
			handImages[i]->set(deck.null());
		}
	}
}

// Highlights the current player and disable the other players
void View::enableRageOption(){
	for (unsigned int i = 0; i < 4; i++){
		if (i!=model_->currentPlayerNumber()){
			playerButtons[i].set_sensitive(false);
			playerFrames[i].drag_unhighlight();
		}
		else{
			playerButtons[i].set_sensitive(true);
			playerFrames[i].drag_highlight();	
		}
	}
}


// Starts the a new round
void View::startRound(){
	std::vector <int> scores = model_->scores();
	std::vector <int> discards = model_->discards();
	clearHand();
	clearTable();
	updateScores();
	updateDiscards();
	std::stringstream message;
	for (unsigned int i = 0; i < 4; i++){
		playerButtons[i].set_sensitive(false);
		playerButtons[i].set_label("Rage!");
	}
	message << "A new round begins. It's player " << model_->currentPlayerNumber()+1 << "'s turn to play.";
	createDialog(message.str());
	startRoundDialogClicked();
}

// Action listener for the start round dialog
void View::startRoundDialogClicked() {
	controller_->playRound();
}

// Calls the next turn function
void View::nextTurn(){
	controller_->playRound();	
}

// Function to create a new dialog
void View::createDialog(std::string message){
	GameDialog dialog(*this, message);
}

// Grab the current table and update the table image
void View::updateTable(){
	std::vector<int> cardValues = model_->getTableCardValues();
	for (unsigned int i = 0; i < cardValues.size(); i++) {
		int row = cardValues[i] / 13;
		int column = cardValues[i] % 13;
		card[row][column]->set(deck.image((Rank)column, (Suit)row));
	}

}

// Updates the scores of the game
void View::updateScores()
{
	std::vector <int> scores = model_->scores();
	std::stringstream message;
	for(unsigned int i = 0; i < 4; i++)
	{
		message << scores[i] << " points";
		nameLabels[i].set_label(message.str());
		message.str(std::string()); //clear stream
	}
}

// Update the discard display
void View::updateDiscards(){
	std::vector <int> discards = model_->discards();
	std::stringstream message;
	for(unsigned int i = 0; i < 4; i++){
		message << discards[i] << " discards";
		discardLabels[i].set_text(message.str());
		message.str(std::string()); //clear stream
	}
}

// Reset the score labels
void View::resetScore()
{
	for(unsigned int i = 0; i < 4; i++)
	{
		nameLabels[i].set_text("0 points");
	}
}

// Changes the player label
void View::changePlayerLabel(int playerNumber) // use to change the label
{
	string label;
	if (model_->isHuman(playerNumber)){
		label = "Human";
	}
	else{
		label = "Computer";
	}
	playerButtons[playerNumber].set_label(label);
}

// Clear the table of all pictures
void View::clearTable() // Tested will work 
{
	for(unsigned int x = 0; x < 4; x++)
	{
		for(unsigned int y = 0; y < 13; y++)
		{
			card[x][y]->set(deck.null());
		}
	}
}

// Clear the hand and sets it to null pictures
void View::clearHand() // tested will work
{
	for(unsigned int i = 0; i < 13; i++)
	{
		handImages[i]->set(deck.null());
		handButtons[i]->set_sensitive(false);
	}
}

// Calls the controller for a new game
void View::newGame()
{
	historyButton.set_sensitive(true);
	controller_->newGame(seedField.get_text());
}

// Sets the view for end game
void View::endGame()
{
	controller_->endGame();
	clearTable();
	clearHand();
	for (unsigned int i = 0; i < 4; i++) {
		playerButtons[i].set_sensitive(true);
		nameLabels[i].set_label("0 points");
		discardLabels[i].set_label("0 discards");
		playerFrames[i].drag_unhighlight();		
		if (model_->isHuman(i)) {
			playerButtons[i].set_label("Human");
		}
		else {
			playerButtons[i].set_label("Computer");
		}
	}
	historyButton.set_sensitive(false);
}

// Display the game history 
void View::displayHistory()
{
	createDialog(model_->gameHistory());
}

// Action binded to a player button
void View::playerButtonClicked(int playerNumber)
{
	controller_->playerButtonClicked(playerNumber);
	if (!model_->hasGameStarted()){
		changePlayerLabel(playerNumber);
	}
}

// Action binded to hand buttons
void View::handButtonClicked(int cardNumber)
{
	controller_->handButtonClicked(cardNumber);
}
