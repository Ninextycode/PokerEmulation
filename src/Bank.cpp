#include "bank.h"
#include "game.h"
#include "evaluator.h"

using namespace std;
using namespace pkr;

Bank::Bank(Game& game):  game(game) {
    resetForNewStreet();
    bets.resize(game.playersData.size(), 0);
}

void Bank::cleanForRound() {
    for(int i = 0; i < bets.size(); i++) {
        bets[i] = 0;
    }
}

void Bank::playAction(Action action) {
    if(!isActionValid(action)) {
        throw runtime_error("Invalid action");
    }
    int index = nextExpectedBidderIndex;
    int bet = action.getMoney();
    bets[index] += bet;
    
    lastBidderIndex = index;
    
    PlayerData& playerD = *game.playersData[index];
    playerD.actions.push_back(action);
    playerD.money -= bet;
    
    if(bet > maxBet) { //raise
        //small blind is not counted as raise, so first raise is actually big blind
        lastRaisedBy = max(game.bigBlind, bet - maxBet);  
        bidderIndexToActLast = previousActiveNotAllInPlayerIndex(index);
        maxBet = bet;
    }
    
    if(didPlayerFold(playerD)) {
        playerD.active = false;
        activeNotAllInPlayersNumber--;
    }  
    
    if(bet == game.smallBlind) {
        smallBlindPut = true;
    }
    
    if(bet == game.bigBlind) {
        bigBlindPut = true;
    }
}

bool Bank::isPlayerActiveNotAllIn(PlayerData& data) {
    return (!data.active && !data.isAllIn());
}

bool Bank::didPlayerFold(PlayerData& data) {
    return data.actions.back().getMoney() == 0 && maxBet > 0;
}

bool Bank::isActionValid(Action action) {
    if(!expectMoreBets()) {
        return false; // no more actions expected
    }
    
    if(!smallBlindPut) {
        return action.getMoney() == game.smallBlind;
    }
    
    if(!bigBlindPut) {
        return action.getMoney() == game.bigBlind;
    }
    
    if(action.getPlayer().lock() != game.playersData[nextExpectedBidderIndex]->player) {
        return false; //wrong order of actions
    } 
    if(action.getMoney() == 0) {
        return true; //it is either check or fold, so valid
    }
    
    if(action.getMoney() == maxBet) {
        return true; //call
    } 
    
    if(action.getMoney() > maxBet) { //raise
        if((action.getMoney() - maxBet) >= lastRaisedBy) { //next raise should be no less than last
            return true;
        } else {
            return false;
        }
    }
    
    if(game.playersData[nextExpectedBidderIndex]->money == action.getMoney()) { 
        return true; //all-in is also valid
    } 
    return false;   
}

void Bank::resetForNewStreet() {
    this->nextExpectedBidderIndex = firstActiveNotAllInPlayerIndex();
    this->bidderIndexToActLast = lastActiveNotAllInPlayerIndex();
    this->lastBidderIndex = -1; //noonae actually cated
    this->activeNotAllInPlayersNumber = 0;
    for(auto pd: game.playersData) {
        if(pd->active && !pd->isAllIn()) {
            this->activeNotAllInPlayersNumber++;
        }
    }    
}

bool Bank::expectMoreBets() {
    return activeNotAllInPlayersNumber > 1 && lastBidderIndex == bidderIndexToActLast;
}

void Bank::distributeChips() {
    vector<tuple<int, int>> positions_powers = getPowersOfPlayersCombinations();
    
    for(int i=0; i<positions_powers.size(); /*i incremented at the end of the loop body*/) {
        auto pos_pow = positions_powers[i];
        int playersToShare = 1;
        
        
        //count how many players have the same combination
        for(int j=0; i<positions_powers.size(); i++) {
            if(i!=j && get<1>(positions_powers[j]) == get<1>(pos_pow)) {
                playersToShare++;
            }
        }
        
        //count how much money this players won in this round together
        int moneyToBeGiven = 0;
        int betOfThisPlayer = bets[get<0>(pos_pow)];
        for(int j = i; j < positions_powers.size(); j++) {
            moneyToBeGiven += min(bets[j], betOfThisPlayer);
            bets[j] -=  min(bets[j], betOfThisPlayer); //exclude money won by this players from common bank 
        }
        
        
        int remainings = moneyToBeGiven % playersToShare;
        //distribute money which cannot be fairly distributed
        while(remainings > 0) {            
            for(int k = i; k < i+playersToShare; k++) {
                game.playersData[k]->money += 1;
                remainings -= 1;
                if(remainings == 0) break;
            }
        }
        
        for(int k = i; k < i+playersToShare; k++) {
            game.playersData[k]->money += moneyToBeGiven / playersToShare;
        }
        
        i += playersToShare;
    }
    
    int chips = 0;
    for(int b: bets){
        chips += b;
    }
    if(chips != 0) {
        throw runtime_error("not all chips distributed");
    }
}


vector<tuple<int, int>> Bank::getPowersOfPlayersCombinations() {
    vector<tuple<int, int>> positions_powers;
    positions_powers.reserve(game.playersData.size());
    for(int i = 0; i < game.playersData.size(); i++) {
        auto pd = game.playersData[i];
        if(pd->active) {
            positions_powers.push_back(make_tuple(i, 
                    Evaluator::evaluate(game.sharedCards[0],
                    game.sharedCards[1],
                    game.sharedCards[2],
                    game.sharedCards[3],
                    game.sharedCards[4],
                    pd->hand.c1, pd->hand.c2)));
        } else {
            positions_powers.push_back({i, -1});
        }
    }
    sort(positions_powers.begin(), positions_powers.end(), 
            [](const  tuple<int, int> & a, const  tuple<int, int> & b) -> bool {
                return(get<1>(a) < get<1>(b));
    });
    return positions_powers;
}

int Bank::nextActiveNotAllInPlayerIndex(int index) {
    for(int i = 0; i < game.playersData.size(); i++) {
        index = (index + 1) % game.playersData.size();
        if (isPlayerActiveNotAllIn(*game.playersData[index])) {
            return index;
        }
    } 
    throw runtime_error("cannot find next player which can act");
}

int Bank::previousActiveNotAllInPlayerIndex(int index) {
    for(int i = 0; i < game.playersData.size(); i++) {
        index = (index + game.playersData.size() - 1) % game.playersData.size();
        if (isPlayerActiveNotAllIn(*game.playersData[index])) {
            return index;
        }
    } 
    throw runtime_error("cannot find previous player which can act");
}

int Bank::firstActiveNotAllInPlayerIndex() {
    for(int i = 0; i < game.playersData.size(); i++) {
        if (isPlayerActiveNotAllIn(*game.playersData[i])) {
            return i;
        }
    } 
    throw runtime_error("cannot find player which can act");
}

int Bank::lastActiveNotAllInPlayerIndex() {
    for(int i = game.playersData.size()-1; i >= 0 ; i--) {
        if (isPlayerActiveNotAllIn(*game.playersData[i])) {
            return i;
        }
    } 
    throw runtime_error("cannot find player which can act");
}
