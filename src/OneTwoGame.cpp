#include "game.h"

using namespace pkr;

void OneTwoGame::playGame() {
    smallBlind = 1;
    bigBlind = 2;
    while(this->countPlayersWithChips() > 1) {
        this->playRound();
    }
}