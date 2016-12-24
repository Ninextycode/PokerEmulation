#include "player.h"
#include "data_structs.h"
using namespace pkr;
using namespace std;

bool PlayerData::isAllIn() {
    return this->active && this->money == 0;
}

Player::~Player() {
    
}