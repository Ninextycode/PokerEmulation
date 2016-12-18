#include "data_structs.h"

using namespace pkr;
using namespace std;


Action::ActionBuilder& Action::ActionBuilder::setMoney(int money) {
    this->money = money;
    this->moneySet = true;
    return *this;
}

Action::ActionBuilder& Action::ActionBuilder::setPlayer(weak_ptr<Player>player) {
    this->player = player;
    this->playerSet = true;
    return *this;
}

Action::ActionBuilder& Action::ActionBuilder::setStreet(Street street) {
    this->street = street;
    this->streetSet = true;
    return *this;
}


#define bool_str(b) ((b)?"true":"false")
Action Action::ActionBuilder::build() {
    if(!(streetSet && moneySet && playerSet)) {
        throw logic_error((string)"Cannot build Action. Not enough data." + 
                " Player is set: " + bool_str(playerSet) +
                " Money is set: " + bool_str(moneySet) +
                " Street is set: " + bool_str(streetSet));
    }
    return Action(money, street, player);
}
