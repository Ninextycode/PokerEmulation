#include "PokerSimuator.h"

using namespace pok;
using namespace std;

void Action::ActionBuilder::setMoney(int money) {
    Action::ActionBuilder a;
    a.money = money;
    a.move = move;
    a.player = player;
    a.street = street;
}

void Action::ActionBuilder::setMove(Move move) {
    Action::ActionBuilder a;
    a.money = money;
    a.move = move;
    a.player = player;
    a.street = street;
}

void Action::ActionBuilder::setPlayer(weak_ptr<Player> player) {
    Action::ActionBuilder a;
    a.money = money;
    a.move = move;
    a.player = player;
    a.street = street;
}

void Action::ActionBuilder::setStreet(Street street) {
    Action::ActionBuilder a;
    a.money = money;
    a.move = move;
    a.player = player;
    a.street = street;
}

void Action::ActionBuilder::build() {
    return Action(money, move, street, player);
}