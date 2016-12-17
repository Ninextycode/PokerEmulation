#include "PokerSimuator.h"

using namespace pkr;
using namespace std;

Action::Action(int money, Street street, 
        string player) {
    this->money = money;
    this->player = player;
    this->street = street;
}

int Action::getMoney() {
    return money;
}

Street Action::getStreet() {
    return street;
}

string Action::getPlayer() {
    return player;
}

ostream& pkr::operator <<(std::ostream& out, const Action& action) {
    out << action.player << " put " << action.money << " on " << action.street;
    return out;
}