#include "Game.h"
#include <iostream>
#include <set>
#include <sstream>

// Game constructor: pushes back new player instances into the vector
Game::Game(std::vector<char> players, int seed) : deck_(seed), playerTypes_(players), status_(START){
	quit_ = false;
	for (unsigned int i = 0; i < players.size(); i++){
		if (players[i] == 'h'){
			players_.push_back(new Human());
		}
		else{
			players_.push_back(new Computer());
		}
	}
}

// Destructor deletes the player instances to prevent memory leaks
Game::~Game(){
	for (unsigned int i = 0; i < players_.size(); i++){
		delete players_[i];
	}
}

// Creates a new round, each player gets a new hand and we determine the first player ie who has 7S
void Game::newRound(){
	status_ = START;
	table_.clear();
	possiblePlays_.clear();
	deck_.shuffle();
	for (unsigned int i = 0; i < players_.size(); i++){
		players_[i]->discardHand();
		players_[i]->newHand(i, deck_);
	}
	determineFirstPlayer();
	currentPlayer_ = firstPlayer_;
	std::stringstream message;
	message << "A new round begins. It's player " << (firstPlayer_+1) << "'s turn to play." << "\n";
	std::cout << message.str();
	gameMessage_ += message.str();
}

// Return the current player
int Game::currentPlayerNumber() const{
	return currentPlayer_;
}

// Function to check which existing player has the seven of spades
void Game::determineFirstPlayer(){
	for (unsigned int i = 0; i < players_.size(); i++){
		if (players_[i]->contains(SPADE, SEVEN)){
			firstPlayer_ = i;
			break;
		}
	}
}

// Game play round function
void Game::playRound(){
	updatePossiblePlays();
	if (playerTypes_[currentPlayer_] == 'h'){
		status_ = WAIT;
	}
	else{
		status_ = ACTIVE;
		Computer* computer = dynamic_cast<Computer*>(players_[currentPlayer_]);
		std::cout << "Player " << (currentPlayer_+1) << " ";
		players_[currentPlayer_]->legalPlays(possiblePlays_);
		Card* card = computer->getLastCardPlayed();
		if (card != NULL){
			//std::cout << "here\n";
			table_.placeCard(card);
		}
		nextPlayer();
	}
}

// Check if the round is over
bool Game::isRoundOver() const{
	return players_[currentPlayer_]->isHandEmpty();
}

// Play the human action
void Game::humanAction (Command c){
	status_ = ACTIVE;
	std::stringstream message;
	if (c.type == PLAY){
		Card* card = getCardReference(c.card);
		Human* human = dynamic_cast<Human*>(players_[currentPlayer_]);
		human->playCard(card, possiblePlays_); // PLays the card
		message << "Player " << (currentPlayer_ + 1) << " plays " << *card << "." << "\n";
		std::cout << message.str();
		gameMessage_ += message.str();
		table_.placeCard(card); // Place the card onto the type	
	}	
	else{
		// Discard the desired card
		Card* card = getCardReference(c.card);
		players_[currentPlayer_]->discardCard(card);
		message << "Player " << (currentPlayer_ + 1) << " discards " << *card << "." << "\n";
		gameMessage_ += message.str();
		std::cout << message.str();
	}
	nextPlayer();
}

// Move to the next player
void Game::nextPlayer(){
	currentPlayer_ = (currentPlayer_ + 1) % 4;
	if (isRoundOver()){
		status_ = END;
	}
}

// Get table card values
std::vector<int> Game::getTableCardValues() const{
	std::vector<Card*> cards = table_.cardsOnTable();
	std::vector<int> cardValues;
	for (unsigned int i = 0; i < cards.size(); i++){
		cardValues.push_back(cards[i]->getRank() + 13*cards[i]->getSuit());
	}
	return cardValues;
}

// Check if the card number is legal
bool Game::isLegalPlay(int cardNumber) const{
	return players_[currentPlayer_]->isLegalPlay(cardNumber, possiblePlays_);
}

// Check if the player can play any card
bool Game::canPlayCard() const{
	return players_[currentPlayer_]->canPlayCard(possiblePlays_);
}

// Returns a card pointer
Card* Game::getCard(int cardNumber) const{
	return players_[currentPlayer_]->getCard(cardNumber);
}

