#ifndef GAME_H
#define GAME_H

#include "headers.h"
#include "player.h"
#include "data_structs.h"
#include "bank.h"

namespace pkr {  
   
    class Game {
    friend class Bank;
    protected:
        int button = 0;
        int bigBlind = 1;
        int smallBlind = 1;
        void playRound();
    private:
        Deck deck;

        Street currentStreet = Street::preflop;
        std::vector<Card> sharedCards;
        
        void prepareForRound();
        void prepareDeck();

        void moveButton();
        
        void playPreflop();
        void playFlop();
        void playTurn();
        void playRiver();
        
        void playStreet();
        void recievedNewAction(Action action);
        void cleanSharedCards();
        
        void distributeBanks();
        
        void dealHoleCards();
        void dealFlop();
        void dealTurn();
        void dealRiver();
        int indexOfPlayerInPlayerData(const std::shared_ptr<Player> player);
    
        Bank bank;
    public:
        
        std::vector<std::shared_ptr<PlayerData>> playersData;
                
        Game();
        
        int countPlayersWithChips();
        void setPlayers(std::vector<std::shared_ptr<Player>>& players);
            
        bool isActionValid(Action action);
        virtual void playGame() = 0;
        std::vector<std::shared_ptr<Player>> getPlayerActions();
        
        Street getStreet() const;
        
        virtual ~Game();
    };
    
    class OneTwoGame : public Game {
        void playGame() override;
    };
}

#endif /* GAME_H */

