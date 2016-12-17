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
        std::vector<std::shared_ptr<Player>> activePlayers;
        std::vector<std::shared_ptr<Player>> players;
        
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
        
        void distributeBanks();
        
        void dealHoleCards();
        void dealFlop();
        void dealTurn();
        void dealRiver();
        
    public:
        Street getCurrentStreet();
        bool isActionValid(Action action);
        void setPlayers(std::vector<std::shared_ptr<Player>> players);
        virtual void playGame() = 0;
        std::vector<std::shared_ptr<Player>> getPlayerActions();
    };
    
    
}

#endif /* GAME_H */

