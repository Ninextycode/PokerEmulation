#include "player.h"
#include "game.h"

using namespace pkr;
using namespace std;

AllInPlayer::AllInPlayer(std::string name) {
    this->name = name;
}

void AllInPlayer::markAsWinner() {
    cout << name << " won" << endl;
}

Action AllInPlayer::preformAction(const Game& game, Hand hand) {
    return Action::ActionBuilder().setMoney(myMoney(game))
            .setPlayer(shared_from_this()).setStreet(game.getStreet()).build();
}

int AllInPlayer::myMoney(const Game& currentGame) const {
    auto data = currentGame.getPlayersData();
    for(auto pd: data) {
        if(pd.getPlayer() == shared_from_this()) {
            return pd.getMoney();
        }
    }
}
string AllInPlayer::getName() const {
    return this->name;
}