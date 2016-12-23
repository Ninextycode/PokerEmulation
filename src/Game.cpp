#include "game.h"

using namespace std;
using namespace pkr;

Game::Game(vector<shared_ptr<Player>>& players) {
    for(auto player_ptr: players) {
        this->playersData.push_back(make_shared<PlayerData>());
        playersData.back()->player = player_ptr;
    }
    bank = Bank(playersData);
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
    moveButton();
    setBankBlinds();
}

void Game::setBankBlinds() {
    bank.setBigBlind(this->bigBlind);
    bank.setSmallBlind(this->smallBlind);
}

void Game::prepareDeck() {
    deck = Deck();
    deck.shuffle();
}

void Game::moveButton() {
    button =  (button + 1) % playersData.size();
}

void Game::playPreflop() {
    dealHoleCards();
}

void Game::dealHoleCards() {
    for(auto pd: playersData) {
        if(pd->active) {
            pd->hand = Hand(deck.popCard(), deck.popCard());
        }
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
    int actorIndex = 0;
    while(bank.expectMoreBets()) {
        while(!playersData[actorIndex]->active) {
            actorIndex++;
        }
        Action newAction = playersData[actorIndex]->player->preformAction(*this);
        recievedNewAction(newAction);
    }
}

void Game::recievedNewAction(Action action) {
    if(isActionValid(action)) {
        bank.playAction(action);
    }
    throw new runtime_error("invalid action");
}

void Game::distributeBanks() {
    
}

bool Game::isActionValid(Action action) {
    return bank.isActionValid(action);    
}