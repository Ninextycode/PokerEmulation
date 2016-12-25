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
        
        virtual void onStartRound() = 0;
        virtual void onCardsDealed(std::shared_ptr<Player> player, Hand hand) = 0;
        virtual void onFlopDealed() = 0;
        virtual void onTurnDealed() =  0;
        virtual void onRiverDealed() = 0;
        virtual void onFinalCombinations(std::vector<Hand> hands, const std::vector<Card>& sharedCards) = 0;
        virtual void onGameEnd() = 0;
        virtual void onNewAction(Action action) = 0;
        
        virtual int getInitialStack() = 0;
        
        std::vector<Card> sharedCards;
        
        std::vector<PlayerData> playersData;
    private:
        Deck deck;

        Street currentStreet = Street::preflop;

        
        void prepareForRound();
        void prepareDeck();

        void moveButton();
        
        void playPreflop();
        void playFlop();
        void playTurn();
        void playRiver();
        void afterRoundPlayed();
        
        void prepareForNextStreet();
        void playStreet();
        void recievedNewAction(Action action);
        void cleanSharedCards();
        
        void distributeBanks();
        
        void placeBlinds();
        void dealHoleCards();
        void dealFlop();
        void dealTurn();
        void dealRiver();
        int indexOfPlayerInPlayerData(const std::shared_ptr<Player> player);
    
        Bank bank;
    public:
        
        const std::vector<PlayerData>& getPlayersData() const;
                
        Game();
        
        int countPlayersWithChips();
        void setPlayers(std::vector<std::shared_ptr<Player>> players);
            
        bool isActionValid(Action action);
        virtual void playGame() = 0;
        std::vector<std::shared_ptr<Player>> getPlayerActions();
        
        Street getStreet() const;
        
        virtual ~Game();
    };
    
    class OneTwoGame : public Game {
    protected:
        int getInitialStack() override;
        
        void onStartRound() override;
        void onCardsDealed(std::shared_ptr<Player> player, Hand hand) override;
        void onFlopDealed() override;
        void onTurnDealed() override;
        void onRiverDealed() override;
        void onFinalCombinations(std::vector<Hand> hands, const std::vector<Card>& sharedCards) override;        
        void onGameEnd() override;
        void onNewAction(Action action) override;
    public:
        void playGame() override;
    };
}

#endif /* GAME_H */

