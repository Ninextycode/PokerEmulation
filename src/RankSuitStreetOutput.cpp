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
        case A:
            out << "A";
            break;
        case K:
            out << "K";
            break;
        case Q:
            out << "Q";
            break;
        case J:
            out << "J";
            break;
        case T:
            out << "T";
            break;
        case _9:
            out << "9";
            break;
        case _8:
            out << "8";
            break;
        case _7:
            out << "7";
            break;
        case _6:
            out << "6";
            break;
        case _5:
            out << "5";
            break;
        case _4:
            out << "4";
            break;
        case _3:
            out << "3";
            break;
        case _2:
            out << "2";
            break;
    }
    return out;
}

ostream& pkr::operator<<(ostream& out, const Suit& suit) {
    switch(suit) {
        case s:
            out << "s";
            break;
        case p:
            out << "p";
            break;
        case d:
            out << "d";
            break;
        case f:
            out << "f";
            break;
    }
    return out;
}
