#include "data_structs.h"

using namespace std;
using namespace pkr;

Bank::Bank(const vector<std::shared_ptr<PlayerData>>& biddersData) {
    this->biddersData.insert(this->biddersData.end(), biddersData.begin(), biddersData.end());
}

void Bank::playAction(Action action) {
    if(! isActionValid(action)) {
        throw runtime_error("Invalid action");
    }
    int index = nextExpectedBidderIndex;
    PlayerData& playerD = biddersData[index];
    playerD.actions.push_back(action);
    playerD.money -= action.getMoney();
    
    maxBet = max(maxBet, action.getMoney());
    
    if(isPlayerAllIn(playerD)) {
        isSomeoneAllIn = true;
    }
    
    if(didPlayerFolded(playerD)) {
        playerD.active = false;
        biddersData.erase(biddersData.begin() + index); //TODO try use LINKED_LIST for faster erasing
    }  
    
    nextExpectedBidderIndex = (index + 1) % biddersData.size();
}

bool Bank::isPlayerAllIn(PlayerData& data) {
    return data.money = 0;
}

bool Bank::didPlayerFolded(PlayerData& data) {
    return data.actions.back().getMoney() == 0 && maxBet == 0;
}

bool Bank::isSplitRequired(int indexOfLastChangedData) {
    
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