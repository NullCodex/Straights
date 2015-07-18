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


#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include "DeckGUI.h"
#include "observer.h"

class Controller;
class Model;


class View : public Gtk::Window, public Observer {
public:
        View( Controller*, Model* );
	virtual ~View();
	virtual void update();	// Observer Pattern: concrete update() method
private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	
	// Card Images
	DeckGUI deck;
	
	/*
	// Member widgets:
	Gtk::HBox panels;      // Main window divided into two horizontal panels
	Gtk::VBox butBox;      // Vertical boxes for stacking buttons vertically
	Gtk::Button next_button;
	Gtk::Button reset_button;
	Gtk::Button startButton;
	Gtk::Button endButton;
	Gtk::Image card;
	Gtk::Table playerHand;
	*/

	/*
	Gtk::HBox mainPanel;
	Gtk::HBox secondPanel;
	Gtk::HBox thirdPanel;
	Gtk::VBox optionSelect;
	Gtk::VBox butBox;
	Gtk::Button next_button;
	Gtk::Button reset_button;
	Gtk::Button startButton;
	Gtk::Button endButton;
	Gtk::Image card;
	Gtk::Table playerHand;
	Gtk::Image cards[13];
	*/

	Gtk::VBox rootWindow;

	// game start, end and seed components
	Gtk::HBox startEndRow;
	Gtk::Button startButton;
	Gtk::Entry seedField;
	Gtk::Button endButton;

	// table components
	Gtk::Frame tableCardFrames[4][13];
	Gtk::Frame tableFrame;
	Gtk::VBox tableContainer;
	Gtk::HBox cardRows[4];
	Gtk::Image * card[4][13];

	// player button and score components
	Gtk::Button playerButtons[4];
	Gtk::Frame playerFrames[4];
	Gtk::Label nameLabels[4];
	Gtk::Label discardLabels[4];
	Gtk::Label playerButton[4];
	Gtk::VBox playerColumn[4];
	Gtk::HBox playerRow;

	// player hand components
	Gtk::HBox handRow;
	Gtk::Frame handFrame;
	Gtk::Image * handImages[13];
	Gtk::Button * handButtons[13];

	Gtk::Image tempCard;


	// Signal handlers:
	void nextButtonClicked();
	void resetButtonClicked();


	void newGame();
	void endGame();

	void playerButtonClicked(int);
	void handButtonClicked(int);
	void enableRageOption();
	void displayHand();

	void changePlayerLabel(int);
	void clearTable();
	void clearHand();
	void resetScore();
	void updateTable();
	void updateScores();
	void updateDiscards();
	void startRound();
	void endRound();
	void nextTurn();
	void startRoundDialogClicked();
	void endRoundDialogClicked();
	void endGameDialogClicked();

	void createDialog(std::string);
}; // View

#endif

