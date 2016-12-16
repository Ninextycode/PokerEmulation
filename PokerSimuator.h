#include <vector>
#include <memory>

namespace pok {
    class Player;
    
    enum class Street {
        preflop, flop, turn, river
    };

    enum class Move {
        fold, check, call, bet, raise
    };

    class Action {
    public:
        class ActionBuilder {
        public:
            ActionBuilder setPlayer();
            ActionBuilder setMoney(int money);
            ActionBuilder setMove(Move move);
            ActionBuilder setStreet(Street street);
            Action build();
        private:
            std::weak_ptr<Player> player;
            Move move;
            Street street;
            int money = 0;
        };
        
        int getMoney();
        Move getMove();
        std::weak_ptr<Player> getPlayer();
        Street getStreet();
    private:
        Action(int money, Move move, Street street, Player player);
        int money;
        Move move;
        Street street;
        std::weak_ptr<Player> player;
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
        virtual void preformAction(std::shared_ptr<Game> currentGame) = 0;  
        virtual ~Player();
    };
    
    class AllInPlayer {
    public:
        void preformAction(std::shared_ptr<Game> currentGame) override;
    };
}