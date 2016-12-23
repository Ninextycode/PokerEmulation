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
    class Bank {
    private:        
        int lastBidderIndex = 0;
        int nextExpectedBidderIndex = 0;
        int bidderIndexToActLast;
        int maxBet = 0;
        int activeNotAllInPlayersNumber = 0;
        
        int bigBlind;
        int smallBlind;
        
        bool isPlayerAllIn(PlayerData& data);
        bool didPlayerFold(PlayerData& data);
        bool isPlayerActiveNotAllIn(PlayerData& data);
        
        int previousActiveNotAllInPlayerIndex(int index);
        int nextActiveNotAllInPlayerIndex(int index);
        
        int lastActiveNotAllInPlayerIndex();
        int firstActiveNotAllInPlayerIndex();
        std::vector<std::shared_ptr<PlayerData>> biddersData; 
         
    public:
        void setBigBlind(int bigBlind);
        void setSmallBlind(int smallBlind);
        
        Bank();
        Bank(const std::vector<std::shared_ptr<PlayerData>>& biddersDara);

        bool isActionValid(Action action);
        void playAction(Action action);
        void resetForNewStreet();
        bool expectMoreBets();

    };
}
#endif /* BANK_H */

