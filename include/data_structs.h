#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "headers.h"
#include "simple_data_structs.h"

namespace pkr {
    class Player;
    
    
    class Action {
    public:      
        class ActionBuilder {
        public:
            //TODO return reference instead of pointers            
            ActionBuilder& setPlayer(std::weak_ptr<Player> player);
            ActionBuilder& setMoney(int money);
            ActionBuilder& setStreet(Street street);
            Action build();
        private:
            std::weak_ptr<Player> player;
            Street street;
            int money = 0;
            
            bool playerSet = false;
            bool streetSet = false;
            bool moneySet = false;    
        };
        
        int getMoney();
        std::weak_ptr<const Player> getPlayer();
        Street getStreet();
    private:
        Action(int money, Street street, std::weak_ptr<Player> player);
        
        int money;
        Street street;
        std::weak_ptr<Player> player;
        
    friend std::ostream& operator<<(std::ostream& out, const Action& action);
    };

    class Player;
    class PlayerData {
    /*
     * Game class is friend for it to being able 
     * to assign a hand and prevent other classes from reading this hand
     */
    friend class Game;
    /*
     * Bank class is friend for it to being able 
     * to get the strength of hands and prevent other classes from reading this hand
     */
    friend class Bank;
    private: 
        Hand hand;
        int money;   
        std::shared_ptr<Player> player;        
        std::vector<Action> actions;

        bool active = true;
        bool isAllIn();
    public:
        int getMoney();
        std::vector<Action> getActions();
        std::shared_ptr<Player> getPlayer(); 
    };
}

#endif /* DATA_STRUCTURES_H */

