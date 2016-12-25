/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bank.h
 * Author: maxim
 *
 * Created on 23 December 2016, 16:44
 */

#include "headers.h"
#include "data_structs.h"

#ifndef BANK_H
#define BANK_H
namespace pkr {
    class Game;
    
    class Bank {
    private:        
        int lastBidderIndex = 0;
        int nextExpectedBidderIndex = 0;
        int bidderIndexToActLast;
        int maxBet = 0;
        int activePlayersNumber = 0;
        int notAllInPlayersNumber = 0;
        int lastRaisedBy = 0; //if one puts 125 in bank and another puts 360, then lastRaisedBy = (360-125) = 235
        
        bool smallBlindPut = false;
        bool bigBlindPut = false;
        
        std::vector<int> bets;
        std::vector<std::tuple<int, int>> getPowersOfPlayersCombinations();
        bool isPlayerAllIn(PlayerData& data);
        bool didPlayerFold(PlayerData& data);
        bool isPlayerActiveNotAllIn(PlayerData& data);
        
        int previousActiveNotAllInPlayerIndex(int index);
        int nextActiveNotAllInPlayerIndex(int index);

        void resetBets();
        Game& game;
                
    public:

        Bank(Game& game);
        void resetForNewRound();
        void resetForNewStreet();
                
        bool isActionValid(Action action);
        void playAction(Action action);

        int getNextExpectedBidderIndex();
        
        void distributeChips();
        
        bool expectMoreBets();

    };
}
#endif /* BANK_H */

