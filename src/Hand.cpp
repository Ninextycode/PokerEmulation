#include "data_structures.h"

using namespace std;
using namespace pkr;

Hand::Hand(Card c1, Card c2){
    this->c1 = c1;
    this->c2 = c2;
}

Hand::Hand() {
    
}

std::ostream& pkr::operator<<(std::ostream& out, const Hand& hand) {
    out << hand.c1 << hand.c2;
    return out;
}