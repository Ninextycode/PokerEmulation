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

Card::Card(const char* s) {
    switch(s[0]) {
        case 'A':
            this->rank = Rank::A;
            break;
        case 'K':            
            this->rank = Rank::K;
            break;
        case 'Q':
            this->rank = Rank::Q;
            break;
        case 'J':
            this->rank = Rank::J;
            break;
        case 'T':
            this->rank = Rank::T;
            break;
        case '9':
            this->rank = Rank::_9;
            break;
        case '8': 
            this->rank = Rank::_8;
            break;
        case '7': 
            this->rank = Rank::_7;
            break;
        case '6':        
            this->rank = Rank::_6;
            break;
        case '5':      
            this->rank = Rank::_5;
            break;
        case '4':      
            this->rank = Rank::_4;
            break;
        case '3':     
            this->rank = Rank::_3;
            break;
        case '2':          
            this->rank = Rank::_2;
            break;
        default:
            throw invalid_argument(s);
    }  
    switch(s[1]) {
        case 's':      
            this->suit = Suit::s;
            break;
        case 'c':     
            this->suit = Suit::c;
            break;
        case 'd':          
            this->suit = Suit::d;
            break;
        case 'h':          
            this->suit = Suit::h;
            break;    
        default:
            throw invalid_argument(s);
    }
}


Card::Card(){
    this->rank = (Rank)0;
    this->suit = (Suit)0;
}

ostream& pkr::operator <<(std::ostream& out, const Card& card) {
    out << card.rank << card.suit;
    return out;
}