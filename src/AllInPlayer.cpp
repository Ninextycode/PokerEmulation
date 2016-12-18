#include "player.h"

using namespace pkr;
using namespace std;

void AllInPlayer::markAsWinner() {
    
}

Action AllInPlayer::preformAction(const Game& currentGame) {
    throw runtime_error("not implemented");
}

string AllInPlayer::getName() {
    return this->name;
}