// Returns the current player's hand
std::vector<int> Game::currentHand() const{
	return players_[currentPlayer_]->currentHand();
}

// Grabs the card reference
Card* Game::getCardReference(Card card){
	Card* cardReference = NULL;
	for (int i = 0; i < 52; i++){
		if (*deck_.getCard(i) == card){
			cardReference = deck_.getCard(i);
			return cardReference;
		}
	}
	return cardReference;
}
// Prints the current table
void Game::outputCurrentTable() const{
	std::cout << "Cards on the table:\n" << table_;
}

bool Game::winnerExists() const // function to check we have a winner
{
	for(unsigned int i = 0; i < players_.size(); i++)
	{
		if(players_[i]->getScore() >= 80)
		{
			return true;
		}
	}
	return false;
}

bool Game::hasQuit() const{
	return quit_;
}

// Grabs the round score and also print the scores
std::string Game::endRound() {
	std::stringstream message;
	for (unsigned int i = 0; i < players_.size(); i++){
		message << "Player " << (i + 1) << "'s discards:";
		message << players_[i]->returnDiscardList();
		message << "Player " << (i + 1) << "'s score: " << players_[i]->getScore() << " + " << players_[i]->valueOfDiscarded() <<
			" = " << (players_[i]->getScore() + players_[i]->valueOfDiscarded()) << "\n";
		players_[i]->updateScore();
	}
	resetGameHistory();
	return message.str();
}

// Output the winner/winners of the game
std::string Game::getWinners() const{
	std::set<int> scores;
	std::stringstream message;
	for (unsigned int i = 0; i < players_.size(); i++){
		scores.insert(players_[i]->getScore());
	}
	for (unsigned int i = 0; i < players_.size(); i++){
		if (*scores.begin() == players_[i]->getScore()){
			message << "Player " << (i + 1) << " wins!\n";
		}
	}
	return message.str();
}

// Updates the possible plays for players
void Game::updatePossiblePlays(){
	Card* card = table_.lastCardPlayed();
	if (card==NULL){
		for (unsigned int i = 0; i < 52; i++){
			if (*deck_.getCard(i) == Card(SPADE, SEVEN)){
				possiblePlays_.insert(deck_.getCard(i));
				return;
			}
		}
	}
	else if (card->getSuit() == SPADE && card->getRank() == SEVEN){
		for (int i = 0; i < 52; i++){
			if (deck_.getCard(i)->getRank() == SEVEN){
				possiblePlays_.insert(deck_.getCard(i));
			}
		}
	}
	std::vector <Card*> possiblePlays;
	for (int i = 0; i < 52; i++){
		if (deck_.getCard(i)->getSuit() == card->getSuit()){
			if (abs(deck_.getCard(i)->getRank() - card->getRank()) == 1){
				possiblePlays.push_back(deck_.getCard(i));
			}
		}
	}
	
	for (unsigned int i = 0; i < (unsigned)possiblePlays.size(); i++){
		possiblePlays_.insert(possiblePlays[i]);		
	}
}

// Return the round status
RoundStatus Game::status() const{
	return status_;
}

// Get the game scores
std::vector<int> Game::scores() const{
	std::vector<int> playerScores;
	for (int i = 0; i < 4; i++){
		playerScores.push_back(players_[i]->getScore());
	}
	return playerScores;
}

// Return the discards
std::vector<int> Game::discards() const{
	std::vector<int> numDiscards;
	for (int i =0; i < players_.size(); i++){
		numDiscards.push_back(players_[i]->numDiscards());
	}
	return numDiscards;
}

// Ragequit function
void Game::ragequit(){
	std::stringstream message;
	status_ = ACTIVE;
	Human* temp = dynamic_cast<Human*>(players_[currentPlayer_]);
	players_[currentPlayer_] = new Computer(players_[currentPlayer_]);
	delete temp;
	message << "Player " << (currentPlayer_ + 1) << " ragequits. A computer will now take over." << "\n";
	gameMessage_ += message.str();
	std::cout << message.str();
	playerTypes_[currentPlayer_] = 'c';
}

// Reset the game history
void Game::resetGameHistory()
{
	gameMessage_ = "";
}

// Grabs the game history
std::string Game::getGameHistory() const
{
	return gameMessage_;
}