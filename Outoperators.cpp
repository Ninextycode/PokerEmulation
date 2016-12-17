#include "PokerSimuator.h"

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