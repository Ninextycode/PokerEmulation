#ifndef PLAYER_H
#define PLAYER_H

#include "headers.h"

#include "simple_data_structs.h"
#include "data_structs.h"

namespace pkr{
    class Game;
    /*
     * Player class contains the logic of decisions, 
     * but not the data used to make this decisions.
     * Data is stored in Game class.
     */

    class Player : public std::enable_shared_from_this<Player> {
    public:
        virtual void markAsWinner() = 0;
        virtual Action preformAction(const Game& currentGame, Hand hand)  = 0;  
        
        virtual std::string getName() const = 0;
        virtual ~Player();
    };
    
    class AllInPlayer : public Player{
    private:
        std::string name;
    public:
        AllInPlayer(std::string name);
        void markAsWinner() override;
        std::string getName() const override;
        Action preformAction(const Game& currentGame, Hand hand) override;
        int myMoney(const Game& currentGame) const;
    };
}

#endif /* PLAYER_H */

