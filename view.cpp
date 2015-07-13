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
#include <iostream>
#include <string>

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c),  startButton("Start new game with seed:"), endButton("End current game"){

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
	rootWindow.add(startEndRow);

	// Bind start and end button signal
	startButton.signal_clicked().connect(sigc::mem_fun(*this, &View::restartGame));
	endButton.signal_clicked().connect(sigc::mem_fun(*this, &View::endGame));

	// Setup the table of cards
	tableFrame.set_label("Cards on the table");
	tableFrame.add(tableContainer);
	rootWindow.add(tableFrame);

	// Initialize the playing field
	for (unsigned int y = 0; y < 4; y++) {
		for (unsigned int i = 0; i < 13; i++ ) {
			card[y][i] = Gtk::manage(new Gtk::Image( nullCardPixbuf ));
			tableCardFrames[y][i].add(*card[y][i]);
			cardRows[y].add( tableCardFrames[y][i] );
		}
		tableContainer.add( cardRows[y] );
	}

		// Setup the players
	for (unsigned int x = 0; x < 4; x++) {
		std::stringstream ss;
		ss << x + 1;
		playerButtons[x].set_label("Human");
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
		handImages[y] = Gtk::manage(new Gtk::Image( nullCardPixbuf ));
		handButtons[y] = Gtk::manage(new Gtk::Button());
		handButtons[y]->set_image(*handImages[y]);
		//handButtons[y]->set_sensitive(false);
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

} // View::View

View::~View() {}


void View::update() {
  Suit suit = model_->suit();
  Rank rank = model_->rank();
  if ( suit == NOSUIT ) 
    tempCard.set( deck.null() );
  else
    tempCard.set( deck.image(rank, suit) );

}

void View::nextButtonClicked() {
  controller_->nextButtonClicked();
} // View::nextButtonClicked

void View::resetButtonClicked() {
  controller_->resetButtonClicked();
} // View::resetButtonClicked

void View::restartGame()
{
	controller_->newGame(seedField.get_text());
}

void View::endGame()
{
	controller_->endGame();
}

void View::playerButtonClicked(int playerNumber)
{
	controller_->playerButtonClicked(playerNumber);
}

void View::handButtonClicked(int cardNumber)
{
	std::cout << "check" << std::endl;
	controller_->handButtonClicked(cardNumber);
}