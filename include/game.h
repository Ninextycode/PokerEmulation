#ifndef GAME_H
#define GAME_H

#include "headers.h"
#include "player.h"
#include "data_structs.h"
#include "bank.h"
#include "deck.h"

namespace pkr {  
    class Bank;
    
    class Game {
    friend class Bank;
    protected:
        int button = -1; //for the button to be 0 after the first move
        int bigBlind = 1;
        int smallBlind = 1;
        void playRound();
        
        virtual void onStartRound() const = 0;
        virtual void onCardsDealt(std::shared_ptr<Player> const player, Hand hand) const = 0;
        virtual void onFlopDealt(std::vector<Card> flop) const = 0;
        virtual void onTurnDealt(Card turn) const =  0;
        virtual void onRiverDealt(Card river) const = 0;
        virtual void onFinalCombinations(std::vector<Hand> hands, const std::vector<Card>& sharedCards) const = 0;
        virtual void onGameEnd() const = 0;
        virtual void onNewAction(Action action) const = 0;
        
        virtual int getInitialStack() const = 0;
        
        std::vector<Card> sharedCards;
        
        std::vector<PlayerData> playersData;
        
            
        int countPlayersWithChips();
        
    private:
        std::shared_ptr<Deck> deck;

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

        
        Bank* bank;
    public:  
        const std::vector<PlayerData>& getPlayersData() const;
                
        Game(std::shared_ptr<Deck> deck);
        Game();
            
        void setPlayers(std::vector<std::shared_ptr<Player>> players);
            
        bool isActionValid(Action action);
        virtual void playGame() = 0;

        Street getStreet() const;
        
        virtual ~Game();
    };
    
    class OneTwoGame : public Game {
    protected:
        int getInitialStack() const override;
        void onStartRound() const override;
        void onCardsDealt(std::shared_ptr<Player> const player, Hand hand) const override;
        void onFlopDealt(std::vector<Card> flop) const override;
        void onTurnDealt(Card turn) const override;
        void onRiverDealt(Card river) const override;
        void onFinalCombinations(std::vector<Hand> hands, const std::vector<Card>& sharedCards) const override;
        void onGameEnd() const override;
        void onNewAction(Action action) const override;

    public:
        using Game::Game;
        
        void playGame() override;
    };
}

#endif /* GAME_H */

