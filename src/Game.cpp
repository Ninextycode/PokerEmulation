#include "game.h"
#include "data_structs.h"

using namespace std;
using namespace pkr;

    
void Game::setPlayers(vector<shared_ptr<Player> > players) {
    for(auto player_ptr: players) {
        PlayerData pd;
        pd.player = player_ptr;
        this->playersData.push_back(pd);
    }
}

void Game::playRound() {
    prepareForRound();
    
    playPreflop();
    playFlop();
    playTurn();
    playRiver();
    
    distributeBanks();
}

void Game::prepareForRound() {
    prepareDeck();
    prepareActivePlayers();
    moveButton();
}

void Game::prepareDeck() {
    deck = Deck();
    deck.shuffle();
}

void Game::prepareActivePlayers() {
    activePlayersData = vector<PlayerData>();
    
    for(int i = 0; i < playersData.size(); i++) {
        auto pd = playersData[(i+button) % playersData.size()];
        if(pd.money > 0) {
            activePlayersData.push_back(pd);
        }
    };
};

void Game::moveButton() {
    button =  (button + 1) % playersData.size();
}

void Game::playPreflop() {
    dealHoleCards();
}

void Game::dealHoleCards() {
    for(auto pd: activePlayersData) {
        pd.hand = Hand(deck.popCard(), deck.popCard());
    }
}

void Game::playFlop() {
    dealFlop();
    playStreet();
}

void Game::dealFlop(){
    sharedCards.push_back(deck.popCard());
    sharedCards.push_back(deck.popCard());
    sharedCards.push_back(deck.popCard());
}

void Game::playTurn() {
    dealTurn();
    playStreet();
}

void Game::dealTurn(){
    sharedCards.push_back(deck.popCard());
}

void Game::playRiver() {
    dealRiver();
    playStreet();
}

void Game::dealRiver(){
    sharedCards.push_back(deck.popCard());
}

void Game::playStreet() {
    int endPlayerIndex = activePlayersData.size();
    int currentPlayerIndex = 0;
    while(endPlayerIndex != currentPlayerIndex) {
        auto pd = activePlayersData[currentPlayerIndex];
        Action newAction = pd.player->preformAction(*this);
        recievedNewAction(newAction, pd);
        currentPlayerIndex = (currentPlayerIndex + 1) % activePlayersData.size();
    }
}

void Game::recievedNewAction(Action action, PlayerData& dataOfPlayerWhoActed) {
    if(isActionValid(action)) {
        banks[0]
    }
}

void Game::distributeBanks() {
    
}

bool Game::isActionValid(const Action& action) {
    return banks[0].isActionValid(action);    
}