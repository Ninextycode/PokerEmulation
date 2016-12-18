#include "data_structs.h"

using namespace pkr;
using namespace std;

Action::Action(int money, Street street, 
        weak_ptr<Player> player) {
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

weak_ptr<const Player> Action::getPlayer() {
    return player;
}

ostream& pkr::operator <<(std::ostream& out, const Action& action) {
    out << action.player.lock()->getName() << " put " << action.money << " on " << action.street;
    return out;
}