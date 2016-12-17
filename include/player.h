#ifndef PLAYER_H
#define PLAYER_H

#include "headers.h"
#include "game.h"
#include "data_structures.h"

namespace pkr{
    class Game;
    
    /*
     * Player class contains the logic of decisions, 
     * but not the data used to make this decisions.
     * Data is stored in Game class.
     */
    class Player {
    private:
        Card card1, card2;
    public:
        virtual void markAsWinner() = 0;
        virtual void preformAction(std::weak_ptr<Game> currentGame) = 0;  
        
        virtual std::string getName() = 0;
        virtual ~Player();
    };
    
    class AllInPlayer : public Player{
    private:
        std::string name;
    public:
        void markAsWinner() override;
        std::string getName() override;
        void preformAction(std::weak_ptr<Game> currentGame) override;
    };
}

#endif /* PLAYER_H */

