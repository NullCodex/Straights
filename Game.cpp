#include "Game.h"
#include <iostream>
#include <set>

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
	table_.clear();
	possiblePlays_.clear();
	deck_.shuffle();
	for (unsigned int i = 0; i < players_.size(); i++){
		players_[i]->discardHand();
		players_[i]->newHand(i, deck_);
	}
	determineFirstPlayer();
	currentPlayer_ = firstPlayer_;
	std::cout << "A new round begins. It's player " << (firstPlayer_+1) << "'s turn to play." << std::endl;
}

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

void Game::playRound(){
	updatePossiblePlays();
	if (playerTypes_[currentPlayer_] == 'h'){
		status_ = WAIT;
	}
	else{
		Computer* computer = dynamic_cast<Computer*>(players_[currentPlayer_]);
		std::cout << "Player " << (currentPlayer_+1) << " ";
		players_[currentPlayer_]->legalPlays(possiblePlays_);
		Card* card = computer->getLastCardPlayed();
		if (card != NULL){
			table_.placeCard(card);
		}
	}
}

bool Game::isRoundOver() const{
	return players_[currentPlayer_]->isHandEmpty();
}
void Game::humanAction (Command c){
	status_ = ACTIVE;
	if (c.type == PLAY){
		Card* card = getCardReference(c.card);
		Human* human = dynamic_cast<Human*>(players_[currentPlayer_]);
		human->playCard(card, possiblePlays_); // PLays the card
		std::cout << "Player " << (currentPlayer_ + 1) << " plays " << *card << "." << std::endl;
		table_.placeCard(card); // Place the card onto the type	
	}	
	else{
		// Discard the desired card
		Card* card = getCardReference(c.card);
		players_[currentPlayer_]->discardCard(card);
		std::cout << "Player " << (currentPlayer_ + 1) << " discards " << *card << "." << std::endl;
	}
	nextPlayer();
}

void Game::nextPlayer(){
	currentPlayer_ = (currentPlayer_ + 1) %4;
	if (currentPlayer_ == firstPlayer_){
		status_ = END;
	}
}

std::vector<int> Game::getTableCardValues() const{
	std::vector<Card*> cards = table_.cardsOnTable();
	std::vector<int> cardValues;
	for (unsigned int i = 0; i < cards.size(); i++){
		cardValues.push_back(cards[i]->getRank() + 13*cards[i]->getSuit());
	}
	return cardValues;
}

bool Game::isLegalPlay(int cardNumber) const{
	return players_[currentPlayer_]->isLegalPlay(cardNumber, possiblePlays_);
}

bool Game::canPlayCard() const{
	return players_[currentPlayer_]->canPlayCard(possiblePlays_);
}

Card* Game::getCard(int cardNumber) const{
	return players_[currentPlayer_]->getCard(cardNumber);
}

std::vector<int> Game::currentHand() const{
	return players_[currentPlayer_]->currentHand();
}
// Game function to control the flow of the game
void Game::nextTurn(){
	int curPlayer = firstPlayer_;
	for (unsigned int i = 0; i < players_.size() && !quit_; i++){
		updatePossiblePlays();
		// Grab a command from the user if the player is a human type
		if (playerTypes_[curPlayer] == 'h'){
			Command c;
			outputCurrentTable();
			std::cout << "Your hand:" << *players_[curPlayer] << std::endl;
			std::cout << "Legal plays:";
			players_[curPlayer]->legalPlays(possiblePlays_);
			std::cout << "\n";
			c.type = DECK;
			while (c.type == DECK && !quit_){
				std::cout << ">";
				std::cin >> c;
/*
				if (c.type == PLAY){
					try{
						Card* card = getCardReference(c.card);
						Human* human = dynamic_cast<Human*>(players_[curPlayer]);
						human->playCard(card, possiblePlays_); // PLays the card
						std::cout << "Player " << (curPlayer + 1) << " plays " << *card << "." << std::endl;
						table_.placeCard(card); // Place the card onto the type
					}
					catch (Human::InvalidCardException &e){
						std::cout << "This is not a legal play." << std::endl;
						c.type = DECK;
					}
				}

				else if (c.type == DISCARD){
					try{
						// Discard the desired card
						Card* card = getCardReference(c.card);
						Human* human = dynamic_cast<Human*>(players_[curPlayer]);
						human->discardCard(card, possiblePlays_);
						std::cout << "Player " << (curPlayer + 1) << " discards " << *card << "." << std::endl;
					}
					catch (Human::CanPlayCardException &e){
						std::cout << "You have a legal play. You may not discard." << std::endl;
						c.type = DECK;
					}
				}
				
				else if (c.type == DECK){
					std::cout << deck_ << std::endl; // prints the deck
				}
				else if (c.type == QUIT){
					quit_ = true;
				}
				else{ //ragequit: replace the current human player with a computer player
					Human* temp = dynamic_cast<Human*>(players_[curPlayer]);
					players_[curPlayer] = new Computer(players_[curPlayer]);
					delete temp;
					std::cout << "Player " << (curPlayer + 1) << " ragequits. A computer will now take over." << std::endl;
					playerTypes_[curPlayer] = 'c';
					curPlayer--;
					i--;
				}
				*/
			}
		}
		else{
			//Do Computer player's turn: basic ai which will play the first legal card if no legal plays exists, discard the first one
			Computer* computer = dynamic_cast<Computer*>(players_[curPlayer]);
			std::cout << "Player " << (curPlayer+1) << " ";
			players_[curPlayer]->legalPlays(possiblePlays_);
			Card* card = computer->getLastCardPlayed();
			if (card != NULL){
				table_.placeCard(card);
			}
			
		}
		curPlayer = (curPlayer + 1) % 4;
	}
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
void Game::endRound() {
	for (unsigned int i = 0; i < players_.size(); i++){
		std::cout << "Player " << (i + 1) << "'s discards:";
		players_[i]->outputDiscardList();
		std::cout << "Player " << (i + 1) << "'s score: " << players_[i]->getScore() << " + " << players_[i]->valueOfDiscarded() <<
			" = " << (players_[i]->getScore() + players_[i]->valueOfDiscarded()) << std::endl;
		players_[i]->updateScore();
	}

}

// Output the winner/winners of the game
void Game::outputWinners() const{
	std::set<int> scores;
	for (unsigned int i = 0; i < players_.size(); i++){
		scores.insert(players_[i]->getScore());
	}
	for (unsigned int i = 0; i < players_.size(); i++){
		if (*scores.begin() == players_[i]->getScore()){
			std::cout << "Player " << (i + 1) << " wins!\n";
		}
	}
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

RoundStatus Game::status() const{
	return status_;
}

std::vector<int> Game::scores() const{
	std::vector<int> playerScores;
	for (int i = 0; i < 4; i++){
		playerScores.push_back(players_[i]->getScore());
	}
	return playerScores;
}

std::vector<int> Game::discards() const{
	std::vector<int> playerDiscards;
	for (int i = 0; i < 4; i++){
		playerDiscards.push_back(players_[i]->numDiscards());
	}
	return playerDiscards;
}