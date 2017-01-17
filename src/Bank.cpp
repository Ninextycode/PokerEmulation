#include "bank.h"

using namespace std;
using namespace pkr;

Bank::Bank(Game& game):  game(game) {
}

void Bank::resetForNewRound() {
    resetForNewStreet();
    resetBets();
}

void Bank::resetBets() {
    bets.resize(game.playersData.size(), 0);
    this->bigBlindPut = false;
    this->smallBlindPut = false; 
}

void Bank::resetForNewStreet() {
    if(this->game.currentStreet == Street::preflop && this->activePlayersNumber == 2) {
        this->nextExpectedBidderIndex = // adjustment for heads ups
                nextActiveNotAllInPlayerIndex(nextActiveNotAllInPlayerIndex(game.button));
    } else {
        this->nextExpectedBidderIndex = nextActiveNotAllInPlayerIndex(game.button);
    }
    this->bidderIndexToActLast = previousActiveNotAllInPlayerIndex(nextExpectedBidderIndex);
    
    this->lastBidderIndex = -1; // noone actually acted on this street
    this->notAllInPlayersNumber = 0;
    this->activePlayersNumber = 0;
    this->maxBet = 0;
    for(auto pd: game.playersData) {
        if(pd.active && !pd.isAllIn()) {
            this->notAllInPlayersNumber++;
            this->activePlayersNumber++;
        }
    }    
}

void Bank::playAction(Action action) {
    if(!isActionValid(action)) {
        throw wrong_action("Invalid action");
    }
    int index = nextExpectedBidderIndex;
    nextExpectedBidderIndex = nextActiveNotAllInPlayerIndex(index);

    int bet = action.getMoney();
    bets[index] += bet;
    
    lastBidderIndex = index;
    
    PlayerData& playerD = game.playersData[index];
    playerD.actions.push_back(action);
    playerD.money -= bet;
    
    if(bet > maxBet) { //raise
        //small blind is not counted as raise, so first raise is actually big blind
        lastRaisedBy = max(game.bigBlind, bet - maxBet);  
        maxBet = bet;
        
        if(notAllInPlayersNumber > 1) {
            bidderIndexToActLast = previousActiveNotAllInPlayerIndex(index);
        } else {
            bidderIndexToActLast = index; //someone raised, but everyone else are all-in
        }
    }
    
    if(didPlayerFold(playerD)) {
        playerD.active = false;
        activePlayersNumber--;
    }  
    
    if(playerD.isAllIn()) {
        notAllInPlayersNumber--;
    }
    
    if(bet == game.smallBlind) {
        smallBlindPut = true;
    }
    
    if(bet == game.bigBlind) {
        bigBlindPut = true;
    }
}

bool Bank::isPlayerActiveNotAllIn(PlayerData& data) {
    return (data.active && !data.isAllIn());
}

bool Bank::didPlayerFold(PlayerData& data) {
    return data.actions.back().getMoney() == 0 && maxBet > 0;
}

bool Bank::isActionValid(Action action) {
    if(!expectMoreBets()) {
        return false; // no more actions expected
    }
    
    if(action.getPlayer().lock() != game.playersData[nextExpectedBidderIndex].player) {
        return false; //wrong order of actions
    } 
    
        
    if(game.playersData[nextExpectedBidderIndex].money == action.getMoney()) { 
        return true; //all-in is also valid
    } 
    
    if(!smallBlindPut) {
        return action.getMoney() == game.smallBlind; //all-in already checked
    }
    
    if(!bigBlindPut) {
        return action.getMoney() == game.bigBlind; //all-in already checked
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

    return false;   
}

bool Bank::expectMoreBets() {
    return activePlayersNumber > 1 && notAllInPlayersNumber > 0 && lastBidderIndex != bidderIndexToActLast;
}

void Bank::distributeChips() {
    vector<pair<int, int>> positions_powers = getPowersOfPlayersCombinations();
    
    for(int i=0; i<positions_powers.size(); i++) {
        auto pos_pow = positions_powers[i];
                        
        int playersToShare = 0;
        //count how many players have the same combination, including himself
        for(int j=i; j<positions_powers.size(); j++) {
            if(positions_powers[j].second == pos_pow.second) {
                playersToShare++;
            }
        }
        
        //count how much money this players won in this round together
        int moneyToBeGiven = 0;
        int betOfThisPlayer = bets[pos_pow.first];
        if(betOfThisPlayer == 0) 
            continue;
        
        for(int j = i; j < positions_powers.size(); j++) {
            int& bet = bets[positions_powers[j].first];
            moneyToBeGiven += min(bet, betOfThisPlayer);
            bet -=  min(bet, betOfThisPlayer); //exclude money won by this players from common bank 
        }
        
                
        for(int k = i; k < i+playersToShare; k++) {
            game.playersData[positions_powers[k].first].money += moneyToBeGiven / playersToShare;
        }
        
        int remainings = moneyToBeGiven % playersToShare;
        //distribute money which cannot be fairly distributed        
        for(int k = i; k < i+playersToShare; k++) {
            if(remainings == 0) 
                break;
            game.playersData[positions_powers[k].first].money += 1;
            remainings -= 1;
        }
    }
    
    int chips = 0;
    for(int b: bets){
        chips += b;
    }
    if(chips != 0) {
        //throw runtime_error("not all chips distributed");
    }
}


vector<pair<int, int>> Bank::getPowersOfPlayersCombinations() {
    vector<pair<int, int>> positions_powers;

    for(int i = 0; i < game.playersData.size(); i++) {
        auto& pd = game.playersData[i];
        if(pd.active) {
            positions_powers.push_back(pair<int, int>(i, 
                    Evaluator::evaluate(game.sharedCards[0],
                    game.sharedCards[1],
                    game.sharedCards[2],
                    game.sharedCards[3],
                    game.sharedCards[4],
                    pd.hand.c1, pd.hand.c2)));
        }
    }
    sort(positions_powers.begin(), positions_powers.end(), 
            [](const  pair<int, int> & a, const  pair<int, int> & b) -> bool {
                return(a.second > b.second);
    });
    return positions_powers;
}

int Bank::nextActiveNotAllInPlayerIndex(int index) {
    for(int i = 0; i < game.playersData.size()-1; i++) {
        index = (index + 1) % game.playersData.size();
        if (isPlayerActiveNotAllIn(game.playersData[index])) {
            return index;
        }
    } 
    return -1; //noone to act next, everyone is allin or folded
}

int Bank::previousActiveNotAllInPlayerIndex(int index) {
    for(int i = 0; i < game.playersData.size()-1; i++) {
        index = (index + game.playersData.size() - 1) % game.playersData.size();
        if (isPlayerActiveNotAllIn(game.playersData[index])) {
            return index;
        }
    } 
    return -1; //noone to act next, everyone is allin or folded
}

int Bank::getNextExpectedBidderIndex() {
    return nextExpectedBidderIndex;
}