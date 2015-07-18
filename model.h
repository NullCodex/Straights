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
#include "Game.h"

const int numSuits = 4;
const int numCards = 52;

//
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
    Suit suit(int);
    Rank rank(int);
    void nextCard();
    void resetCards();
    void newGame(std::string);
    void endGame();
    void playerButtonClicked(int);
    void handButtonClicked(int);
    void setupRound();
    char playerType(int) const;
    bool hasGameStarted() const;
    bool isHuman(int) const;
    bool isRoundStatusStart() const;
    bool isRoundStatusActive() const;
    bool isRoundStatusWait() const;
    bool isRoundStatusEnd() const;
    std::vector<int> scores() const;
    std::vector<int> discards() const;
    int currentPlayerNumber() const;
    void playRound();
    std::vector<int> currentHand() const;
    std::string errorMessage() const;
    std::vector<int> getTableCardValues() const;
private:
    bool gameStatus_;
    int topCard_;
    Game* game_;
    std::vector <char> playerTypes_;
    int seed_;
}; // Model


#endif
