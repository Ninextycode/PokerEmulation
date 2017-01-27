#include "game.h"

using namespace pkr;
using namespace std;

int OneTwoGame::getInitialStack() const {
    return 10;
}

void OneTwoGame::playGame() {
    smallBlind = 1;
    bigBlind = 2;
    while(this->countPlayersWithChips() > 1) {
        this->playRound();
    }
}

void OneTwoGame::onStartRound() const{
    cout << "=== NEW ROUND ===" << endl;
    cout << "Button is " << playersData[button].getPlayer()->getName() << endl;
    for(auto pd: playersData) {
        cout << pd.getPlayer()->getName() << " starts with " << pd.getMoney() << endl;
    }
}

void OneTwoGame::onCardsDealt(std::shared_ptr<Player> player, Hand hand) const {
    cout << player->getName() << " gets " << hand << endl;
}

void OneTwoGame::onFlopDealt(vector<Card> flop) const {
    cout << "Flop is " 
            << flop[0] 
            << flop[1]
            << flop[2] << endl;
}

void OneTwoGame::onTurnDealt(Card turn) const {
    cout << "Turn is " 
            << turn << endl;
}


void OneTwoGame::onRiverDealt(Card river) const {
    cout << "River is " 
            << river << endl;
}

void OneTwoGame::onFinalCombinations(std::vector<Hand> hands, const std::vector<Card>& sharedCards) const {
    for(int i = 0; i < playersData.size(); i++) {
        if(playersData[i].isActive()) {
            cout << playersData[i].getPlayer()->getName() << " has " <<  hands[i] << "|" 
                    << sharedCards[0] << sharedCards[1] << sharedCards[2] << sharedCards[3] << sharedCards[4] << endl;
        }
    }
}

void OneTwoGame::onGameEnd() const {
    for(int i = 0; i < playersData.size(); i++) {
        cout << playersData[i].getPlayer()->getName()
                << " has " << playersData[i].getMoney() << " chips " << endl;
    }
}

void OneTwoGame::onNewAction(Action action) const {
    cout << action << endl;
}