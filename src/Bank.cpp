#include "data_structs.h"

using namespace std;
using namespace pkr;

Bank::Bank(const vector<std::shared_ptr<PlayerData>>& biddersData) {
    this->biddersData.insert(this->biddersData.end(), biddersData.begin(), biddersData.end());
}

bool Bank::isActionValid(Action action) {
    if(action.getPlayer().lock() != biddersData[nextExpectedBidderIndex]->player) {
        return false; //wrong order of actions
    } 
    if(action.getMoney() == 0) {
        return true; //it is either check or fold, so valid
    }
    
    if(action.getMoney() >= maxBet) {
        return true; //call or raise
    } 
    
    if(biddersData[nextExpectedBidderIndex]->money == action.getMoney()) { 
        return true; //all-in is also valid
    } 
    return false;   
}

bool Bank::isActive() {
    return active;
}