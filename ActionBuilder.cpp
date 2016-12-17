#include "PokerSimuator.h"

using namespace pkr;
using namespace std;

Action::ActionBuilder::ActionBuilder() {
    
}

std::shared_ptr<Action::ActionBuilder> Action::ActionBuilder::build_ptr(){
    auto a = new Action::ActionBuilder();
    return std::shared_ptr<Action::ActionBuilder>(a);
}

shared_ptr<Action::ActionBuilder> Action::ActionBuilder::setMoney(int money) {
    this->money = money;
    this->moneySet = true;
    return shared_from_this();
}

shared_ptr<Action::ActionBuilder> Action::ActionBuilder::setPlayer(std::string player) {
    this->player = player;
    this->playerSet = true;
    return shared_from_this();;
}

shared_ptr<Action::ActionBuilder> Action::ActionBuilder::setStreet(Street street) {
    this->street = street;
    this->streetSet = true;
    return shared_from_this();;
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





Action::ActionBuilder2& Action::ActionBuilder2::setMoney(int money) {
    this->money = money;
    this->moneySet = true;
    return *this;
}

Action::ActionBuilder2& Action::ActionBuilder2::setPlayer(std::string player) {
    this->player = player;
    this->playerSet = true;
    return *this;
}

Action::ActionBuilder2& Action::ActionBuilder2::setStreet(Street street) {
    this->street = street;
    this->streetSet = true;
    return *this;
}

#define bool_str(b) ((b)?"true":"false")
Action Action::ActionBuilder2::build() {
    if(!(streetSet && moneySet && playerSet)) {
        throw logic_error((string)"Cannot build Action. Not enough data." + 
                " Player is set: " + bool_str(playerSet) +
                " Money is set: " + bool_str(moneySet) +
                " Street is set: " + bool_str(streetSet));
    }
    return Action(money, street, player);
}