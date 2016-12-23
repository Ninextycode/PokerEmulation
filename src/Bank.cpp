#include "bank.h"

using namespace std;
using namespace pkr;

Bank::Bank(){}

Bank::Bank(const vector<std::shared_ptr<PlayerData>>& biddersData) {
    this->biddersData.insert(this->biddersData.end(), biddersData.begin(), biddersData.end());
    for(int i = 0; i < this->biddersData.size(); i++) {
        if(this->biddersData[i]->active) {
            this->activeNotAllInPlayersNumber++;
        }
    }
    resetForNewStreet();
}

Bank::setBigBlind(int bigBlind) {
    this->bigBlind = bigBlind;
}

Bank::setSmallBlind(int smallBlind) {
    this->smallBlind = smallBlind;
}


void Bank::playAction(Action action) {
    if(!isActionValid(action)) {
        throw runtime_error("Invalid action");
    }
    int index = nextExpectedBidderIndex;
    int bet = action.getMoney();
        
    lastBidderIndex = index;
    
    PlayerData& playerD = *biddersData[index];
    playerD.actions.push_back(action);
    playerD.money -= bet;
    
    if(bet > maxBet) {
        bidderIndexToActLast = previousActiveNotAllInPlayerIndex(index);
    }
    
    if(didPlayerFold(playerD)) {
        playerD.active = false;
        activeNotAllInPlayersNumber--;
    }  
    

}

bool Bank::isPlayerAllIn(PlayerData& data) {
    return data.money == 0 && data.active;
}

bool Bank::isPlayerActiveNotAllIn(PlayerData& data) {
    return (!data.active && !isPlayerAllIn(data));
}

bool Bank::didPlayerFold(PlayerData& data) {
    return data.actions.back().getMoney() == 0 && maxBet > 0;
}

bool Bank::isActionValid(Action action) {
    if(!expectMoreBets()) {
        return false; // no more actions expected
    }
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

void Bank::resetForNewStreet() {
    this->nextExpectedBidderIndex = firstActiveNotAllInPlayerIndex();
    this->bidderIndexToActLast = lastActiveNotAllInPlayerIndex();
    this->lastBidderIndex = -1; //noonae actually cated
}

bool Bank::expectMoreBets() {
    return activeNotAllInPlayersNumber > 1 && lastBidderIndex == bidderIndexToActLast;
}

int Bank::nextActiveNotAllInPlayerIndex(int index) {
    for(int i = 0; i < this->biddersData.size(); i++) {
        index = (index + 1) % biddersData.size();
        if (isPlayerActiveNotAllIn(*biddersData[index])) {
            return index;
        }
    } 
    throw runtime_error("cannot find next player which can act");
}

int Bank::previousActiveNotAllInPlayerIndex(int index) {
    for(int i = 0; i < this->biddersData.size(); i++) {
        index = (index + biddersData.size() - 1) % biddersData.size();
        if (isPlayerActiveNotAllIn(*biddersData[index])) {
            return index;
        }
    } 
    throw runtime_error("cannot find previous player which can act");
}

int Bank::firstActiveNotAllInPlayerIndex() {
    for(int i = 0; i < this->biddersData.size(); i++) {
        if (isPlayerActiveNotAllIn(*biddersData[i])) {
            return i;
        }
    } 
    throw runtime_error("cannot find player which can act");
}

int Bank::lastActiveNotAllInPlayerIndex() {
    for(int i = this->biddersData.size()-1; i >= 0 ; i--) {
        if (isPlayerActiveNotAllIn(*biddersData[i])) {
            return i;
        }
    } 
    throw runtime_error("cannot find player which can act");
}
