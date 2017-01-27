#include "player.h"
#include "data_structs.h"
using namespace pkr;
using namespace std;

bool PlayerData::isAllIn() const {
    return this->active && this->money == 0;
}

int PlayerData::getMoney() const {
    return money;
}

vector<Action> PlayerData::getActions() const {
    return actions;
}

const shared_ptr<Player> PlayerData::getPlayer() const {
    return this->player;
}

bool PlayerData::isActive() const{
    return active;
}

Player::~Player() {
    
}
