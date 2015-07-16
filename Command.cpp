#include "Command.h"
#include <cassert>
#include <sstream>
using namespace std;

// cin the commands from the user ie human player
istream &operator>>(istream &in, Command &c){
	c.type = BAD_COMMAND;
	
	string cmd;
	in >> cmd;
	
	// Cases depending on what the user inputs
	if (cmd == "play") {
		c.type = PLAY;
		in >> c.card;
	} else if (cmd == "discard") {
		c.type = DISCARD;
		in >> c.card;
	} else if (cmd == "deck") {
		c.type = DECK;
	} else if (cmd == "quit") {
		c.type = QUIT;
	} else if (cmd == "ragequit") {
		c.type = RAGEQUIT;
	}
	
	// Assertion for bad commands
	assert(!in.fail() && c.type != BAD_COMMAND);
	
	return in;
}
