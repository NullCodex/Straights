/*
 *  Deck.cc
 *  
 *
 *  Created by Caroline Kierstead on 25/05/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */
#include "DeckGUI.h"
#include <algorithm>
#include <iterator>
#include <string>
using std::string;
using std::transform;

// Sets up an array of the Portable Network Graphics (PNG) file names that contain the necessary card images.
// The deck will load the contents into pixel buffers for later use.
const char * image_names[] = {
	// Set up all clubs
	"cards_png/img/0_0.png",
	"cards_png/img/0_1.png",
	"cards_png/img/0_2.png",
	"cards_png/img/0_3.png",
	"cards_png/img/0_4.png",
	"cards_png/img/0_5.png",
	"cards_png/img/0_6.png",
	"cards_png/img/0_7.png",
	"cards_png/img/0_8.png",
	"cards_png/img/0_9.png",
	"cards_png/img/0_j.png",
	"cards_png/img/0_q.png",
	"cards_png/img/0_k.png",
	// setup all diamonds
	"cards_png/img/1_0.png",
	"cards_png/img/1_1.png",
	"cards_png/img/1_2.png",
	"cards_png/img/1_3.png",
	"cards_png/img/1_4.png",
	"cards_png/img/1_5.png",
	"cards_png/img/1_6.png",
	"cards_png/img/1_7.png",
	"cards_png/img/1_8.png",
	"cards_png/img/1_9.png",
	"cards_png/img/1_j.png",
	"cards_png/img/1_q.png",
	"cards_png/img/1_k.png",
	// setup all hearts
	"cards_png/img/2_0.png",
	"cards_png/img/2_1.png",
	"cards_png/img/2_2.png",
	"cards_png/img/2_3.png",
	"cards_png/img/2_4.png",
	"cards_png/img/2_5.png",
	"cards_png/img/2_6.png",
	"cards_png/img/2_7.png",
	"cards_png/img/2_8.png",
	"cards_png/img/2_9.png",
	"cards_png/img/2_j.png",
	"cards_png/img/2_q.png",
	"cards_png/img/2_k.png",
	// setup all spaces
	"cards_png/img/3_0.png",
	"cards_png/img/3_1.png",
	"cards_png/img/3_2.png",
	"cards_png/img/3_3.png",
	"cards_png/img/3_4.png",
	"cards_png/img/3_5.png",
	"cards_png/img/3_6.png",
	"cards_png/img/3_7.png",
	"cards_png/img/3_8.png",
	"cards_png/img/3_9.png",
	"cards_png/img/3_j.png",
	"cards_png/img/3_q.png",
	"cards_png/img/3_k.png",
	/*   
	// Set up NINE of {DIAMOND,CLUB,HEART,SPADE}
	"cards_png/0_0.png", "cards_png/0_1.png", "cards_png/0_2.png", "cards_png/0_3.png",
	// Set up TEN of {DIAMOND,CLUB,HEART,SPADE}
	"cards_png/1_0.png", "cards_png/1_1.png", "cards_png/1_2.png", "cards_png/1_3.png",
	// Set up JACK of {DIAMOND,CLUB,HEART,SPADE}
	"cards_png/2_0.png", "cards_png/2_1.png", "cards_png/2_2.png", "cards_png/2_3.png",
	// Set up QUEEN of {DIAMOND,CLUB,HEART,SPADE}
	"cards_png/3_0.png", "cards_png/3_1.png", "cards_png/3_2.png", "cards_png/3_3.png",
	// Set up KING of {DIAMOND,CLUB,HEART,SPADE}
	"cards_png/4_0.png", "cards_png/4_1.png", "cards_png/4_2.png", "cards_png/4_3.png",
	// Set up ACE of {DIAMOND,CLUB,HEART,SPADE}
	"cards_png/5_0.png", "cards_png/5_1.png", "cards_png/5_2.png", "cards_png/5_3.png",
	// Set up the back of a card for a place holder/null card
	"cards_png/back_1.png"
	*/
}; 

// Loads the image from the specified file name into a pixel buffer.
Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string & name) {
	return Gdk::Pixbuf::create_from_file( name );
} // createPixbuf

DeckGUI::DeckGUI()  {
	// Images can only be loaded once the main window has been initialized, so cannot be done as a static
	// constant array. Instead, use the STL transform algorithm to apply the method createPixbuf to every
	// element in the array of image names, starting with first and ending with the last. New elements are
	// added to the back of deck.
	transform( &image_names[0], &image_names[G_N_ELEMENTS(image_names)], 
			   std::back_inserter(deck), &createPixbuf );
} // DeckGUI::DeckGUI

DeckGUI::~DeckGUI() {
} // DeckGUI::~DeckGUI

// Returns the image for the specified card.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::image( Rank r, Suit s ) {
	int index = ((int) r)*4 + ((int) s );
	return deck[ index ];
} // DeckGUI::getCardImage 

// Returns the image to use for the placeholder.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::null() {
	int size = deck.size();
	return deck[ size-1 ];
} // DeckGUI::getNullCardImage

