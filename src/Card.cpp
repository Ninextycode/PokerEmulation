#include "data_structures.h"

using namespace pkr;
using namespace std;

Card::Card(Rank rank, Suit suit) {
    this->rank = rank;
    this->suit = suit;
}

Card::Card(){
    
}

ostream& pkr::operator <<(std::ostream& out, const Card& card) {
    out << card.rank << card.suit;
    return out;
}