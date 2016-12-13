
enum class Street {
    preflop, flop, turn, river
}

enum class Move {
  fold, check, call, bet, raise
}

class Action {
public Action()
  //use this pattern for many paramethers
private:
    int money;
    Move move;
    Street street;
    Action action;
}

class Game {
public:
    void PlayGame(std::vector<std::shared_ptr<Player>> players);
}

class Player {
public:
    void preformAction(&Game currentGame);
    vector<Action> getActions();
    vector<Action> getActions(Street street);
}