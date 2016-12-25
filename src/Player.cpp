#include "player.h"
#include "data_structs.h"
using namespace pkr;
using namespace std;

bool PlayerData::isAllIn() {
    return this->active && this->money == 0;
}

int PlayerData::getMoney() {
    return money;
}

vector<Action> PlayerData::getActions() {
    return actions;
}

shared_ptr<Player> PlayerData::getPlayer() {
    return this->player;
}

bool PlayerData::isActive() {
    return active;
}

Player::~Player() {
    
}
