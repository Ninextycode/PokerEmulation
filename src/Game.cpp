#include "game.h"

using namespace std;
using namespace pkr;

Game::Game(): bank(*this) {

}

Street Game::getStreet() const {
    return this->currentStreet;
}

Game::~Game() {
    
}

int Game::countPlayersWithChips() {
    int n = 0;
    for(auto pd: playersData) {
        if(pd->money > 0) {
            n++;
        }
    }
    return n;
}

void Game::setPlayers(std::vector<std::shared_ptr<Player> >& players) {
    for(auto player_ptr: players) {
        this->playersData.push_back(make_shared<PlayerData>());
        playersData.back()->player = player_ptr;
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
    moveButton();
    cleanSharedCards();
    bank.cleanForRound();
}

void Game::cleanSharedCards() {
    sharedCards.clear();
    sharedCards.reserve(7);
}

void Game::prepareDeck() {
    deck = Deck();
    deck.shuffle();
}

void Game::moveButton() {
    do {
        button =  (button + 1) % playersData.size();
    } while(!(playersData[button]->money > 0));
}

void Game::playPreflop() {
    this->currentStreet = Street::preflop;
    dealHoleCards();
    playStreet();
}

void Game::dealHoleCards() {
    for(auto pd: playersData) {
        if(pd->active) {
            pd->hand = Hand(deck.popCard(), deck.popCard());
        }
    }
}

void Game::playFlop() {
    this->currentStreet = Street::flop;
    dealFlop();
    playStreet();
}

void Game::dealFlop(){
    sharedCards.push_back(deck.popCard());
    sharedCards.push_back(deck.popCard());
    sharedCards.push_back(deck.popCard());
}

void Game::playTurn() {
    this->currentStreet = Street::turn;
    dealTurn();
    playStreet();
}

void Game::dealTurn(){
    sharedCards.push_back(deck.popCard());
}

void Game::playRiver() {
    this->currentStreet = Street::river;
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
    bank.distributeChips();
}

bool Game::isActionValid(Action action) {
    return bank.isActionValid(action);    
}