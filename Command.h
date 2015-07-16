#ifndef _COMMAND_
#define _COMMAND_

#include "Card.h"
#include <istream>

//Possible commands
enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };

//Keeps track of command type and card inputted for the command
struct Command{
	Type type;
	Card card;
	
	Command() : type(BAD_COMMAND), card(SPADE, ACE) {}
};

//overriding input operator to handle inputting commands
std::istream &operator>>(std::istream &, Command &);

#endif