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


#ifndef MVC_MODEL_H
#define MVC_MODEL_H

#include "subject.h"
#include <string>
#include <sstream>
#include <iostream>



enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };
const int numSuits = 4;
const int numCards = 52;
/*
const int numFaces = 6;
const int numSuits = 4;
const int numCards = numFaces * numSuits;

enum Faces { NINE, TEN, JACK, QUEEN, KING, ACE, NOFACE };
enum Suits { DIAMOND, CLUB, HEART, SPADE, NOSUIT };
*/

class Model : public Subject {
public:
    Model();
    Suit suit();
    Rank rank();
    void nextCard();
    void resetCards();
    void newGame(std::string);
    void endGame();
    void playerButtonClicked(int);
    void handButtonClicked(int);
private:
    int topCard_;
}; // Model


#endif
