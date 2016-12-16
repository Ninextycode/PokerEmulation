#include <vector>

namespace pok {
    enum class Street {
        preflop, flop, turn, river
    }

    enum class Move {
      fold, check, call, bet, raise
    }

    class Action {
    public:
        class ActionBuilder {
        public:
            ActionBuilder setPlayer()
            ActionBuilder setMoney(int money);
            ActionBuilder setMove(Move move);
            ActionBuilder setStreet(Street street);
            Action build();
        private:
            std::weak_ptr<Player> player;
            int money = 0;
        };
        int getMoney();
        Move getMove();
        Street getStreet();
    private:
        Action(int money, Move move, Street street, Action actiob)
        int money;
        Move move;
        Street street;
    }

    class Game {
    public:
        bool isActionValid(Action action);
        void setPlayers(std::vector<std::shared_ptr<Player>> players);
        void PlayGame(std::vector<std::shared_ptr<Player>> players);
        std::vector<std::shared_ptr<Player>> getPlayerActions()
    }

    class Player {
    public:
        void preformAction(&Game currentGame);
        std::vector<Action> getActions();
        std::vector<Action> getActions(Street street);
        
        virtual ~Player();
    }
}