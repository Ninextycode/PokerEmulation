#include "game.h"

using namespace std;
using namespace pkr;

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
    for(int i = 0; i < players.size(); i++) {
        if(players[i+button]->getMoney() > 0) {
            
        }
    };
}

void Game::moveButton() {
    button =  (button + 1) % players.size();
}

void Game::playPreflop() {
    dealHoleCards();
}

void Game::dealHoleCards() {
   
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
    
}

void Game::distributeBanks() {
   
}