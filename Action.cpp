#include "PokerSimuator.h"

using namespace pok;
using namespace std;

int Action::getMoney() {
    return money;
}

Move Action::getMove() {
    return move;
}

Street Action::getStreet() {
    return street;
}

std::shared_ptr<Player> Action::getPlayer() {
    return player.lock();
}