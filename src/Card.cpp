#include "simple_data_structs.h"

using namespace pkr;
using namespace std;

int Card::toInt() {
    int x = rank * 4 + suit;
    return rank * 4 + suit;
}

Card::Card(Rank rank, Suit suit) {
    this->rank = rank;
    this->suit = suit;
}

Card::Card(){
    this->rank = (Rank)0;
    this->suit = (Suit)0;
}

ostream& pkr::operator <<(std::ostream& out, const Card& card) {
    out << card.rank << card.suit;
    return out;
}