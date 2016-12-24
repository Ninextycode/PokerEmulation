#ifndef GAME_H
#define GAME_H

#include "headers.h"
#include "player.h"
#include "data_structs.h"
#include "bank.h"

namespace pkr {  
   
    class Game {
    friend class Bank;
    private:
        int button = 0;
        int bigBlind = 1;
        int smallBlind = 1;
        
        Deck deck;
        std::vector<std::shared_ptr<PlayerData>> playersData;
        
        std::vector<Card> sharedCards;
        Street currentStreet = Street::preflop;
        
        void prepareForRound();
        void prepareDeck();

        void moveButton();
        
        void playPreflop();
        void playFlop();
        void playTurn();
        void playRiver();
        
        void playRound();
        void playStreet();
        void recievedNewAction(Action action);
        
        void distributeBanks();
        
        void dealHoleCards();
        void dealFlop();
        void dealTurn();
        void dealRiver();
        int indexOfPlayerInPlayerData(const std::shared_ptr<Player> player);
    
        Bank bank;
    public:
        Game(std::vector<std::shared_ptr<Player>>& player);

        bool isActionValid(Action action);
        virtual void playGame() = 0;
        std::vector<std::shared_ptr<Player>> getPlayerActions();
    };
    
    
}

#endif /* GAME_H */

