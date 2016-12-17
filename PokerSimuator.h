#include <vector>
#include <memory>
#include <iostream>
#include <exception>
#include <string>

#define s_ptr std::shared pointer
#define w_ptr std::weak_ptr<_Tp
namespace pkr {
    class Player;
    
    enum class Street {
        preflop, flop, turn, river
    };
    std::ostream& operator<<(std::ostream& out, const Street& street);
    
    class Action {
    public:      
        class ActionBuilder : public std::enable_shared_from_this<ActionBuilder>{
        public:
            //TODO return reference instead of pointers
            static std::shared_ptr<ActionBuilder> build_ptr();
            
            std::shared_ptr<ActionBuilder> setPlayer(std::string player);
            std::shared_ptr<ActionBuilder> setMoney(int money);
            std::shared_ptr<ActionBuilder> setStreet(Street street);
            Action build();
            
        private:
            ActionBuilder();
            std::string player;
            Street street;
            int money = 0;
            
            bool playerSet = false;
            bool streetSet = false;
            bool moneySet = false;    
        };
        
        class ActionBuilder2 {
        public:
            //TODO return reference instead of pointers            
            ActionBuilder2& setPlayer(std::string player);
            ActionBuilder2& setMoney(int money);
            ActionBuilder2& setStreet(Street street);
            Action build();
        private:
            std::string player;
            Street street;
            int money = 0;
            
            bool playerSet = false;
            bool streetSet = false;
            bool moneySet = false;    
        };
        
        int getMoney();
        std::string getPlayer();
        Street getStreet();
    private:
        Action(int money, Street street, std::string player);
        
        int money;
        Street street;
        std::string player;
        
    friend std::ostream& operator<<(std::ostream& out, const Action& action);
    };
    
    class Game {
    public:
        bool isActionValid(Action action);
        void setPlayers(std::vector<std::shared_ptr<Player>> players);
        virtual void PlayGame(std::vector<std::shared_ptr<Player>> players);
        std::vector<std::shared_ptr<Player>> getPlayerActions();
    };

    /*
     * Player class contains the logic of decisions, 
     * but not the data used to make this decisions.
     * Data is stored in Game class.
     */
    class Player {
    public:
        virtual std::string getName() = 0;
        virtual void preformAction(std::weak_ptr<Game> currentGame) = 0;  
        virtual ~Player();
    };
    
    class AllInPlayer : public Player{
    private:
        std::string name;
    public:
        std::string getName() override;
        void preformAction(std::weak_ptr<Game> currentGame) override;
    };
}