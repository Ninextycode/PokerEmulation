#ifndef GAME_H
#define GAME_H

#include "headers.h"
#include "player.h"
#include "data_structures.h"

namespace pkr {  
    class Player;
    
    class Game {
    private:
        int button = 0;
        
        Deck deck;
        std::vector<PlayerData> activePlayersData;
        std::vector<PlayerData> playersData;
        
        std::vector<Card> sharedCards;
        Street currentStreet = Street::preflop;
        
        void prepareForRound();
        void prepareDeck();
        void prepareActivePlayers();
        void moveButton();
        
        void playPreflop();
        void playFlop();
        void playTurn();
        void playRiver();
        
        void playRound();
        void playStreet();
        void workAroundNewAction(Action action, PlayerData& dataOfPlayerWhoActed);
        
        void distributeBanks();
        
        void dealHoleCards();
        void dealFlop();
        void dealTurn();
        void dealRiver();
        
    public:
        Street getCurrentStreet();
        bool isActionValid(const Action& action);
        void setPlayers(std::vector<std::shared_ptr<Player>> players);
        virtual void playGame() = 0;
        std::vector<std::shared_ptr<Player>> getPlayerActions();
    };
    
    
}

#endif /* GAME_H */

