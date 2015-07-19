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


#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H


#include <gtkmm.h>

class Model;

class Controller {
// public controller functions
public:
   Controller( Model* );
   void newGame(std::string);
   void endGame();
   void newRound();
   void playerButtonClicked(int);
   void handButtonClicked(int);
   void playRound();
private:
   Model *model_;
}; // Controller


#endif

