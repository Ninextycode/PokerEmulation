#include "simple_data_structs.h"

using namespace std;
using namespace pkr;

Hand::Hand(Card c1, Card c2){
    this->c1 = c1;
    this->c2 = c2;
}

Hand::Hand() {
    
}

ostream& pkr::operator <<(ostream& out, const Hand& hand) {
    out << hand.c1 << hand.c2;
    return out;
}