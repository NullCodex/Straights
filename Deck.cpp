#include "Deck.h"
//Constructor, creates a deck and assigns seed_ to input seed parameter
Deck::Deck(int seed){
	seed_ = seed;
	for (int i = 0; i < 52; i++){
		cards_.push_back(new Card(Suit(i/13), Rank(i%13)));	//Creates an ordered deck
	}
}

//Destructor: deletes card* in vector
Deck::~Deck(){
	for (int i = 0; i < cards_.size(); i++){
		delete cards_[i];
	}
}

//shuffles cards in the deck
void Deck::shuffle(){
	static std::mt19937 rng(seed_);
	int n = Card::CARD_COUNT;

	while (n > 1) {
		int k = (int)(rng() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

//Returns the card* in deck at index i
Card* Deck::getCard(int i){
	return cards_[i];
}

//Outputs the deck 13 cards per line
std::ostream &operator<< (std::ostream & sout, const Deck & deck){
	int i = 0;
	sout << *deck.cards_[i];
	for (i = 1; i < deck.cards_.size(); i++){
		if (i % 13 == 0){
			sout << "\n";
			sout << *deck.cards_[i];
		}
		else{
			sout << " " << *deck.cards_[i];
		}
	}
	return sout;
}