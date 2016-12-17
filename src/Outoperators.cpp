#include "data_structures.h"

using namespace pkr;
using namespace std;

ostream& pkr::operator<<(ostream& out, const Street& street) {
    switch(street) {
        case Street::preflop:
            out << "preflop";
            break;
        case Street::flop:
            out << "flop";
            break;
        case Street::turn:
            out << "turn";
            break;
        case Street::river:
            out << "river";
            break;
    }
    return out;
}

ostream& pkr::operator<<(ostream& out, const Rank& rank) {
    switch(rank) {
        case Rank::A:
            out << "A";
            break;
        case Rank::K:
            out << "K";
            break;
        case Rank::Q:
            out << "Q";
            break;
        case Rank::J:
            out << "J";
            break;
        case Rank::T:
            out << "T";
            break;
        case Rank::_9:
            out << "9";
            break;
        case Rank::_8:
            out << "8";
            break;
        case Rank::_7:
            out << "7";
            break;
        case Rank::_6:
            out << "6";
            break;
        case Rank::_5:
            out << "5";
            break;
        case Rank::_4:
            out << "4";
            break;
        case Rank::_3:
            out << "3";
            break;
        case Rank::_2:
            out << "2";
            break;
    }
    return out;
}

ostream& pkr::operator<<(ostream& out, const Suit& suit) {
    switch(suit) {
        case Suit::s:
            out << "s";
            break;
        case Suit::p:
            out << "p";
            break;
        case Suit::d:
            out << "d";
            break;
        case Suit::f:
            out << "f";
            break;
    }
    return out;
}
