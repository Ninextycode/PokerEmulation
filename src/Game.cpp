#include "game.h"

using namespace std;
using namespace pkr;

Game::Game() {
   deck = std::make_shared<Deck>();
   bank = new Bank(*this);
}

Game::Game(shared_ptr<Deck> deck): deck(deck) {
   bank = new Bank(*this);
}

Street Game::getStreet() const {
    return this->currentStreet;
}
const vector<PlayerData>& Game::getPlayersData() const {
    return this->playersData;
}

Game::~Game() {
    delete bank;
}

int Game::countPlayersWithChips() {
    int n = 0;
    for(auto pd: playersData) {
        if(pd.money > 0) {
            n++;
        }
    }
    return n;
}

void Game::setPlayers(std::vector<std::shared_ptr<Player> > players) {
    for(auto player_ptr: players) {
        PlayerData pd;       
        pd.player = player_ptr;
        pd.money = getInitialStack();
        this->playersData.push_back(pd);
    }
}

void Game::playRound() {
    if(this->countPlayersWithChips() < 2) {
        throw runtime_error("not enough players for this round");
    }
    
    prepareForRound();
    
    playPreflop();
    playFlop();
    playTurn();
    playRiver();
    
    distributeBanks();
    afterRoundPlayed();
}

void Game::prepareForRound() {
    prepareDeck();
    moveButton();
    cleanSharedCards();
    bank->resetForNewRound();
    onStartRound();
}

void Game::cleanSharedCards() {
    sharedCards.clear();
    sharedCards.reserve(7);
}

void Game::prepareDeck() {
    deck->shuffle();
}

void Game::moveButton() {
    do {
        button =  (button + 1) % playersData.size();
    } while(!(playersData[button].money > 0));
}

void Game::playPreflop() {
    this->currentStreet = Street::preflop;
    placeBlinds();
    dealHoleCards();
    playStreet();
}

void Game::placeBlinds() {
    auto pd = playersData[bank->getNextExpectedBidderIndex()];
    Action smallBlindAction = Action::ActionBuilder()
            .setMoney(min(smallBlind, pd.money)).setPlayer(pd.player).setStreet(currentStreet).build();
    recievedNewAction(smallBlindAction);
    
    pd = playersData[bank->getNextExpectedBidderIndex()];
    Action bigBlindAction = Action::ActionBuilder()
            .setMoney(min(bigBlind, pd.money)).setPlayer(pd.player).setStreet(currentStreet).build();
    recievedNewAction(bigBlindAction);
}

void Game::dealHoleCards() {
    for(auto& pd: playersData) {
        if(pd.active) {
            Hand h(deck->popCard(), deck->popCard());
            this->onCardsDealed(pd.player, h);
            pd.hand = h;
        }
    }
}

void Game::playFlop() {
    this->currentStreet = Street::flop;
    dealFlop();
    playStreet();
}

void Game::dealFlop(){
    sharedCards.push_back(deck->popCard());
    sharedCards.push_back(deck->popCard());
    sharedCards.push_back(deck->popCard());
    this->onFlopDealed();
}

void Game::playTurn() {
    this->currentStreet = Street::turn;
    dealTurn();
    playStreet();
}

void Game::dealTurn(){
    sharedCards.push_back(deck->popCard());
    this->onTurnDealed();
}

void Game::playRiver() {
    this->currentStreet = Street::river;
    dealRiver();
    playStreet();
}

void Game::dealRiver(){
    sharedCards.push_back(deck->popCard());
    this->onRiverDealed();
}

void Game::playStreet() {
    prepareForNextStreet();

    while(bank->expectMoreBets()) {
        Action newAction = playersData[bank->getNextExpectedBidderIndex()].player->preformAction(*this);
        recievedNewAction(newAction);
    }
    
}

void Game::afterRoundPlayed() {
    vector<Hand> hands;
    hands.reserve(playersData.size());
    for(auto pd : playersData) {
        hands.push_back(pd.hand);
    }
    this->onFinalCombinations(hands, sharedCards);
    this->onGameEnd();
}

void Game::prepareForNextStreet() {
    bank->resetForNewStreet();
}

void Game::recievedNewAction(Action action) {
    bank->playAction(action);
    onNewAction(action);
}

void Game::distributeBanks() {
    bank->distributeChips();
}

bool Game::isActionValid(Action action) {
    return bank->isActionValid(action);    
}