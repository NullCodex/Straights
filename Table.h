#ifndef _TABLE_
#define _TABLE_
#include "Card.h"
#include <vector>
#include <set>

class Table{
public:
	friend std::ostream &operator<< (std::ostream &, const Table &);
	void placeCard(Card*); //add card to table
	Card* lastCardPlayed(); // Return a pointer to the last game played
	void clear(); // Wipes the table
	std::vector <Card*> cardsOnTable() const; // Return the cards on table
private:
	std::vector <Card*> cardsOnTable_; // Cards on table
	std::set<int> clubs_;  // Cards of suit clubs that were played
	std::set<int> hearts_; // Cards of suit hearts that were played
	std::set<int> spades_; // Cards of suit spades that were played
	std::set<int> diamonds_; // Cards of suit diamonds that were played
};

std::ostream &operator<<(std::ostream &, const Table &); // Overloading the ostream operator

#endif
