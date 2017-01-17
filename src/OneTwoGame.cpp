#include "game.h"

using namespace pkr;
using namespace std;

int OneTwoGame::getInitialStack() {
    return 10 + int(10 * ((float)std::rand())/ RAND_MAX);
}

void OneTwoGame::playGame() {
    smallBlind = 1;
    bigBlind = 2;
    while(this->countPlayersWithChips() > 1) {
        this->playRound();
    }
}

void OneTwoGame::onStartRound() {
    cout << "=== NEW ROUND ===" << endl;
    cout << "Button is " << playersData[button].getPlayer()->getName() << endl;
    for(auto pd: playersData) {
        cout << pd.getPlayer()->getName() << " starts with " << pd.getMoney() << endl;
    }
}

void OneTwoGame::onCardsDealed(std::shared_ptr<Player> player, Hand hand) {
    cout << player->getName() << " gets " << hand << endl;
}

void OneTwoGame::onFlopDealed() {
    cout << "Flop is " 
            << sharedCards[sharedCards.size() - 1] 
            << sharedCards[sharedCards.size() - 2]
            << sharedCards[sharedCards.size() - 3] << endl;
}

void OneTwoGame::onTurnDealed() {
    cout << "Turn is " 
            << sharedCards[sharedCards.size() - 1] << endl;
}


void OneTwoGame::onRiverDealed() {
    cout << "River is " 
            << sharedCards[sharedCards.size() - 1] << endl;
}

void OneTwoGame::onFinalCombinations(std::vector<Hand> hands, const std::vector<Card>& sharedCards) {
    for(int i = 0; i < playersData.size(); i++) {
        if(playersData[i].isActive()) {
            cout << playersData[i].getPlayer()->getName() << " has " <<  hands[i] << "|" 
                    << sharedCards[0] << sharedCards[1] << sharedCards[2] << sharedCards[3] << sharedCards[4] << endl;
        }
    }
}

void OneTwoGame::onGameEnd() {
    for(int i = 0; i < playersData.size(); i++) {
        cout << playersData[i].getPlayer()->getName()
                << " has " << playersData[i].getMoney() << " chips " << endl;
    }
}

void OneTwoGame::onNewAction(Action action) {
    cout << action << endl;
}